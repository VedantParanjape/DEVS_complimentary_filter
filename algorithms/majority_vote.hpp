#ifndef __MAJORITY_VOTE_HPP__
#define __MAJORITY_VOTE_HPP__

#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdint>

std::vector<std::vector<float>> majority_vote_algorithm(std::vector<std::vector<float>>& accel, std::vector<std::vector<float>>& gyro)
{
    return {accel[0], gyro[0]};
}
#endif
