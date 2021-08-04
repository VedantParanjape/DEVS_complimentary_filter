#ifndef __ACCELEROMETER_HPP__
#define __ACCELEROMETER_HPP__

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
struct accelerometer_ports
{
    struct out_x : public out_port<float> {};
    struct out_y : public out_port<float> {};
    struct out_z : public out_port<float> {};
};

template <typename TIME>
class accelerometer
{
private:
    TIME refresh_rate;
    IMU imu_driver;
    MPU6050 *accel;

public:
    using input_ports = tuple<>;
    using output_ports = tuple<typename accelerometer_ports::out_x, typename accelerometer_ports::out_y, typename accelerometer_ports::out_z>;
    
    // default constructor
    accelerometer(PinName sda, PinName scl) noexcept
    {
        refresh_rate = TIME("00:00:00:300");
        accel = imu_driver.init(sda, scl);
    }

    // parameterized constructor
    accelerometer(TIME refresh_rate_sensor, PinName sda, PinName scl)
    {
        refresh_rate = refresh_rate_sensor;
        accel = imu_driver.init(sda, scl);
    }

    struct state_type
    {
        std::vector<float> accel;
    }; 
    state_type state;

    // internal transition function
    void internal_transition()
    {
        float readings[3];
        accel->getAccelero(readings);
        state.accel = {readings[0], readings[1], readings[2]};
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

        get_messages<typename accelerometer_ports::out_x>(bags).push_back(state.accel[0]);
        get_messages<typename accelerometer_ports::out_y>(bags).push_back(state.accel[1]);
        get_messages<typename accelerometer_ports::out_z>(bags).push_back(state.accel[2]);

        return bags;
    }

    // time advance function
    TIME time_advance() const
    {
        return refresh_rate;
    }

    friend ostringstream& operator<<(ostringstream& os, const typename accelerometer<TIME>::state_type& i) 
    {        
#if defined(RT_ARM_MBED)
        // printf("accelerometer raw readings: x:%f y:%f z:%f\n", i.accel[0], i.accel[1], i.accel[2]);
#else
        os << "accelerometer raw readings:" << " x: " << i.accel[0] << " y: " << i.accel[1] << " z: " << i.accel[2] << "\n";
#endif
        return os;
    }
};

#endif