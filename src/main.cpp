
#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>

#include <cadmium/modeling/coupling.hpp>
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/concept/coupled_model_assert.hpp>
#include <cadmium/modeling/dynamic_coupled.hpp>
#include <cadmium/modeling/dynamic_atomic.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/tuple_to_ostream.hpp>
#include <cadmium/logger/common_loggers.hpp>
#include <cadmium/io/iestream.hpp>

#include <algorithm/complimentary_filter.hpp>
#include <atomic_model/accelerometer.hpp>
#include <atomic_model/fusion_controller.hpp>
#include <atomic_model/gyroscope.hpp>
#include <atomic_model/imu_controller.hpp>

int main()
{
    std::cout << "Hello world\n";

    return 0;
}