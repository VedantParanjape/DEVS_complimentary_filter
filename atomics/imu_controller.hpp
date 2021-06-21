#ifndef __IMU_CONTROLLER_HPP__
#define __IMU_CONTROLLER_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <assert.h>
#include <string>
#include <random>
#include <limits>

using namespace cadmium;
using namespace std;

struct imu_controller_ports
{
    struct in_acc_x : public in_port<float> {};
    struct in_acc_y : public in_port<float> {};
    struct in_acc_z : public in_port<float> {};

    struct in_gyro_x : public in_port<float> {};
    struct in_gyro_y : public in_port<float> {};
    struct in_gyro_z : public in_port<float> {};

    struct out_gyro : public out_port<std::vector<float>> {};
    struct out_accel : public out_port<std::vector<float>> {};
    struct out_offset : public out_port<std::vector<float>> {};
};

template <typename TIME>
class imu_controller
{
public:
    using input_ports = tuple<typename imu_controller_ports::in_acc_x, typename imu_controller_ports::in_acc_y,
                                typename imu_controller_ports::in_acc_z, typename imu_controller_ports::in_gyro_x,
                                  typename imu_controller_ports::in_gyro_y, typename imu_controller_ports::in_gyro_z>;
    using output_ports = tuple<typename imu_controller_ports::out_gyro, typename imu_controller_ports::out_accel, typename imu_controller_ports::out_offset>;

    imu_controller() noexcept
    {
        state.accel_readings = std::vector<float> (3);
        state.gyro_readings = std::vector<float> (3);
        state.imu_offsets = std::vector<float> (3);

        state.active = false;
    }

    struct state_type
    {
        std::vector<float> accel_readings;
        std::vector<float> gyro_readings;
        std::vector<float> imu_offsets;
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
        state.accel_readings[0] = get_messages<typename imu_controller_ports::in_acc_x>(mbs)[0];
        state.accel_readings[1] = get_messages<typename imu_controller_ports::in_acc_y>(mbs)[0];
        state.accel_readings[2] = get_messages<typename imu_controller_ports::in_acc_z>(mbs)[0];

        state.gyro_readings[0] = get_messages<typename imu_controller_ports::in_gyro_x>(mbs)[0];
        state.gyro_readings[1] = get_messages<typename imu_controller_ports::in_gyro_y>(mbs)[0];
        state.gyro_readings[2] = get_messages<typename imu_controller_ports::in_gyro_z>(mbs)[0];

        state.active = true;
    }

    // confluent transition function
    void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs)
    {
        internal_transition();
        external_transition(TIME(), std::move(mbs));
    }

    // output function
    typename make_message_bags<output_ports>::type output() const 
    {
        typename make_message_bags<output_ports>::type bags;
        
        // + TODO: add checking for validity of the data
        get_messages<typename imu_controller_ports::out_accel>(bags).push_back(state.accel_readings);
        get_messages<typename imu_controller_ports::out_gyro>(bags).push_back(state.gyro_readings);
        get_messages<typename imu_controller_ports::out_offset>(bags).push_back(state.imu_offsets);

        return bags;
    }

    // time_advance function
    TIME time_advance() const 
    {
        return state.active ? TIME("00:00:00:100") : std::numeric_limits<TIME>::infinity();
    }

    friend ostringstream& operator<<(ostringstream& os, const typename imu_controller<TIME>::state_type& i) 
    {
        os << "accelerometer:" << " x: " << i.accel_readings[0] << " y: " << i.accel_readings[1] << " z: " << i.accel_readings[2] << "\n";
        os << "gyroscope:" << " x: " << i.gyro_readings[0] << " y: " << i.gyro_readings[1] << " z: " << i.gyro_readings[2] << "\n";
        os << "IMU offset:" << " x: " << i.imu_offsets[0] << " y: " << i.imu_offsets[1] << " z: " << i.imu_offsets[2] << "\n";
        return os;
    }
};

#endif