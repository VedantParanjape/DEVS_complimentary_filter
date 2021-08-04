#ifndef __FUSION_CONTROLLER_HPP__
#define __FUSION_CONTROLLER_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include "complimentary_filter.hpp"
#include "message.hpp"
#include <assert.h>
#include <string>
#include <random>
#include <limits>

using namespace cadmium;
using namespace std;

struct fusion_controller_ports
{
    struct in_accel : public in_port<cartesion_vector> {};
    struct in_gyro : public in_port<cartesion_vector> {};
    struct in_offset: public in_port<cartesion_vector> {};

    struct out_fused_angle : public out_port<cartesion_vector> {};
};

template <typename TIME>
class fusion_controller
{
public:
    using input_ports = tuple<typename fusion_controller_ports::in_accel, 
                                typename fusion_controller_ports::in_gyro,
                                  typename fusion_controller_ports::in_offset>;
    using output_ports = tuple<typename fusion_controller_ports::out_fused_angle>;

    fusion_controller() noexcept
    {
        state.fused_angle = std::vector<float> (3);
        state.active = false;
    }

    struct state_type
    {
        std::vector<float> fused_angle;
        bool active;
    };
    state_type state;

    // internal transition function
    void internal_transition()
    {
        state.active = false;
    }

    // external transition function
    void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs)
    {
        std::vector<float> in_accel, in_gyro, in_offset;

        for (const auto &x : get_messages<typename fusion_controller_ports::in_accel>(mbs))
        {
            in_accel = x.data;
        }
        for (const auto &x : get_messages<typename fusion_controller_ports::in_gyro>(mbs))
        {
            in_gyro = x.data;
        }
        for (const auto &x : get_messages<typename fusion_controller_ports::in_offset>(mbs))
        {
            in_offset = x.data;
        }
        state.fused_angle = complimentary_filter(in_accel, in_gyro, in_offset);
        
        state.active = true;
    }

    void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs)
    {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
    }

    // output function
    typename make_message_bags<output_ports>::type output() const 
    {
        typename make_message_bags<output_ports>::type bags;

        get_messages<typename fusion_controller_ports::out_fused_angle>(bags).push_back(cartesion_vector(state.fused_angle));

        return bags;
    }

    // time_advance function
    TIME time_advance() const 
    {
        // + TODO: what should be time here ?
        return state.active ? TIME("00:00:00:00") : std::numeric_limits<TIME>::infinity();
    }

    friend ostringstream& operator<<(ostringstream& os, const typename fusion_controller<TIME>::state_type& i) 
    {
#if defined(RT_ARM_MBED)        
        printf("fused_angle: x:%f y:%f z:%f\n", i.fused_angle[0], i.fused_angle[1], i.fused_angle[2]);
#else
        os << "\n";
        os << "fused_angle:" << " x: " << i.fused_angle[0] << " y: " << i.fused_angle[1] << " z: " << i.fused_angle[2] << "\n";
#endif
        return os;
    }
};

#endif