import time

infile = open("top_model/inputs/mpu_reading.txt")

outfile_a_x = [open("top_model/inputs/accelerometer_x_1.txt", "w+"), 
                open("top_model/inputs/accelerometer_x_2.txt", "w+"), 
                 open("top_model/inputs/accelerometer_x_3.txt", "w+"), 
                  open("top_model/inputs/accelerometer_x_4.txt", "w+"), 
                   open("top_model/inputs/accelerometer_x_5.txt", "w+")]

outfile_a_y = [open("top_model/inputs/accelerometer_y_1.txt", "w+"),
                open("top_model/inputs/accelerometer_y_2.txt", "w+"),
                 open("top_model/inputs/accelerometer_y_3.txt", "w+"),
                  open("top_model/inputs/accelerometer_y_4.txt", "w+"),
                   open("top_model/inputs/accelerometer_y_5.txt", "w+")]

outfile_a_z = [open("top_model/inputs/accelerometer_z_1.txt", "w+"),
                open("top_model/inputs/accelerometer_z_2.txt", "w+"),
                 open("top_model/inputs/accelerometer_z_3.txt", "w+"),
                  open("top_model/inputs/accelerometer_z_4.txt", "w+"),
                   open("top_model/inputs/accelerometer_z_5.txt", "w+")]

outfile_g_x = [open("top_model/inputs/gyroscope_x_1.txt", "w+"),
                open("top_model/inputs/gyroscope_x_2.txt", "w+"),
                 open("top_model/inputs/gyroscope_x_3.txt", "w+"),
                  open("top_model/inputs/gyroscope_x_4.txt", "w+"),
                   open("top_model/inputs/gyroscope_x_5.txt", "w+")]

outfile_g_y = [open("top_model/inputs/gyroscope_y_1.txt", "w+"),
                open("top_model/inputs/gyroscope_y_2.txt", "w+"),
                 open("top_model/inputs/gyroscope_y_3.txt", "w+"),
                  open("top_model/inputs/gyroscope_y_4.txt", "w+"),
                   open("top_model/inputs/gyroscope_y_5.txt", "w+")]

outfile_g_z = [open("top_model/inputs/gyroscope_z_1.txt", "w+"),
                open("top_model/inputs/gyroscope_z_2.txt", "w+"),
                 open("top_model/inputs/gyroscope_z_3.txt", "w+"),
                  open("top_model/inputs/gyroscope_z_4.txt", "w+"),
                   open("top_model/inputs/gyroscope_z_5.txt", "w+")]

accel_readings = []
gyro_readings = []

for i in infile.readlines():
    i = i.rstrip('\n')
    if i.find('gyro') != -1:
        gyro_readings.append(i[i.find('gyro') + 7:].split(" "))
    elif i.find('acc') != -1:
        accel_readings.append(i[i.find('acc') + 6:].split(" "))

delta = [0.01, 0.02, 0.0, 0.01, 0.6]
for i in range(0, 5):
    outfile_a_x_ = outfile_a_x[i]
    outfile_a_y_ = outfile_a_y[i]
    outfile_a_z_ = outfile_a_z[i]
    time_counter = 0
    for j in accel_readings:
        outfile_a_x_.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + f"{float(j[0]) + delta[i]}\n")
        outfile_a_y_.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + f"{float(j[1]) + delta[i]}\n")
        outfile_a_z_.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + f"{float(j[2]) + delta[i]}\n")
        time_counter = time_counter + 10

for i in range(0, 5):
    outfile_g_x_ = outfile_g_x[i]
    outfile_g_y_ = outfile_g_y[i]
    outfile_g_z_ = outfile_g_z[i]
    time_counter = 0
    for j in gyro_readings:
        outfile_g_x_.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + f"{float(j[0]) + delta[i]}\n")
        outfile_g_y_.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + f"{float(j[1]) + delta[i]}\n")
        outfile_g_z_.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + f"{float(j[2]) + delta[i]}\n")
        time_counter = time_counter + 10

print(len(accel_readings))
print(len(gyro_readings))
