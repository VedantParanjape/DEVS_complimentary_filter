
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
#include <NDTime.hpp>

#include "complimentary_filter.hpp"
#include "accelerometer.hpp"
#include "fusion_controller.hpp"
#include "gyroscope.hpp"
#include "imu_controller.hpp"

using namespace std;
using TIME = NDTime;

int main()
{
    //to measure simulation execution time
    auto start = chrono::high_resolution_clock::now();

    // loggers
    static std::ofstream out_data("SensorFusion_Cadmium_output.txt");
    struct oss_sink_provider
    {
        static std::ostream &sink()
        {
            return out_data;
        }
    };

    using info = cadmium::logger::logger<cadmium::logger::logger_info, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
    using debug = cadmium::logger::logger<cadmium::logger::logger_debug, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
    using state = cadmium::logger::logger<cadmium::logger::logger_state, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
    using log_messages = cadmium::logger::logger<cadmium::logger::logger_messages, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
    using routing = cadmium::logger::logger<cadmium::logger::logger_message_routing, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
    using global_time = cadmium::logger::logger<cadmium::logger::logger_global_time, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
    using local_time = cadmium::logger::logger<cadmium::logger::logger_local_time, cadmium::dynamic::logger::formatter<TIME>, oss_sink_provider>;
    using log_all = cadmium::logger::multilogger<info, debug, state, log_messages, routing, global_time, local_time>;
    using logger_top = cadmium::logger::multilogger<log_messages, global_time>;

    using AtomicModelPtr = std::shared_ptr<cadmium::dynamic::modeling::model>;
    using CoupledModelPtr = std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>>;

    AtomicModelPtr accelerometer_model = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_0");
    AtomicModelPtr gyroscope_model = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_0");
    AtomicModelPtr imu_controller_model = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_0");
    AtomicModelPtr fusion_controller_model = cadmium::dynamic::translate::make_dynamic_atomic_model<fusion_controller, TIME>("fusion_controller_0");

    return 0;
}