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

#if defined(RT_ARM_MBED)
#include <cadmium/real_time/arm_mbed/rt_clock.hpp>
#endif

#if defined(RT_ARM_MBED)
#include "../mbed.h"
#include "gyroscope.hpp"
#include "accelerometer.hpp"
#endif

#if !defined(RT_ARM_MBED)
#include <cadmium/io/iestream.hpp>
#endif

#include <NDTime.hpp>
#include "complimentary_filter.hpp"
#include "fusion_controller.hpp"
#include "imu_controller.hpp"
#include "message.hpp"

using namespace std;
using TIME = NDTime;

#if !defined(RT_ARM_MBED)
const char *input_acc_x = "./inputs/accelerometer_x.txt";
const char *input_acc_y = "./inputs/accelerometer_y.txt";
const char *input_acc_z = "./inputs/accelerometer_z.txt";
const char *input_gyro_x = "./inputs/gyroscope_x.txt";
const char *input_gyro_y = "./inputs/gyroscope_y.txt";
const char *input_gyro_z = "./inputs/gyroscope_z.txt";

template<typename T>
class InputReader : public iestream_input<float, T, iestream_input_defs<float>> 
{
    public:
        InputReader () = default;
        InputReader (const char* file_path) :
        iestream_input<float, T, iestream_input_defs<float>> (file_path) {}
};
#endif

int main()
{
    // to measure simulation execution time
    auto start = chrono::high_resolution_clock::now();

    using AtomicModelPtr = std::shared_ptr<cadmium::dynamic::modeling::model>;
    using CoupledModelPtr = std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>>;

#if !defined(RT_ARM_MBED)
    AtomicModelPtr accelerometer_model_x = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_x", input_acc_x);
    AtomicModelPtr accelerometer_model_y = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_y", input_acc_y);
    AtomicModelPtr accelerometer_model_z = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_z", input_acc_z);
    AtomicModelPtr gyroscope_model_x = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_x", input_gyro_x);
    AtomicModelPtr gyroscope_model_y = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_y", input_gyro_y);
    AtomicModelPtr gyroscope_model_z = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_z", input_gyro_z);
#else    
    AtomicModelPtr accelerometer_model = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_0", p9, p10);
    AtomicModelPtr gyroscope_model = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_0", p9, p10);
#endif

    AtomicModelPtr imu_controller_model = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_0");
    AtomicModelPtr fusion_controller_model = cadmium::dynamic::translate::make_dynamic_atomic_model<fusion_controller, TIME>("fusion_controller_0");

    cadmium::dynamic::modeling::Ports iports_TOP = {};
    cadmium::dynamic::modeling::Ports oports_TOP = {};

#if !defined(RT_ARM_MBED)
    cadmium::dynamic::modeling::Models submodels_TOP = {accelerometer_model_x, accelerometer_model_y, accelerometer_model_z, gyroscope_model_x, gyroscope_model_y, gyroscope_model_z, imu_controller_model, fusion_controller_model};
#else
    cadmium::dynamic::modeling::Models submodels_TOP = {accelerometer_model, gyroscope_model, imu_controller_model, fusion_controller_model};
#endif

    cadmium::dynamic::modeling::EICs eics_TOP = {};
    cadmium::dynamic::modeling::EOCs eocs_TOP = {};

    cadmium::dynamic::modeling::ICs ics_TOP = {
#if !defined(RT_ARM_MBED)
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_x>("accel_x", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_y>("accel_y", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_z>("accel_z", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_x>("gyro_x", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_y>("gyro_y", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_z>("gyro_z", "imu_controller_0"),
#else
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_x, imu_controller_ports::in_acc_x>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_y, imu_controller_ports::in_acc_y>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_z, imu_controller_ports::in_acc_z>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_x, imu_controller_ports::in_gyro_x>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_y, imu_controller_ports::in_gyro_y>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_z, imu_controller_ports::in_gyro_z>("gyroscope_0", "imu_controller_0"),
#endif     
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

    /*************** Loggers *******************/
    static ofstream out_messages("./outputs/DEVS_complimentary_output_messages.txt");
    struct oss_sink_messages{
        static ostream& sink(){          
            return out_messages;
        }
    };
    static ofstream out_state("./outputs/DEVS_complimentary_output_state.txt");
    struct oss_sink_state{
        static ostream& sink(){          
            return out_state;
        }
    };
    
    using state=logger::logger<logger::logger_state, dynamic::logger::formatter<TIME>, oss_sink_state>;
    using log_messages=logger::logger<logger::logger_messages, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_mes=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_sta=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_state>;
    using logger_top=logger::multilogger<state, log_messages, global_time_mes, global_time_sta>;

    cadmium::dynamic::engine::runner<NDTime, logger_top> run(TOP, NDTime("00:00:00"));
    run.run_until(NDTime("00:00:31:300"));

    return 0;
}   