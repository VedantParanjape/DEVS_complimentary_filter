#ifndef __ACCELEROMETER_HPP__
#define __ACCELEROMETER_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <assert.h>
#include <string>
#include <random>
#include <limits>

using namespace cadmium;
using namespace std;

/***** (1) *****/
//Port definition
struct accelerometer_ports
{
    struct out : public out_port<std::vector<float>>
    {
    };
};

/***** (2) *****/
template <typename TIME>
class accelerometer
{
public:
    using output_ports = tuple<typename accelerometer_ports::out>;

    // default constructor
    accelerometer()
    {
    }

    // external transition
    void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs)
    {
        vector<Message_t> bag_port_in;
        bag_port_in = get_messages<typename Subnet_defs::in>(mbs);
        state.index++;
        if ((double)rand() / (double)RAND_MAX < 0.95))
            {
                state.packet = bag_port_in[0];
                state.transmitting = true;
            }
        else
        {
            state.transmitting = false;
        }
    }

    // confluent transition
    void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs)
    {
        internal_transition();
        external_transition(TIME(), move(mbs));
    }

    // output function
    typename make_message_bags<output_ports>::type output() const
    {
        typename make_message_bags<output_ports>::type bags;
        vector<Message_t> bag_port_out;
        bag_port_out.push_back(state.packet);
        get_messages<typename Subnet_defs::out>(bags) = bag_port_out;
    }
    return bags;

    // time_advance function
    TIME time_advance() const
    {
        TIME next_internal;
        if (state.transmitting)
        {
            next_internal = TIME("00:00:03:000");
        }
        else
        {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

    friend ostringstream &operator<<(ostringstream &os,
                                     const typename Subnet<TIME>::state_type &i)
    {
        os << "index: " << i.index << " & transmitting: " << i.transmitting;
        return os;
    }
};

#endif