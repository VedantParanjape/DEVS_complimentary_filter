
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

const char *input_1 = "./inputs/accelerometer.txt";
const char *input_2 = "./inputs/gyroscope.txt";

int main()
{
    // to measure simulation execution time
    auto start = chrono::high_resolution_clock::now();

    // loggers
    static std::ofstream out_data("./outputs/SensorFusion_Cadmium_output.txt");
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

    cadmium::dynamic::modeling::Ports iports_TOP = {};
    cadmium::dynamic::modeling::Ports oports_TOP = {};

    cadmium::dynamic::modeling::Models submodels_TOP = {accelerometer_model, gyroscope_model, imu_controller_model, fusion_controller_model};

    cadmium::dynamic::modeling::EICs eics_TOP = {};
    cadmium::dynamic::modeling::EOCs eocs_TOP = {};

    cadmium::dynamic::modeling::ICs ics_TOP = {
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_x, imu_controller_ports::in_acc_x>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_y, imu_controller_ports::in_acc_y>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_z, imu_controller_ports::in_acc_z>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_x, imu_controller_ports::in_gyro_x>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_y, imu_controller_ports::in_gyro_y>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_z, imu_controller_ports::in_gyro_z>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, fusion_controller_ports::in_accel>("imu_controller_0", "fusion_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, fusion_controller_ports::in_gyro>("imu_controller_0", "fusion_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_offset, fusion_controller_ports::in_offset>("imu_controller_0", "fusion_controller_0"),
    };

    CoupledModelPtr TOP = std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>(
        "TOP",
        submodels_TOP,
        iports_TOP,
        oports_TOP,
        eics_TOP,
        eocs_TOP,
        ics_TOP);

    std::cout << "here\n";
    cadmium::dynamic::engine::runner<NDTime, log_all> run(TOP, {0});
    run.run_until(NDTime("00:10:00:000"));

    return 0;
}