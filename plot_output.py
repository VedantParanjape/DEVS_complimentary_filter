import matplotlib.pyplot as plt
import openpyxl
import math
import numpy as np

workbook = openpyxl.load_workbook(filename="top_model/outputs/simulation_data.xlsx", data_only=True)
sheet = workbook.active

time = []

accel_x_1 = []
accel_y_1 = []
accel_z_1 = []

accel_x_2 = []
accel_y_2 = []
accel_z_2 = []

accel_x_3 = []
accel_y_3 = []
accel_z_3 = []

accel_x_4 = []
accel_y_4 = []
accel_z_4 = []

accel_x_5 = []
accel_y_5 = []
accel_z_5 = []

gyro_x_1 = []
gyro_y_1 = []
gyro_z_1 = []

gyro_x_2 = []
gyro_y_2 = []
gyro_z_2 = []

gyro_x_3 = []
gyro_y_3 = []
gyro_z_3 = []

gyro_x_4 = []
gyro_y_4 = []
gyro_z_4 = []

gyro_x_5 = []
gyro_y_5 = []
gyro_z_5 = []

majority_accel_x = []
majority_accel_y = []
majority_accel_z = []

majority_gyro_x = []
majority_gyro_y = []
majority_gyro_z = []

fused_angle_x = []
fused_angle_y = []
fused_angle_z = []

for row in sheet.iter_rows(min_row=2, values_only=True):
    time.append(row[0])
    accel_x_1.append(float(row[1]))
    accel_y_1.append(float(row[2]))
    accel_z_1.append(float(row[3]))

    accel_x_2.append(float(row[4]))
    accel_y_2.append(float(row[5]))
    accel_z_2.append(float(row[6]))

    accel_x_3.append(float(row[7]))
    accel_y_3.append(float(row[8]))
    accel_z_3.append(float(row[9]))
    
    accel_x_4.append(float(row[10]))
    accel_y_4.append(float(row[11]))
    accel_z_4.append(float(row[12]))

    accel_x_5.append(float(row[13]))
    accel_y_5.append(float(row[14]))
    accel_z_5.append(float(row[15]))

    gyro_x_1.append(float(row[16]))
    gyro_y_1.append(float(row[17]))
    gyro_z_1.append(float(row[18]))

    gyro_x_2.append(float(row[19]))
    gyro_y_2.append(float(row[20]))
    gyro_z_2.append(float(row[21]))

    gyro_x_3.append(float(row[22]))
    gyro_y_3.append(float(row[23]))
    gyro_z_3.append(float(row[24]))

    gyro_x_4.append(float(row[25]))
    gyro_y_4.append(float(row[26]))
    gyro_z_4.append(float(row[27]))

    gyro_x_5.append(float(row[28]))
    gyro_y_5.append(float(row[29]))
    gyro_z_5.append(float(row[30]))

    majority_accel_x.append(float(row[31]))
    majority_accel_y.append(float(row[32]))
    majority_accel_z.append(float(row[33]))

    majority_gyro_x.append(float(row[34]))
    majority_gyro_y.append(float(row[35]))
    majority_gyro_z.append(float(row[36]))

    fused_angle_x.append(float(row[37]))
    fused_angle_y.append(float(row[38]))
    fused_angle_z.append(float(row[39]))

accel_x_1 = np.array(accel_x_1)
accel_y_1 = np.array(accel_y_1)
accel_z_1 = np.array(accel_z_1)
accel_x_2 = np.array(accel_x_2)
accel_y_2 = np.array(accel_y_2)
accel_z_2 = np.array(accel_z_2)
accel_x_3 = np.array(accel_x_3)
accel_y_3 = np.array(accel_y_3)
accel_z_3 = np.array(accel_z_3)
accel_x_4 = np.array(accel_x_4)
accel_y_4 = np.array(accel_y_4)
accel_z_4 = np.array(accel_z_4)
accel_x_5 = np.array(accel_x_5)
accel_y_5 = np.array(accel_y_5)
accel_z_5 = np.array(accel_z_5)

gyro_x_1 = np.array(gyro_x_1)
gyro_y_1 = np.array(gyro_y_1)
gyro_z_1 = np.array(gyro_z_1)
gyro_x_2 = np.array(gyro_x_2)
gyro_y_2 = np.array(gyro_y_2)
gyro_z_2 = np.array(gyro_z_2)
gyro_x_3 = np.array(gyro_x_3)
gyro_y_3 = np.array(gyro_y_3)
gyro_z_3 = np.array(gyro_z_3)
gyro_x_4 = np.array(gyro_x_4)
gyro_y_4 = np.array(gyro_y_4)
gyro_z_4 = np.array(gyro_z_4)
gyro_x_5 = np.array(gyro_x_5)
gyro_y_5 = np.array(gyro_y_5)
gyro_z_5 = np.array(gyro_z_5)

majority_accel_x = np.array(majority_accel_x)
majority_accel_y = np.array(majority_accel_y)
majority_accel_z = np.array(majority_accel_z)

majority_gyro_x = np.array(majority_gyro_x)
majority_gyro_y = np.array(majority_gyro_y)
majority_gyro_z = np.array(majority_gyro_z)

fused_angle_x = np.array(fused_angle_x)
fused_angle_y = np.array(fused_angle_y)
fused_angle_z = np.array(fused_angle_z)

accel_x_1 = np.arctan2(accel_x_1, np.power(np.power(accel_y_1, 2) + np.power(accel_z_1, 2), 0.5))*180/np.math.pi
accel_y_1 = np.arctan2(accel_y_1, np.power(np.power(accel_x_1, 2) + np.power(accel_z_1, 2), 0.5))*180/np.math.pi
accel_z_1 = np.arctan2(accel_z_1, np.power(np.power(accel_y_1, 2) + np.power(accel_x_1, 2), 0.5))*180/np.math.pi

accel_x_2 = np.arctan2(accel_x_2, np.power(np.power(accel_y_2, 2) + np.power(accel_z_2, 2), 0.5))*180/np.math.pi
accel_y_2 = np.arctan2(accel_y_2, np.power(np.power(accel_x_2, 2) + np.power(accel_z_2, 2), 0.5))*180/np.math.pi
accel_z_2 = np.arctan2(accel_z_2, np.power(np.power(accel_y_2, 2) + np.power(accel_x_2, 2), 0.5))*180/np.math.pi

accel_x_3 = np.arctan2(accel_x_3, np.power(np.power(accel_y_3, 2) + np.power(accel_z_3, 2), 0.5))*180/np.math.pi
accel_y_3 = np.arctan2(accel_y_3, np.power(np.power(accel_x_3, 2) + np.power(accel_z_3, 2), 0.5))*180/np.math.pi
accel_z_3 = np.arctan2(accel_z_3, np.power(np.power(accel_y_3, 2) + np.power(accel_x_3, 2), 0.5))*180/np.math.pi

accel_x_4 = np.arctan2(accel_x_4, np.power(np.power(accel_y_4, 2) + np.power(accel_z_4, 2), 0.5))*180/np.math.pi
accel_y_4 = np.arctan2(accel_y_4, np.power(np.power(accel_x_4, 2) + np.power(accel_z_4, 2), 0.5))*180/np.math.pi
accel_z_4 = np.arctan2(accel_z_4, np.power(np.power(accel_y_4, 2) + np.power(accel_x_4, 2), 0.5))*180/np.math.pi

accel_x_5 = np.arctan2(accel_x_5, np.power(np.power(accel_y_5, 2) + np.power(accel_z_5, 2), 0.5))*180/np.math.pi
accel_y_5 = np.arctan2(accel_y_5, np.power(np.power(accel_x_5, 2) + np.power(accel_z_5, 2), 0.5))*180/np.math.pi
accel_z_5 = np.arctan2(accel_z_5, np.power(np.power(accel_y_5, 2) + np.power(accel_x_5, 2), 0.5))*180/np.math.pi

majority_accel_x = np.arctan2(majority_accel_x, np.power(np.power(majority_accel_y, 2) + np.power(majority_accel_z, 2), 0.5))*180/np.math.pi
majority_accel_y = np.arctan2(majority_accel_y, np.power(np.power(majority_accel_x, 2) + np.power(majority_accel_z, 2), 0.5))*180/np.math.pi
majority_accel_z = np.arctan2(majority_accel_z, np.power(np.power(majority_accel_x, 2) + np.power(majority_accel_y, 2), 0.5))*180/np.math.pi

gyro_x_1[0] = accel_x_1[0]
gyro_y_1[0] = accel_y_1[0]
gyro_z_1[0] = accel_z_1[0]

gyro_x_2[0] = accel_x_2[0]
gyro_y_2[0] = accel_y_2[0]
gyro_z_2[0] = accel_z_2[0]

gyro_x_3[0] = accel_x_3[0]
gyro_y_3[0] = accel_y_3[0]
gyro_z_3[0] = accel_z_3[0]

gyro_x_4[0] = accel_x_4[0]
gyro_y_4[0] = accel_y_4[0]
gyro_z_4[0] = accel_z_4[0]

gyro_x_5[0] = accel_x_5[0]
gyro_y_5[0] = accel_y_5[0]
gyro_z_5[0] = accel_z_5[0]

majority_gyro_x[0] = majority_accel_x[0]
majority_gyro_y[0] = majority_accel_y[0]
majority_gyro_z[0] = majority_accel_z[0]

sum = 0
gyro_x_1 = np.array([sum := sum + gyro_x_1[i]*0.01 for i in range(len(gyro_x_1))])
sum = 0
gyro_y_1 = np.array([sum := sum + gyro_y_1[i]*0.01 for i in range(len(gyro_y_1))])
sum = 0
gyro_z_1 = np.array([sum := sum + gyro_z_1[i]*0.01 for i in range(len(gyro_z_1))])

sum = 0
gyro_x_2 = np.array([sum := sum + gyro_x_2[i]*0.01 for i in range(len(gyro_x_2))])
sum = 0
gyro_y_2 = np.array([sum := sum + gyro_y_2[i]*0.01 for i in range(len(gyro_y_2))])
sum = 0
gyro_z_2 = np.array([sum := sum + gyro_z_2[i]*0.01 for i in range(len(gyro_z_2))])

sum = 0
gyro_x_3 = np.array([sum := sum + gyro_x_3[i]*0.01 for i in range(len(gyro_x_3))])
sum = 0
gyro_y_3 = np.array([sum := sum + gyro_y_3[i]*0.01 for i in range(len(gyro_y_3))])
sum = 0
gyro_z_3 = np.array([sum := sum + gyro_z_3[i]*0.01 for i in range(len(gyro_z_3))])

sum = 0
gyro_x_4 = np.array([sum := sum + gyro_x_4[i]*0.01 for i in range(len(gyro_x_4))])
sum = 0
gyro_y_4 = np.array([sum := sum + gyro_y_4[i]*0.01 for i in range(len(gyro_y_4))])
sum = 0
gyro_z_4 = np.array([sum := sum + gyro_z_4[i]*0.01 for i in range(len(gyro_z_4))])

sum = 0
gyro_x_5 = np.array([sum := sum + gyro_x_5[i]*0.01 for i in range(len(gyro_x_5))])
sum = 0
gyro_y_5 = np.array([sum := sum + gyro_y_5[i]*0.01 for i in range(len(gyro_y_5))])
sum = 0
gyro_z_5 = np.array([sum := sum + gyro_z_5[i]*0.01 for i in range(len(gyro_z_5))])

sum = 0
majority_gyro_x = np.array([sum := sum + i*0.01 for i in majority_gyro_x])
sum = 0
majority_gyro_y = np.array([sum := sum + i*0.01 for i in majority_gyro_y])
sum = 0
majority_gyro_z = np.array([sum := sum + i*0.01 for i in majority_gyro_z])

plt.plot(time, majority_accel_x, label="acceleration_angle (X)")
plt.plot(time, majority_gyro_x, label="gyroscope_angle (X)")
plt.plot(time, fused_angle_x, label="fusion angle (X)")
plt.xticks([time[i] for i in range(0, len(time), 40)])
plt.xlabel("Time")
plt.ylabel("Angle")
plt.legend(fancybox=True)

fig, ax = plt.subplots(nrows=3, ncols=1)
ax[0].plot(time, majority_accel_x, label="acceleration_angle (X)")
ax[0].plot(time, majority_gyro_x, label="gyroscope_angle (X)")
ax[0].plot(time, fused_angle_x, label="fusion angle (X)")
ax[0].set_xticks([time[i] for i in range(0, len(time), 40)])
ax[0].set_xlabel("Time")
ax[0].set_ylabel("Angle")
ax[0].legend(fancybox=True)
ax[0].set_title("X Axis")

ax[1].plot(time, majority_accel_y, label="acceleration_angle (Y)")
ax[1].plot(time, majority_gyro_y, label="gyroscope_angle (Y)")
ax[1].plot(time, fused_angle_y, label="fusion angle (Y)")
ax[1].set_xticks([time[i] for i in range(0, len(time), 40)])
ax[1].set_xlabel("Time")
ax[1].set_ylabel("Angle")
ax[1].legend(fancybox=True)
ax[1].set_title("Y Axis")

ax[2].plot(time, majority_accel_z, label="acceleration_angle (Z)")
ax[2].plot(time, majority_gyro_z, label="gyroscope_angle (Z)")
ax[2].plot(time, fused_angle_z, label="fusion angle (Z)")
ax[2].set_xticks([time[i] for i in range(0, len(time), 40)])
ax[2].set_xlabel("Time")
ax[2].set_ylabel("Angle")
ax[2].legend(fancybox=True)
ax[2].set_title("Z Axis")
fig.tight_layout()

fig_0, ax_0 = plt.subplots(nrows=3, ncols=2)
ax_0[0][0].plot(time, accel_x_1, label="acceleration_angle (X)")
ax_0[0][0].plot(time, gyro_x_1, label="gyroscope_angle (X)")
ax_0[0][0].plot(time, fused_angle_x, label="fusion angle (X)")
ax_0[0][0].set_xticks([time[i] for i in range(0, len(time), 40)])
ax_0[0][0].set_xlabel("Time")
ax_0[0][0].set_ylabel("Angle")
ax_0[0][0].legend(fancybox=True)
ax_0[0][0].set_title("IMU Sensor 1")

ax_0[0][1].plot(time, accel_x_2, label="acceleration_angle (X)")
ax_0[0][1].plot(time, gyro_x_2, label="gyroscope_angle (X)")
ax_0[0][1].plot(time, fused_angle_x, label="fusion angle (X)")
ax_0[0][1].set_xticks([time[i] for i in range(0, len(time), 40)])
ax_0[0][1].set_xlabel("Time")
ax_0[0][1].set_ylabel("Angle")
ax_0[0][1].legend(fancybox=True)
ax_0[0][1].set_title("IMU Sensor 2")

ax_0[1][0].plot(time, accel_x_3, label="acceleration_angle (X)")
ax_0[1][0].plot(time, gyro_x_3, label="gyroscope_angle (X)")
ax_0[1][0].plot(time, fused_angle_x, label="fusion angle (X)")
ax_0[1][0].set_xticks([time[i] for i in range(0, len(time), 40)])
ax_0[1][0].set_xlabel("Time")
ax_0[1][0].set_ylabel("Angle")
ax_0[1][0].legend(fancybox=True)
ax_0[1][0].set_title("IMU Sensor 3")

ax_0[1][1].plot(time, accel_x_4, label="acceleration_angle (X)")
ax_0[1][1].plot(time, gyro_x_4, label="gyroscope_angle (X)")
ax_0[1][1].plot(time, fused_angle_x, label="fusion angle (X)")
ax_0[1][1].set_xticks([time[i] for i in range(0, len(time), 40)])
ax_0[1][1].set_xlabel("Time")
ax_0[1][1].set_ylabel("Angle")
ax_0[1][1].legend(fancybox=True)
ax_0[1][1].set_title("IMU Sensor 4")

ax_0[2][0].plot(time, accel_x_5, label="acceleration_angle (X)")
ax_0[2][0].plot(time, gyro_x_5, label="gyroscope_angle (X)")
ax_0[2][0].plot(time, fused_angle_x, label="fusion angle (X)")
ax_0[2][0].set_xticks([time[i] for i in range(0, len(time), 40)])
ax_0[2][0].set_xlabel("Time")
ax_0[2][0].set_ylabel("Angle")
ax_0[2][0].legend(fancybox=True)
ax_0[2][0].set_title("IMU Sensor 5")

ax_0[2][1].plot(time, majority_accel_x, label="acceleration_angle (X)")
ax_0[2][1].plot(time, majority_gyro_x, label="gyroscope_angle (X)")
ax_0[2][1].plot(time, fused_angle_x, label="fusion angle (X)")
ax_0[2][1].set_xticks([time[i] for i in range(0, len(time), 40)])
ax_0[2][1].set_xlabel("Time")
ax_0[2][1].set_ylabel("Angle")
ax_0[2][1].legend(fancybox=True)
ax_0[2][1].set_title("Majority Vote")
fig_0.tight_layout()

plt.show()

