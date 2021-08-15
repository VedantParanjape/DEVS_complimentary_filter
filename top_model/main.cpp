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

#include <cadmium/real_time/arm_mbed/rt_clock.hpp>

#include "../mbed.h"
#include "gyroscope.hpp"
#include "accelerometer.hpp"

#include "complimentary_filter.hpp"
#include "fusion_controller.hpp"
#include "imu_controller.hpp"
#include "majority_vote_controller.hpp"
#include "message.hpp"

using namespace std;
using TIME = NDTime;

int main()
{
    // to measure simulation execution time
    auto start = chrono::high_resolution_clock::now();

    using AtomicModelPtr = std::shared_ptr<cadmium::dynamic::modeling::model>;
    using CoupledModelPtr = std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>>;

    AtomicModelPtr accelerometer_model_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_0", D14, D15, 0);
    AtomicModelPtr gyroscope_model_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_0", D14, D15, 0);
    AtomicModelPtr accelerometer_model_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_1", D3, D6, 1);
    AtomicModelPtr gyroscope_model_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_1", D3, D6, 1);
    AtomicModelPtr accelerometer_model_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<accelerometer, TIME>("accelerometer_2", D5, D7, 2);
    AtomicModelPtr gyroscope_model_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<gyroscope, TIME>("gyroscope_2", D5, D7, 2);

    AtomicModelPtr imu_controller_model_0 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_0");
    AtomicModelPtr imu_controller_model_1 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_1");
    AtomicModelPtr imu_controller_model_2 = cadmium::dynamic::translate::make_dynamic_atomic_model<imu_controller, TIME>("imu_controller_2");
    AtomicModelPtr majority_vote_model = cadmium::dynamic::translate::make_dynamic_atomic_model<majority_vote_controller, TIME>("majority_vote_controller_0");
    AtomicModelPtr fusion_controller_model = cadmium::dynamic::translate::make_dynamic_atomic_model<fusion_controller, TIME>("fusion_controller_0");

    cadmium::dynamic::modeling::Ports iports_TOP = {};
    cadmium::dynamic::modeling::Ports oports_TOP = {};

    cadmium::dynamic::modeling::Models submodels_TOP = {accelerometer_model_0, accelerometer_model_1, accelerometer_model_2,
                                                        gyroscope_model_0, gyroscope_model_1, gyroscope_model_2,
                                                        imu_controller_model_0, imu_controller_model_1, imu_controller_model_2,
                                                        majority_vote_model, fusion_controller_model};
    cadmium::dynamic::modeling::EICs eics_TOP = {};
    cadmium::dynamic::modeling::EOCs eocs_TOP = {};

    cadmium::dynamic::modeling::ICs ics_TOP = {
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
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_1>("imu_controller_0", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_1>("imu_controller_0", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_2>("imu_controller_1", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_2>("imu_controller_1", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_accel, majority_vote_controller_ports::in_accel_3>("imu_controller_2", "majority_vote_controller_0"),
        cadmium::dynamic::translate::make_IC<imu_controller_ports::out_gyro, majority_vote_controller_ports::in_gyro_3>("imu_controller_2", "majority_vote_controller_0"),

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

    cadmium::dynamic::engine::runner<NDTime, cadmium::logger::not_logger> run(TOP, NDTime("00:00:00"));

    run.run_until_passivate();

    return 0;
}   

// #include "mbed.h"
// #include "MPU6050.h"
// #include "driver.hpp"

// int main()
// {
//     IMU imu_driver;
//     MPU6050 *imu1 = imu_driver.init(D14, D15);
//     MPU6050 *imu2 = imu_driver.init(D3, D6);
//     MPU6050 *imu3 = imu_driver.init(D5, D7);
//     while(1)
//     {
//         float readings[3];

//         std::cout << imu1->testConnection() << " " << imu2->testConnection() << " " << imu3->testConnection() << std::endl;
//         imu1->getGyro(readings);
//         std::cout << readings[0] << " " << readings[1] << " " << readings[2] << std::endl;
//         imu2->getGyro(readings);
//         std::cout << readings[0] << " " << readings[1] << " " << readings[2] << std::endl;
//         imu3->getGyro(readings);
//         std::cout << readings[0] << " " << readings[1] << " " << readings[2] << std::endl;

//         wait_us(1000 * 1000);
//     }
// }