#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include "MPU6050/MPU6050.h"
#include <assert.h>
#include <vector>
#include <utility>

class IMU
{
    private:
        inline static std::vector<MPU6050*> sensor_array;
        inline static std::vector<std::pair<PinName, PinName>> sensor_pin_array;
    public:
        MPU6050* init(PinName sda, PinName scl)
        {
            int flag = -1;
            for (unsigned int i = 0; i < sensor_pin_array.size(); i++)
            {
                std::pair<PinName, PinName> temp(sda, scl);
                if (sensor_pin_array[i] == temp)
                {
                    flag = i;
                    break;
                }
            }

            if (flag == -1)
            {
                std::pair<PinName, PinName> pins(sda, scl);
                MPU6050 *sensor = new MPU6050(sda, scl);
                sensor_pin_array.push_back(pins);
                sensor_array.emplace_back(sensor);
                flag = sensor_array.size() - 1;
            }

            return sensor_array[flag];
        }
};

#endif