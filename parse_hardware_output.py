import numpy as np
import matplotlib.pyplot as plt

infile = open("top_model/inputs/putty.log")

accel_x_1 = []
accel_y_1 = []
accel_z_1 = []

accel_x_2 = []
accel_y_2 = []
accel_z_2 = []

accel_x_3 = []
accel_y_3 = []
accel_z_3 = []

gyro_x_1 = []
gyro_y_1 = []
gyro_z_1 = []

gyro_x_2 = []
gyro_y_2 = []
gyro_z_2 = []

gyro_x_3 = []
gyro_y_3 = []
gyro_z_3 = []

majority_accel_x = []
majority_accel_y = []
majority_accel_z = []

majority_gyro_x = []
majority_gyro_y = []
majority_gyro_z = []

fused_angle_x = []
fused_angle_y = []
fused_angle_z = []

for i in infile.readlines():
    i = i.rstrip('\n')
    data = i.split(";")

    if data[0] == "a0":
        accel_x_1.append(float(data[1]))
        accel_y_1.append(float(data[2]))
        accel_z_1.append(float(data[3]))

    elif data[0] == "a1":
        accel_x_2.append(float(data[1]))
        accel_y_2.append(float(data[2]))
        accel_z_2.append(float(data[3]))

    elif data[0] == "a2":
        accel_x_3.append(float(data[1]))
        accel_y_3.append(float(data[2]))
        accel_z_3.append(float(data[3]))

    elif data[0] == "g0":
        gyro_x_1.append(float(data[1]))
        gyro_y_1.append(float(data[2]))
        gyro_z_1.append(float(data[3]))

    elif data[0] == "g1":
        gyro_x_2.append(float(data[1]))
        gyro_y_2.append(float(data[2]))
        gyro_z_2.append(float(data[3]))

    elif data[0] == "g2":
        gyro_x_3.append(float(data[1]))
        gyro_y_3.append(float(data[2]))
        gyro_z_3.append(float(data[3]))

    elif data[0] == "am":
        majority_accel_x.append(float(data[1]))
        majority_accel_y.append(float(data[2]))
        majority_accel_z.append(float(data[3]))

    elif data[0] == "gm":
        majority_gyro_x.append(float(data[1]))
        majority_gyro_y.append(float(data[2]))
        majority_gyro_z.append(float(data[3]))

    elif data[0] == "f":
        fused_angle_x.append(float(data[1]))
        fused_angle_y.append(float(data[2]))
        fused_angle_z.append(float(data[3]))

accel_x_1 = np.array(accel_x_1)
accel_y_1 = np.array(accel_y_1)
accel_z_1 = np.array(accel_z_1)
accel_x_2 = np.array(accel_x_2)
accel_y_2 = np.array(accel_y_2)
accel_z_2 = np.array(accel_z_2)
accel_x_3 = np.array(accel_x_3)
accel_y_3 = np.array(accel_y_3)
accel_z_3 = np.array(accel_z_3)
gyro_x_1 = np.array(gyro_x_1)
gyro_y_1 = np.array(gyro_y_1)
gyro_z_1 = np.array(gyro_z_1)
gyro_x_2 = np.array(gyro_x_2)
gyro_y_2 = np.array(gyro_y_2)
gyro_z_2 = np.array(gyro_z_2)
gyro_x_3 = np.array(gyro_x_3)
gyro_y_3 = np.array(gyro_y_3)
gyro_z_3 = np.array(gyro_z_3)
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

majority_gyro_x[0] = majority_accel_x[0]
majority_gyro_y[0] = majority_accel_y[0]
majority_gyro_z[0] = majority_accel_z[0]

sum = 0
gyro_x_1 = np.array([sum := sum + gyro_x_1[i]*1.5 for i in range(len(gyro_x_1))])
sum = 0
gyro_y_1 = np.array([sum := sum + gyro_y_1[i]*1.5 for i in range(len(gyro_y_1))])
sum = 0
gyro_z_1 = np.array([sum := sum + gyro_z_1[i]*1.5 for i in range(len(gyro_z_1))])

sum = 0
gyro_x_2 = np.array([sum := sum + gyro_x_2[i]*1.5 for i in range(len(gyro_x_2))])
sum = 0
gyro_y_2 = np.array([sum := sum + gyro_y_2[i]*1.5 for i in range(len(gyro_y_2))])
sum = 0
gyro_z_2 = np.array([sum := sum + gyro_z_2[i]*1.5 for i in range(len(gyro_z_2))])

sum = 0
gyro_x_3 = np.array([sum := sum + gyro_x_3[i]*1.5 for i in range(len(gyro_x_3))])
sum = 0
gyro_y_3 = np.array([sum := sum + gyro_y_3[i]*1.5 for i in range(len(gyro_y_3))])
sum = 0
gyro_z_3 = np.array([sum := sum + gyro_z_3[i]*1.5 for i in range(len(gyro_z_3))])

sum = 0
majority_gyro_x = np.array([sum := sum + i*1.5 for i in majority_gyro_x])
sum = 0
majority_gyro_y = np.array([sum := sum + i*1.5 for i in majority_gyro_y])
sum = 0
majority_gyro_z = np.array([sum := sum + i*1.5 for i in majority_gyro_z])

plt.plot(majority_accel_x, label="acceleration_angle (X)")
plt.plot(majority_gyro_x, label="gyroscope_angle (X)")
plt.plot(fused_angle_x, label="fusion angle (X)")
plt.xlabel("Time")
plt.ylabel("Angle")
plt.legend(fancybox=True)

fig, ax = plt.subplots(nrows=3, ncols=1)
ax[0].plot(majority_accel_x, label="acceleration_angle (X)")
ax[0].plot(majority_gyro_x, label="gyroscope_angle (X)")
ax[0].plot(fused_angle_x, label="fusion angle (X)")
ax[0].set_xlabel("Time")
ax[0].set_ylabel("Angle")
ax[0].legend(fancybox=True)
ax[0].set_title("X Axis")

ax[1].plot(majority_accel_y, label="acceleration_angle (Y)")
ax[1].plot(majority_gyro_y, label="gyroscope_angle (Y)")
ax[1].plot(fused_angle_y, label="fusion angle (Y)")
ax[1].set_xlabel("Time")
ax[1].set_ylabel("Angle")
ax[1].legend(fancybox=True)
ax[1].set_title("Y Axis")

ax[2].plot(majority_accel_z, label="acceleration_angle (Z)")
ax[2].plot(majority_gyro_z, label="gyroscope_angle (Z)")
ax[2].plot(fused_angle_z, label="fusion angle (Z)")
ax[2].set_xlabel("Time")
ax[2].set_ylabel("Angle")
ax[2].legend(fancybox=True)
ax[2].set_title("Z Axis")

fig_0, ax_0 = plt.subplots(nrows=2, ncols=2)
ax_0[0][0].plot(accel_x_1, label="acceleration_angle (X)")
ax_0[0][0].plot(gyro_x_1, label="gyroscope_angle (X)")
ax_0[0][0].plot(fused_angle_x, label="fusion angle (X)")
ax_0[0][0].set_xlabel("Time")
ax_0[0][0].set_ylabel("Angle")
ax_0[0][0].legend(fancybox=True)
ax_0[0][0].set_title("IMU Sensor 1")

ax_0[0][1].plot(accel_x_2, label="acceleration_angle (X)")
ax_0[0][1].plot(gyro_x_2, label="gyroscope_angle (X)")
ax_0[0][1].plot(fused_angle_x, label="fusion angle (X)")
ax_0[0][1].set_xlabel("Time")
ax_0[0][1].set_ylabel("Angle")
ax_0[0][1].legend(fancybox=True)
ax_0[0][1].set_title("IMU Sensor 2")

ax_0[1][0].plot(accel_x_3, label="acceleration_angle (X)")
ax_0[1][0].plot(gyro_x_3, label="gyroscope_angle (X)")
ax_0[1][0].plot(fused_angle_x, label="fusion angle (X)")
ax_0[1][0].set_xlabel("Time")
ax_0[1][0].set_ylabel("Angle")
ax_0[1][0].legend(fancybox=True)
ax_0[1][0].set_title("IMU Sensor 3")

ax_0[1][1].plot(majority_accel_x, label="acceleration_angle (X)")
ax_0[1][1].plot(majority_gyro_x, label="gyroscope_angle (X)")
ax_0[1][1].plot(fused_angle_x, label="fusion angle (X)")
ax_0[1][1].set_xlabel("Time")
ax_0[1][1].set_ylabel("Angle")
ax_0[1][1].legend(fancybox=True)
ax_0[1][1].set_title("Majority Vote")
fig_0.tight_layout()

fig.tight_layout()
plt.show()