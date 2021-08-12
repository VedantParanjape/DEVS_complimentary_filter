import matplotlib.pyplot as plt
import openpyxl
from xlsxwriter import worksheet
import math

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
for row in sheet.iter_rows(min_row=2, values_only=True):
    time.append(row[0])
    Ax = float(row[1])
    Ay = float(row[2])
    Az = float(row[3])
    a_x = math.atan2(Ax, (Ay**2 + Az**2)**0.5)*180/math.pi
    a_y = math.atan2(Ay, (Ax**2 + Az**2)**0.5)*180/math.pi
    a_z = math.atan2(Az, (Ay**2 + Ax**2)**0.5)*180/math.pi
    g_x = g_x + float(row[4])*0.1
    g_y = g_y + float(row[4])*0.1
    g_z = g_z + float(row[4])*0.1
    accel_x.append(a_x)
    accel_y.append(a_y)
    accel_z.append(a_z)
    gyro_x.append(g_x)
    gyro_y.append(g_y)
    gyro_z.append(g_z)
    fused_angle_x.append(row[7])
    fused_angle_y.append(row[8])
    fused_angle_z.append(row[9])

plt.ylim(-1000, 1000)
plt.plot(accel_z, label="acceleration_angle (X)")
plt.plot(gyro_z, label="gyroscope_angle (X)")
plt.plot(fused_angle_z, label="fusion angle (X)")
plt.legend(loc="upper left")
plt.show()