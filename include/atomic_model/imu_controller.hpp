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
};

// typedef struct imu_controller_state_
// {

// } imu_controller_state;

#endif