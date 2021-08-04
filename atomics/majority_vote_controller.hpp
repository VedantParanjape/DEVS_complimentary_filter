#ifndef __MAJORITY_VOTE_CONTROLLER_HPP__
#define __MAJORITY_VOTE_CONTROLLER_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include "majority_vote.hpp"
#include "message.hpp"

#include <assert.h>
#include <string>
#include <random>
#include <limits>

using namespace cadmium;
using namespace std;

struct majority_vote_controller_ports
{
    struct in_accel_1 : public in_port<cartesian_vector> {};
    struct in_gyro_1 : public in_port<cartesian_vector> {};

    struct in_accel_2 : public in_port<cartesian_vector> {};
    struct in_gyro_2 : public in_port<cartesian_vector> {};

    struct in_accel_3 : public in_port<cartesian_vector> {};
    struct in_gyro_3 : public in_port<cartesian_vector> {};

    struct out_gyro : public out_port<cartesian_vector> {};
    struct out_accel : public out_port<cartesian_vector> {};
    struct out_offset : public out_port<cartesian_vector> {};
};

template <typename TIME>
class majority_vote_controller
{
public:
    using input_ports = tuple<typename majority_vote_controller_ports::in_accel_1, typename majority_vote_controller_ports::in_gyro_1,
                                typename majority_vote_controller_ports::in_accel_2, typename majority_vote_controller_ports::in_gyro_2,
                                  typename majority_vote_controller_ports::in_accel_3, typename majority_vote_controller_ports::in_gyro_3>;

    using output_ports = tuple<typename majority_vote_controller_ports::out_gyro, 
                                typename majority_vote_controller_ports::out_accel, 
                                 typename majority_vote_controller_ports::out_offset>;

    majority_vote_controller() noexcept
    {
        state.accel_readings_vote = std::vector<float> (3);
        state.gyro_readings_vote = std::vector<float> (3);
        state.imu_offsets_vote = std::vector<float> (3);

        state.active = false;
    }

    struct state_type
    {
        std::vector<float> accel_readings_vote;
        std::vector<float> gyro_readings_vote;
        std::vector<float> imu_offsets_vote;
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
        std::vector<vector<float>> in_accel_array(3);
        std::vector<vector<float>> in_gyro_array(3);

        for (const auto &x : get_messages<typename majority_vote_controller_ports::in_accel_1>(mbs))
        {
            in_accel_array[0] = x.data;
        }
        for (const auto &x : get_messages<typename majority_vote_controller_ports::in_gyro_1>(mbs))
        {
            in_gyro_array[0] = x.data;
        }
        for (const auto &x : get_messages<typename majority_vote_controller_ports::in_accel_2>(mbs))
        {
            in_accel_array[1] = x.data;
        }
        for (const auto &x : get_messages<typename majority_vote_controller_ports::in_gyro_2>(mbs))
        {
            in_gyro_array[1] = x.data;
        }
        for (const auto &x : get_messages<typename majority_vote_controller_ports::in_accel_3>(mbs))
        {
            in_accel_array[2] = x.data;
        }
        for (const auto &x : get_messages<typename majority_vote_controller_ports::in_gyro_3>(mbs))
        {
            in_gyro_array[2] = x.data;
        }
        std::vector<std::vector<float>> majority_vote_output = majority_vote_algorithm(in_accel_array, in_gyro_array);

        state.accel_readings_vote = majority_vote_output[0];
        state.gyro_readings_vote = majority_vote_output[1];
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
        
        get_messages<typename majority_vote_controller_ports::out_accel>(bags).push_back(cartesian_vector(state.accel_readings_vote));
        get_messages<typename majority_vote_controller_ports::out_gyro>(bags).push_back(cartesian_vector(state.gyro_readings_vote));
        get_messages<typename majority_vote_controller_ports::out_offset>(bags).push_back(cartesian_vector(state.imu_offsets_vote));

        return bags;
    }

    // time_advance function
    TIME time_advance() const 
    {
        return state.active ? TIME("00:00:00:00") : std::numeric_limits<TIME>::infinity();
    }

    friend ostringstream& operator<<(ostringstream& os, const typename majority_vote_controller<TIME>::state_type& i) 
    {
#if defined(RT_ARM_MBED)        
        // printf("accelerometer: x:%f y:%f z:%f\n", i.accel_readings_vote[0], i.accel_readings_vote[1], i.accel_readings_vote[2]);
        // printf("gyroscope: x:%f y:%f z:%f\n", i.gyro_readings_vote[0], i.gyro_readings_vote[1], i.gyro_readings_vote[2]);
        // printf("IMU offset: x:%f y:%f z:%f\n", i.imu_offsets_vote[0], i.imu_offsets_vote[1], i.imu_offsets_vote[2]);
#else
        os << "\n";
        os << "accelerometer:" << " x: " << i.accel_readings_vote[0] << " y: " << i.accel_readings_vote[1] << " z: " << i.accel_readings_vote[2] << "\n";
        os << "gyroscope:" << " x: " << i.gyro_readings_vote[0] << " y: " << i.gyro_readings_vote[1] << " z: " << i.gyro_readings_vote[2] << "\n";
        os << "IMU offset:" << " x: " << i.imu_offsets_vote[0] << " y: " << i.imu_offsets_vote[1] << " z: " << i.imu_offsets_vote[2] << "\n";
#endif
        return os;
    }
};

#endif