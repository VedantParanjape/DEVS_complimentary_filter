#ifndef __MAJORITY_VOTE_HPP__
#define __MAJORITY_VOTE_HPP__

#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdint>

const float threshold = 0.5;

float majortiy_vote_algorithm_helper(std::vector<float> data)
{
    float maj_index = 0;
    int count = 1;

    for (int i = 0; i < data.size(); i++)
    {
        if (std::fabs(data[maj_index] - data[i]) <= threshold)
        {
            count++;
        }
        else if (count == 0)
        {
            maj_index = i;
            count = 1;
        }
        else
        {
            count--;
        }
    }

    count = 0;
    float majority_reading = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (std::fabs(data[maj_index] - data[i]) <= threshold)
        {
            count++;
        }
    }
    
    if (count > data.size() / 2)
    {
        majority_reading = data[maj_index];
    }
    else
    {
        for (auto &i: data) majority_reading += i;
        majority_reading = majority_reading / data.size();
    }

    return majority_reading;
}

std::vector<float> extract_readings(std::vector<std::vector<float>> &data, int index)
{
    std::vector<float> return_vector;
    for (int i = 0; i < data.size(); i++)
    {
        return_vector.push_back(data[i][index]);
    }

    return return_vector;
}

std::vector<std::vector<float>> majority_vote_algorithm(std::vector<std::vector<float>>& accel, std::vector<std::vector<float>>& gyro)
{
    /**
     * accel - {
     *     1{x, y, z},
     *     2{x, y, z},
     *     3{x, y, z},
     *     4{x, y, z},
     *     5{x, y, z}
     * }
     * 
     * gyro - {
     *     1{x, y, z},
     *     2{x, y, z},
     *     3{x, y, z},
     *     4{x, y, z},
     *     5{x, y, z}
     * }
     */
    
    float acc_x = majortiy_vote_algorithm_helper(extract_readings(accel, 0));
    float acc_y = majortiy_vote_algorithm_helper(extract_readings(accel, 1));
    float acc_z = majortiy_vote_algorithm_helper(extract_readings(accel, 2));
    float gyro_x = majortiy_vote_algorithm_helper(extract_readings(gyro, 0));
    float gyro_y = majortiy_vote_algorithm_helper(extract_readings(gyro, 1));
    float gyro_z = majortiy_vote_algorithm_helper(extract_readings(gyro, 2));

    return {{acc_x, acc_y, acc_z}, {gyro_x, gyro_y, gyro_z}};
}

#endif
