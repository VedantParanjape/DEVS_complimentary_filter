#ifndef __COMPLIMENTARY_FILTER_HPP__
#define __COMPLIMENTARY_FILTER_HPP__

#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdint>

const double rad_to_degree_coeff = 57.2957795;
static uint64_t prev_time = 0;

uint64_t micros()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

std::vector<float> complimentary_filter(std::vector<float> accel_raw, std::vector<float> gyro_raw, std::vector<float> imu_offset)
{
    std::vector<float> accel_angles (3);
    std::vector<float> gyro_angles (3);
    static std::vector<float> complimentary_angles (3);
    const float alpha = 0.8;

    accel_angles[0] = (atan2(accel_raw[0], sqrt(pow(accel_raw[1], 2) + pow(accel_raw[2], 2))) * rad_to_degree_coeff) - imu_offset[0];
    accel_angles[1] = (atan2(accel_raw[1], sqrt(pow(accel_raw[2], 2) + pow(accel_raw[0], 2))) * rad_to_degree_coeff) - imu_offset[1];
    accel_angles[2] = (atan2(accel_raw[2], sqrt(pow(accel_raw[0], 2) + pow(accel_raw[1], 2))) * rad_to_degree_coeff) - imu_offset[2];

    if (prev_time == 0)
    {
        complimentary_angles[0] = accel_angles[0];
        complimentary_angles[1] = accel_angles[1];
        complimentary_angles[2] = accel_angles[2];

        prev_time = micros();

        return complimentary_angles;
    }

    uint64_t curr_time = micros();
    float dt = (float)(curr_time - prev_time) / 1000000;
    prev_time = curr_time;

    gyro_angles[0] = complimentary_angles[0] + gyro_raw[0] * dt;
    gyro_angles[1] = complimentary_angles[1] + gyro_raw[1] * dt;
    gyro_angles[2] = complimentary_angles[2] + gyro_raw[2] * dt;

    complimentary_angles[0] = alpha * gyro_angles[0] + (1 - alpha) * accel_angles[0];
    complimentary_angles[1] = alpha * gyro_angles[1] + (1 - alpha) * accel_angles[1];
    complimentary_angles[2] = alpha * gyro_angles[2] + (1 - alpha) * accel_angles[2];

    return complimentary_angles;
}

#endif
