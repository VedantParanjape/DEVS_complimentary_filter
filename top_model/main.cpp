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

#include "complimentary_filter.hpp"
#include "fusion_controller.hpp"
#include "imu_controller.hpp"
#include "majority_vote_controller.hpp"
#include "message.hpp"

using namespace std;
using TIME = NDTime;

#if !defined(RT_ARM_MBED)
const char *input_acc_x[5] = {"./inputs/accelerometer_x_1.txt", "./inputs/accelerometer_x_2.txt", "./inputs/accelerometer_x_3.txt", "./inputs/accelerometer_x_4.txt", "./inputs/accelerometer_x_5.txt"};
const char *input_acc_y[5] = {"./inputs/accelerometer_y_1.txt", "./inputs/accelerometer_y_2.txt", "./inputs/accelerometer_y_3.txt", "./inputs/accelerometer_y_4.txt", "./inputs/accelerometer_y_5.txt"};
const char *input_acc_z[5] = {"./inputs/accelerometer_z_1.txt", "./inputs/accelerometer_z_2.txt", "./inputs/accelerometer_z_3.txt", "./inputs/accelerometer_z_4.txt", "./inputs/accelerometer_z_5.txt"};
const char *input_gyro_x[5] = {"./inputs/gyroscope_x_1.txt", "./inputs/gyroscope_x_2.txt", "./inputs/gyroscope_x_3.txt", "./inputs/gyroscope_x_4.txt", "./inputs/gyroscope_x_5.txt"};
const char *input_gyro_y[5] = {"./inputs/gyroscope_y_1.txt", "./inputs/gyroscope_y_2.txt", "./inputs/gyroscope_y_3.txt", "./inputs/gyroscope_y_4.txt", "./inputs/gyroscope_y_5.txt"};
const char *input_gyro_z[5] = {"./inputs/gyroscope_z_1.txt", "./inputs/gyroscope_z_2.txt", "./inputs/gyroscope_z_3.txt", "./inputs/gyroscope_z_4.txt", "./inputs/gyroscope_z_5.txt"};

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
    AtomicModelPtr accelerometer_model_x_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_x_0", input_acc_x[0]);
    AtomicModelPtr accelerometer_model_y_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_y_0", input_acc_y[0]);
    AtomicModelPtr accelerometer_model_z_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_z_0", input_acc_z[0]);
    AtomicModelPtr gyroscope_model_x_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_x_0", input_gyro_x[0]);
    AtomicModelPtr gyroscope_model_y_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_y_0", input_gyro_y[0]);
    AtomicModelPtr gyroscope_model_z_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_z_0", input_gyro_z[0]);
    AtomicModelPtr accelerometer_model_x_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_x_1", input_acc_x[1]);
    AtomicModelPtr accelerometer_model_y_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_y_1", input_acc_y[1]);
    AtomicModelPtr accelerometer_model_z_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_z_1", input_acc_z[1]);
    AtomicModelPtr gyroscope_model_x_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_x_1", input_gyro_x[1]);
    AtomicModelPtr gyroscope_model_y_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_y_1", input_gyro_y[1]);
    AtomicModelPtr gyroscope_model_z_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_z_1", input_gyro_z[1]);
    AtomicModelPtr accelerometer_model_x_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_x_2", input_acc_x[2]);
    AtomicModelPtr accelerometer_model_y_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_y_2", input_acc_y[2]);
    AtomicModelPtr accelerometer_model_z_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_z_2", input_acc_z[2]);
    AtomicModelPtr gyroscope_model_x_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_x_2", input_gyro_x[2]);
    AtomicModelPtr gyroscope_model_y_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_y_2", input_gyro_y[2]);
    AtomicModelPtr gyroscope_model_z_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_z_2", input_gyro_z[2]);
    AtomicModelPtr accelerometer_model_x_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_x_3", input_acc_x[3]);
    AtomicModelPtr accelerometer_model_y_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_y_3", input_acc_y[3]);
    AtomicModelPtr accelerometer_model_z_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_z_3", input_acc_z[3]);
    AtomicModelPtr gyroscope_model_x_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_x_3", input_gyro_x[3]);
    AtomicModelPtr gyroscope_model_y_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_y_3", input_gyro_y[3]);
    AtomicModelPtr gyroscope_model_z_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_z_3", input_gyro_z[3]);
    AtomicModelPtr accelerometer_model_x_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_x_4", input_acc_x[4]);
    AtomicModelPtr accelerometer_model_y_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_y_4", input_acc_y[4]);
    AtomicModelPtr accelerometer_model_z_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("accel_z_4", input_acc_z[4]);
    AtomicModelPtr gyroscope_model_x_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_x_4", input_gyro_x[4]);
    AtomicModelPtr gyroscope_model_y_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_y_4", input_gyro_y[4]);
    AtomicModelPtr gyroscope_model_z_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<InputReader, TIME>("gyro_z_4", input_gyro_z[4]);
#else    
    AtomicModelPtr accelerometer_model_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_0", PB_9, PB_8);
    AtomicModelPtr gyroscope_model_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_0", PB_9, PB_8);
    AtomicModelPtr accelerometer_model_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_1", PB_3, PB_10);
    AtomicModelPtr gyroscope_model_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_1", PB_3, PB_10);
    AtomicModelPtr accelerometer_model_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_2", PB_4, PB_8);
    AtomicModelPtr gyroscope_model_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_2", PB_4, PB_8);
    AtomicModelPtr accelerometer_model_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_3", PA_5, PA_6);
    AtomicModelPtr gyroscope_model_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_3", PA_5, PA_6);
    AtomicModelPtr accelerometer_model_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_4", PA_2, PA_3);
    AtomicModelPtr gyroscope_model_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_4", PA_2, PA_3);
#endif

    AtomicModelPtr imu_controller_model_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_0");
    AtomicModelPtr imu_controller_model_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_1");
    AtomicModelPtr imu_controller_model_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_2");
    AtomicModelPtr imu_controller_model_3 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_3");
    AtomicModelPtr imu_controller_model_4 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_4");
    AtomicModelPtr majority_vote_model = cadmium::dynamic::translate::make_dynamic_atomic_model<majority_vote_controller, TIME>("majority_vote_controller_0");
    AtomicModelPtr fusion_controller_model = cadmium::dynamic::translate::make_dynamic_atomic_model<fusion_controller, TIME>("fusion_controller_0");

    cadmium::dynamic::modeling::Ports iports_TOP = {};
    cadmium::dynamic::modeling::Ports oports_TOP = {};

#if !defined(RT_ARM_MBED)
    cadmium::dynamic::modeling::Models submodels_TOP = {accelerometer_model_x_0, accelerometer_model_y_0, accelerometer_model_z_0, 
                                                        accelerometer_model_x_1, accelerometer_model_y_1, accelerometer_model_z_1,
                                                        accelerometer_model_x_2, accelerometer_model_y_2, accelerometer_model_z_2,
                                                        accelerometer_model_x_3, accelerometer_model_y_3, accelerometer_model_z_3,
                                                        accelerometer_model_x_4, accelerometer_model_y_4, accelerometer_model_z_4,
                                                        gyroscope_model_x_0, gyroscope_model_y_0, gyroscope_model_z_0,
                                                        gyroscope_model_x_1, gyroscope_model_y_1, gyroscope_model_z_1,
                                                        gyroscope_model_x_2, gyroscope_model_y_2, gyroscope_model_z_2,
                                                        gyroscope_model_x_3, gyroscope_model_y_3, gyroscope_model_z_3,
                                                        gyroscope_model_x_4, gyroscope_model_y_4, gyroscope_model_z_4,
                                                        imu_controller_model_0, imu_controller_model_1, imu_controller_model_2, imu_controller_model_3, imu_controller_model_4,
                                                        majority_vote_model, fusion_controller_model};
#else
    cadmium::dynamic::modeling::Models submodels_TOP = {accelerometer_model_0, accelerometer_model_1, accelerometer_model_2, accelerometer_model_3, accelerometer_model_4,
                                                        gyroscope_model_0, gyroscope_model_1, gyroscope_model_2, gyroscope_model_3, gyroscope_model_4,
                                                        imu_controller_model_0, imu_controller_model_1, imu_controller_model_2, imu_controller_model_3, imu_controller_model_4,
                                                        majority_vote_model, fusion_controller_model};
#endif

    cadmium::dynamic::modeling::EICs eics_TOP = {};
    cadmium::dynamic::modeling::EOCs eocs_TOP = {};

    cadmium::dynamic::modeling::ICs ics_TOP = {
#if !defined(RT_ARM_MBED)
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_x>("accel_x_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_y>("accel_y_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_z>("accel_z_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_x>("gyro_x_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_y>("gyro_y_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_z>("gyro_z_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_x>("accel_x_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_y>("accel_y_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_z>("accel_z_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_x>("gyro_x_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_y>("gyro_y_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_z>("gyro_z_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_x>("accel_x_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_y>("accel_y_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_z>("accel_z_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_x>("gyro_x_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_y>("gyro_y_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_z>("gyro_z_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_x>("accel_x_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_y>("accel_y_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_z>("accel_z_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_x>("gyro_x_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_y>("gyro_y_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_z>("gyro_z_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_x>("accel_x_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_y>("accel_y_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_acc_z>("accel_z_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_x>("gyro_x_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_y>("gyro_y_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<iestream_input_defs<float>::out, imu_controller_ports::in_gyro_z>("gyro_z_4", "imu_controller_4"),
#else
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_x, imu_controller_ports::in_acc_x>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_y, imu_controller_ports::in_acc_y>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_z, imu_controller_ports::in_acc_z>("accelerometer_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_x, imu_controller_ports::in_gyro_x>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_y, imu_controller_ports::in_gyro_y>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_z, imu_controller_ports::in_gyro_z>("gyroscope_0", "imu_controller_0"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_x, imu_controller_ports::in_acc_x>("accelerometer_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_y, imu_controller_ports::in_acc_y>("accelerometer_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_z, imu_controller_ports::in_acc_z>("accelerometer_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_x, imu_controller_ports::in_gyro_x>("gyroscope_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_y, imu_controller_ports::in_gyro_y>("gyroscope_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_z, imu_controller_ports::in_gyro_z>("gyroscope_1", "imu_controller_1"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_x, imu_controller_ports::in_acc_x>("accelerometer_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_y, imu_controller_ports::in_acc_y>("accelerometer_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_z, imu_controller_ports::in_acc_z>("accelerometer_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_x, imu_controller_ports::in_gyro_x>("gyroscope_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_y, imu_controller_ports::in_gyro_y>("gyroscope_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_z, imu_controller_ports::in_gyro_z>("gyroscope_2", "imu_controller_2"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_x, imu_controller_ports::in_acc_x>("accelerometer_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_y, imu_controller_ports::in_acc_y>("accelerometer_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_z, imu_controller_ports::in_acc_z>("accelerometer_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_x, imu_controller_ports::in_gyro_x>("gyroscope_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_y, imu_controller_ports::in_gyro_y>("gyroscope_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_z, imu_controller_ports::in_gyro_z>("gyroscope_3", "imu_controller_3"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_x, imu_controller_ports::in_acc_x>("accelerometer_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_y, imu_controller_ports::in_acc_y>("accelerometer_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<accelerometer_ports::out_z, imu_controller_ports::in_acc_z>("accelerometer_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_x, imu_controller_ports::in_gyro_x>("gyroscope_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_y, imu_controller_ports::in_gyro_y>("gyroscope_4", "imu_controller_4"),
        cadmium::dynamic::translate::make_IC<gyroscope_ports::out_z, imu_controller_ports::in_gyro_z>("gyroscope_4", "imu_controller_4"),
#endif  
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_1>("imu_controller_0", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_1>("imu_controller_0", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_2>("imu_controller_1", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_2>("imu_controller_1", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_3>("imu_controller_2", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_3>("imu_controller_2", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_4>("imu_controller_3", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_4>("imu_controller_3", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_5>("imu_controller_4", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_5>("imu_controller_4", "majority_vote_controller_0"),

        cadmium::dynamic::translate::make_IC<majority_vote_controller_ports::out_accel, fusion_controller_ports::in_accel>("majority_vote_controller_0", "fusion_controller_0"),
        cadmium::dynamic::translate::make_IC<majority_vote_controller_ports::out_gyro, fusion_controller_ports::in_gyro>("majority_vote_controller_0", "fusion_controller_0"),
        cadmium::dynamic::translate::make_IC<majority_vote_controller_ports::out_offset, fusion_controller_ports::in_offset>("majority_vote_controller_0", "fusion_controller_0"),
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