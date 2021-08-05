import regex
import xlsxwriter

infile = open("top_model/outputs/DEVS_complimentary_filter_output.txt")
workbook = xlsxwriter.Workbook('top_model/outputs/simulation_data.xlsx')
worksheet = workbook.add_worksheet()
worksheet.write('A1', 'TIME')
worksheet.write('B1', 'ACCELERATION X (m/s^2)')
worksheet.write('C1', 'ACCELERATION Y (m/s^2)')
worksheet.write('D1', 'ACCELERATION Z (m/s^2)')
worksheet.write('E1', 'GYROSCOPE X (degree/s)')
worksheet.write('F1', 'GYROSCOPE Y (degree/s)')
worksheet.write('G1', 'GYROSCOPE Z (degree/s)')
worksheet.write('H1', 'FUSED ANGLE X (degree)')
worksheet.write('I1', 'FUSED ANGLE Y (degree)')
worksheet.write('J1', 'FUSED ANGLE Z (degree)')

time_regex = regex.compile(r'\d\d:\d\d:\d\d:\d\d\d')
sensor_regex = regex.compile(r"([+-]?(?:[0-9]*[.])?[0-9]+)[\w|\W]+(accel|gyro)_(x|y|z)")
fused_angle_regex = regex.compile(r"out_(fused_angle):\s{\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)")
# fused_angle_regex = regex.compile(r"out_(gyro|accel):\s{\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)")

time = ""
row = 1
counter = 0
old_time = "00:00:00:000"
coord_dict = {"accel": {"x": 1, "y": 2, "z": 3}, "gyro": {"x": 4, "y": 5, "z": 6}, "fused_angle": {"x": 7, "y": 8, "z": 9}}

for j, i in enumerate(infile.readlines()):
    if j < 10:
        continue

    if time_regex.match(i):
        time = i.rstrip('\n')
        if time != old_time:
            row = row + 1
            counter = 1
        else:
            counter = counter + 1

        old_time = time

    if counter == 1:
        worksheet.write(row, 0, time)
        if sensor_regex.search(i):
            worksheet.write(row, coord_dict[sensor_regex.search(i).group(2)][sensor_regex.search(i).group(3)], sensor_regex.search(i).group(1))
    elif counter == 3:
        if fused_angle_regex.search(i):
            worksheet.write(row, coord_dict[fused_angle_regex.search(i).group(1)]["x"], fused_angle_regex.search(i).group(2))
            worksheet.write(row, coord_dict[fused_angle_regex.search(i).group(1)]["y"], fused_angle_regex.search(i).group(3))
            worksheet.write(row, coord_dict[fused_angle_regex.search(i).group(1)]["z"], fused_angle_regex.search(i).group(4))        
workbook.close()
