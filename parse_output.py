import regex
import xlsxwriter

infile = open("top_model/outputs/DEVS_complimentary_filter_output.txt")
workbook = xlsxwriter.Workbook('top_model/outputs/simulation_data.xlsx')
worksheet = workbook.add_worksheet()
worksheet.write('A1', 'TIME')

worksheet.write('B1', 'ACCELERATION X_0 (m/s^2)')
worksheet.write('C1', 'ACCELERATION Y_0 (m/s^2)')
worksheet.write('D1', 'ACCELERATION z_0 (m/s^2)')

worksheet.write('E1', 'ACCELERATION X_1 (m/s^2)')
worksheet.write('F1', 'ACCELERATION y_1 (m/s^2)')
worksheet.write('G1', 'ACCELERATION Z_1 (m/s^2)')

worksheet.write('H1', 'ACCELERATION X_2 (m/s^2)')
worksheet.write('I1', 'ACCELERATION Y_2 (m/s^2)')
worksheet.write('J1', 'ACCELERATION Z_2 (m/s^2)')

worksheet.write('K1', 'ACCELERATION X_3 (m/s^2)')
worksheet.write('L1', 'ACCELERATION Y_3 (m/s^2)')
worksheet.write('M1', 'ACCELERATION Z_3 (m/s^2)')

worksheet.write('N1', 'ACCELERATION X_4 (m/s^2)')
worksheet.write('O1', 'ACCELERATION Y_4 (m/s^2)')
worksheet.write('P1', 'ACCELERATION Z_4 (m/s^2)')

worksheet.write('Q1', 'GYROSCOPE X_0 (degree/s)')
worksheet.write('R1', 'GYROSCOPE Y_0 (degree/s)')
worksheet.write('S1', 'GYROSCOPE Z_0 (degree/s)')

worksheet.write('T1', 'GYROSCOPE X_1 (degree/s)')
worksheet.write('U1', 'GYROSCOPE Y_1 (degree/s)')
worksheet.write('V1', 'GYROSCOPE Z_1 (degree/s)')

worksheet.write('W1', 'GYROSCOPE X_2 (degree/s)')
worksheet.write('X1', 'GYROSCOPE Y_2 (degree/s)')
worksheet.write('Y1', 'GYROSCOPE Z_2 (degree/s)')

worksheet.write('Z1', 'GYROSCOPE X_3 (degree/s)')
worksheet.write('AA1', 'GYROSCOPE Y_3 (degree/s)')
worksheet.write('AB1', 'GYROSCOPE Z_3 (degree/s)')

worksheet.write('AC1', 'GYROSCOPE X_4 (degree/s)')
worksheet.write('AD1', 'GYROSCOPE Y_4 (degree/s)')
worksheet.write('AE1', 'GYROSCOPE Z_4 (degree/s)')

worksheet.write('AF1', 'MAJORITY VOTE ACCELEROMETER ANGLE X (degree)')
worksheet.write('AG1', 'MAJORITY VOTE ACCELEROMETER ANGLE Y (degree)')
worksheet.write('AH1', 'MAJORITY VOTE ACCELEROMETER ANGLE Z (degree)')

worksheet.write('AI1', 'MAJORITY VOTE GYROSCOPE ANGLE X (degree)')
worksheet.write('AJ1', 'MAJORITY VOTE GYROSCOPE ANGLE Y (degree)')
worksheet.write('AK1', 'MAJORITY VOTE GYROSCOPE ANGLE Z (degree)')

worksheet.write('AL1', 'FUSED ANGLE X (degree)')
worksheet.write('AM1', 'FUSED ANGLE Y (degree)')
worksheet.write('AN1', 'FUSED ANGLE Z (degree)')

time_regex = regex.compile(r'\d\d:\d\d:\d\d:\d\d\d')
sensor_regex = regex.compile(r"([+-]?(?:[0-9]*[.])?[0-9]+)[\w|\W]+(accel|gyro)_(x|y|z)_(\d+)")
majority_vote_regex = regex.compile(r"out_(gyro|accel):\s{\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)")
fused_angle_regex = regex.compile(r"out_(fused_angle):\s{\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)")

time = ""
row = 1
counter = 0
old_time = "00:00:00:000"
coord_dict = {
    "accel": 
            [
                {"x": 1, "y": 2, "z": 3}, 
                {"x": 4, "y": 5, "z": 6},
                {"x": 7, "y": 8, "z": 9},
                {"x": 10, "y": 11, "z": 12},
                {"x": 13, "y": 14, "z": 15}
            ], 
    "gyro": [
                {"x": 16, "y": 17, "z": 18},
                {"x": 19, "y": 20, "z": 21},
                {"x": 22, "y": 23, "z": 24},
                {"x": 25, "y": 26, "z": 27},
                {"x": 28, "y": 29, "z": 30}, 
            ],
    "majority_vote": {
                        "accel": {"x": 31, "y": 32, "z": 33},
                        "gyro": {"x": 34, "y": 35, "z": 36}
                     },
    "fused_angle": {"x": 37, "y": 38, "z": 39} 
}

for j, i in enumerate(infile.readlines()):
    if j < 39:
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
            worksheet.write(row, coord_dict[sensor_regex.search(i).group(2)][int(sensor_regex.search(i).group(4))][sensor_regex.search(i).group(3)], sensor_regex.search(i).group(1))

    elif counter == 3:
        if majority_vote_regex.search(i):
            for r in majority_vote_regex.findall(i):
                worksheet.write(row, coord_dict["majority_vote"][r[0]]["x"], r[1])
                worksheet.write(row, coord_dict["majority_vote"][r[0]]["y"], r[2])
                worksheet.write(row, coord_dict["majority_vote"][r[0]]["z"], r[3])

    elif counter == 4:
        if fused_angle_regex.search(i):
            worksheet.write(row, coord_dict[fused_angle_regex.search(i).group(1)]["x"], fused_angle_regex.search(i).group(2))
            worksheet.write(row, coord_dict[fused_angle_regex.search(i).group(1)]["y"], fused_angle_regex.search(i).group(3))
            worksheet.write(row, coord_dict[fused_angle_regex.search(i).group(1)]["z"], fused_angle_regex.search(i).group(4))        

workbook.close()
