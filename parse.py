import time

infile = open("top_model/inputs/mpu_reading.txt")
outfile_a_x = open("top_model/inputs/accelerometer_x.txt", "w+")
outfile_a_y = open("top_model/inputs/accelerometer_y.txt", "w+")
outfile_a_z = open("top_model/inputs/accelerometer_z.txt", "w+")
outfile_g_x = open("top_model/inputs/gyroscope_x.txt", "w+")
outfile_g_y = open("top_model/inputs/gyroscope_y.txt", "w+")
outfile_g_z = open("top_model/inputs/gyroscope_z.txt", "w+")

accel_readings = []
gyro_readings = []

for i in infile.readlines():
    i = i.rstrip('\n')
    if i.find('gyro') != -1:
        gyro_readings.append(i[i.find('gyro') + 7:].split(" "))
    elif i.find('acc') != -1:
        accel_readings.append(i[i.find('acc') + 6:].split(" "))

time_counter = 0
for i in accel_readings:
    outfile_a_x.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + str(i[0])+"\n")
    outfile_a_y.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + str(i[1])+"\n")
    outfile_a_z.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + str(i[2])+"\n")
    time_counter = time_counter + 10

time_counter = 0
for i in gyro_readings:
    outfile_g_x.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + str(i[0])+"\n")
    outfile_g_y.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + str(i[1])+"\n")
    outfile_g_z.write(time.strftime("%H:%M:%S", time.gmtime(time_counter/1000)) + f":{time_counter%1000:03} " + str(i[2])+"\n")
    time_counter = time_counter + 10

print(len(accel_readings))
print(len(gyro_readings))
