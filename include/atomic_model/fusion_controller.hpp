#ifndef __FUSION_CONTROLLER_HPP__
#define __FUSION_CONTROLLER_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include <algorithm/complimentary_filter.hpp>

#include <assert.h>
#include <string>
#include <random>
#include <limits>

using namespace cadmium;
using namespace std;

struct fusion_controller_ports
{
    struct in_accel : public in_port<std::vector<float>> {};
    struct in_gyro : public in_port<std::vector<float>> {};
    struct in_offset: public in_port<std::vector<float>> {};

    struct out_fused_angle : public out_port<std::vector<float>> {};
};

template <typename TIME>
class fusion_controller
{
public:
    using input_ports = tuple<typename fusion_controller_ports::in_accel, typename fusion_controller_ports::in_gyro>;
    using output_ports = tuple<typename fusion_controller_ports::out_fused_angle>;

    fusion_controller() noexcept
    {
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
        state.fused_angle = complimentary_filter(get_messages<typename fusion_controller_ports::in_accel>(mbs)[0],
                                                    get_messages<typename fusion_controller_ports::in_gyro>(mbs)[0],
                                                       get_messages<typename fusion_controller_ports::in_offset>(mbs)[0]);

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

        get_messages<typename fusion_controller_ports::out_fused_angle>(bags).push_back(state.fused_angle);

        return bags;
    }

    // time_advance function
    TIME time_advance() const 
    {
        // + TODO: what should be time here ?
        return state.active ? TIME("00:00:00") : std::numeric_limits<TIME>::infinity();
    }

    friend ostringstream& operator<<(ostringstream& os, const typename fusion_controller<TIME>::state_type& i) 
    {
        os << "fused angle:" << " x: " << i.fused_angle[0] << " y: " << i.fused_angle[1] << " z: " << i.fused_angle[2] << "\n";
        
        return os;
    }
};

#endif