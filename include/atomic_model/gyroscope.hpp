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

// dummy accelerometer read function
std::vector<float> read_gyroscope()
{
    std::vector<float> ret_val = {1.0, 2.0, 3.0};
    return ret_val;
}

//Port definition
struct gyroscope_ports
{
    struct out : public out_port<std::vector<float>>
    {
    };
};

template <typename TIME>
class gyroscope
{
private:
    TIME refresh_rate;

public:
    using output_ports = tuple<typename gyroscope_ports::out>;
    
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

    // output function
    typename make_message_bags<output_ports>::type output() const
    {
        typename make_message_bags<output_ports>::type bags;
        vector<std::vector<float>> bag_port_out;

        bag_port_out.push_back(read_gyroscope());
        get_messages<typename gyroscope_ports::out>(bags) = bag_port_out;
        
        return bags;
    }

    // time advance function
    TIME time_advance() const
    {
        return refresh_rate;
    }
};

#endif