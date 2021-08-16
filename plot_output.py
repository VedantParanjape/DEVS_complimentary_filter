import matplotlib.pyplot as plt
import openpyxl
from xlsxwriter import worksheet
import math
import numpy as np

workbook = openpyxl.load_workbook(filename="top_model/outputs/simulation_data.xlsx", data_only=True)
sheet = workbook.active

time = []
accel_x = []
accel_y = []
accel_z = []
gyro_x = []
gyro_y = []
gyro_z = []
fused_angle_x = []
fused_angle_y = []
fused_angle_z = []
g_x = 0
g_y = 0
g_z = 0
counter = 0
for row in sheet.iter_rows(min_row=2, values_only=True):
    time.append(row[0])
    Ax = float(row[1])
    Ay = float(row[2])
    Az = float(row[3])
    a_x = math.atan2(Ax, (Ay**2 + Az**2)**0.5)*180/math.pi
    a_y = math.atan2(Ay, (Ax**2 + Az**2)**0.5)*180/math.pi
    a_z = math.atan2(Az, (Ay**2 + Ax**2)**0.5)*180/math.pi
    if counter == 0:
        g_x = a_x
        g_y = a_y
        g_z = a_z
    else:
        g_x = g_x + float(row[4])*0.01
        g_y = g_y + float(row[4])*0.01
        g_z = g_z + float(row[4])*0.01
    accel_x.append(a_x)
    accel_y.append(a_y)
    accel_z.append(a_z)
    gyro_x.append(g_x)
    gyro_y.append(g_y)
    gyro_z.append(g_z)
    fused_angle_x.append(float(row[7]))
    fused_angle_y.append(float(row[8]))
    fused_angle_z.append(float(row[9]))
    counter = counter + 1

plt.plot(time, accel_x, label="acceleration_angle (X)")
plt.plot(time, gyro_x, label="gyroscope_angle (X)")
plt.plot(time, fused_angle_x, label="fusion angle (X)")
plt.xticks([time[i] for i in range(0, len(time), 40)])
plt.xlabel("Time")
plt.ylabel("Angle")
plt.legend(fancybox=True)

fig, ax = plt.subplots(nrows=3, ncols=1)
ax[0].plot(time, accel_x, label="acceleration_angle (X)")
ax[0].plot(time, gyro_x, label="gyroscope_angle (X)")
ax[0].plot(time, fused_angle_x, label="fusion angle (X)")
ax[0].set_xticks([time[i] for i in range(0, len(time), 40)])
ax[0].set_xlabel("Time")
ax[0].set_ylabel("Angle")
ax[0].legend(fancybox=True)
ax[0].set_title("X Axis")

ax[1].plot(time, accel_y, label="acceleration_angle (Y)")
ax[1].plot(time, gyro_y, label="gyroscope_angle (Y)")
ax[1].plot(time, fused_angle_y, label="fusion angle (Y)")
ax[1].set_xticks([time[i] for i in range(0, len(time), 40)])
ax[1].set_xlabel("Time")
ax[1].set_ylabel("Angle")
ax[1].legend(fancybox=True)
ax[1].set_title("Y Axis")

ax[2].plot(time, accel_z, label="acceleration_angle (Z)")
ax[2].plot(time, gyro_z, label="gyroscope_angle (Z)")
ax[2].plot(time, fused_angle_z, label="fusion angle (Z)")
ax[2].set_xticks([time[i] for i in range(0, len(time), 40)])
ax[2].set_xlabel("Time")
ax[2].set_ylabel("Angle")
ax[2].legend(fancybox=True)
ax[2].set_title("Z Axis")

fig.tight_layout()
plt.show()

