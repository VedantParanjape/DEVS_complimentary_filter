#ifndef __GYROSCOPE_HPP__
#define __GYROSCOPE_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <assert.h>
#include <string>
#include <random>
#include <limits>

using namespace cadmium;
using namespace std;

// dummy gyroscope read function
std::vector<float> read_gyroscope()
{
    std::vector<float> ret_val = {1.0, 2.0, 3.0};
    return ret_val;
}

//Port definition
struct gyroscope_ports
{
    struct out_x : public out_port<float> {};
    struct out_y : public out_port<float> {};
    struct out_z : public out_port<float> {};
};

template <typename TIME>
class gyroscope
{
private:
    TIME refresh_rate;

public:
    using output_ports = tuple<typename gyroscope_ports::out_x, typename gyroscope_ports::out_y, typename gyroscope_ports::out_z>;
    
    // default constructor
    gyroscope() noexcept
    {
        refresh_rate = TIME("00:00:00:100");
    }

    // parameterized constructor
    gyroscope(TIME refresh_rate_sensor)
    {
        refresh_rate = refresh_rate_sensor;
    }

    struct state_type
    {
        std::vector<float> gyro;
    }; 
    state_type state;

    // internal transition function
    void internal_transition()
    {
        state.gyro = read_gyroscope();
    }

    // confluence transition function
    void confluence_transition(TIME e, typename make_message_bags<output_ports>::type mbs) 
    {
        internal_transition();
    }

    // output function
    typename make_message_bags<output_ports>::type output() const
    {
        typename make_message_bags<output_ports>::type bags;

        get_messages<typename gyroscope_ports::out_x>(bags).push_back(state.gyro[0]);
        get_messages<typename gyroscope_ports::out_y>(bags).push_back(state.gyro[1]);
        get_messages<typename gyroscope_ports::out_z>(bags).push_back(state.gyro[2]);

        return bags;
    }

    // time advance function
    TIME time_advance() const
    {
        return refresh_rate;
    }
};

#endif