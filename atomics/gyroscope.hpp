#ifndef __GYROSCOPE_HPP__
#define __GYROSCOPE_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <assert.h>
#include <string>
#include <random>
#include <limits>

#include "driver.hpp"

using namespace cadmium;
using namespace std;

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
    IMU imu_driver;
    MPU6050 *gyro;

public:
    using input_ports = tuple<>;
    using output_ports = tuple<typename gyroscope_ports::out_x, typename gyroscope_ports::out_y, typename gyroscope_ports::out_z>;
    
    // default constructor
    gyroscope(PinName sda, PinName scl) noexcept
    {
        refresh_rate = TIME("00:00:00:100");
        gyro = imu_driver.init(sda, scl);
    }

    // parameterized constructor
    gyroscope(TIME refresh_rate_sensor, PinName sda, PinName scl)
    {
        refresh_rate = refresh_rate_sensor;
        gyro = imu_driver.init(sda, scl);
    }

    struct state_type
    {
        std::vector<float> gyro;
    }; 
    state_type state;

    // internal transition function
    void internal_transition()
    {
        float readings[3];
        gyro->getGyro(readings);
        state.gyro = {readings[0], readings[1], readings[2]};
    }
    
    // external transition function
    void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs)
    {
        // do nothing
    }
    
    // confluence transition function
    void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) 
    {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
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

    friend ostringstream& operator<<(ostringstream& os, const typename gyroscope<TIME>::state_type& i) 
    {
        os << "gyroscope raw readings:" << " x: " << i.gyro[0] << " y: " << i.gyro[1] << " z: " << i.gyro[2] << "\n";
        std::cout << "gyroscope raw readings:" << " x: " << i.gyro[0] << " y: " << i.gyro[1] << " z: " << i.gyro[2] << "\n";
        
        return os;
    }
};

#endif