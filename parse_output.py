import regex
import xlsxwriter

infile = open("top_model/outputs/DEVS_complimentary_output_state.txt")
workbook = xlsxwriter.Workbook('top_model/outputs/simulation_data.xlsx')
worksheet = workbook.add_worksheet()
worksheet.write('A1', 'TIME')

worksheet.write('B1', 'ACCELERATION X_0 (m/s^2)')
worksheet.write('C1', 'ACCELERATION X_1 (m/s^2)')
worksheet.write('D1', 'ACCELERATION X_2 (m/s^2)')
worksheet.write('E1', 'ACCELERATION X_3 (m/s^2)')
worksheet.write('F1', 'ACCELERATION X_4 (m/s^2)')

worksheet.write('G1', 'ACCELERATION Y_0 (m/s^2)')
worksheet.write('H1', 'ACCELERATION Y_1 (m/s^2)')
worksheet.write('I1', 'ACCELERATION Y_2 (m/s^2)')
worksheet.write('J1', 'ACCELERATION Y_3 (m/s^2)')
worksheet.write('K1', 'ACCELERATION Y_4 (m/s^2)')

worksheet.write('L1', 'ACCELERATION Z_0 (m/s^2)')
worksheet.write('M1', 'ACCELERATION Z_1 (m/s^2)')
worksheet.write('N1', 'ACCELERATION Z_2 (m/s^2)')
worksheet.write('O1', 'ACCELERATION Z_3 (m/s^2)')
worksheet.write('P1', 'ACCELERATION Z_4 (m/s^2)')

worksheet.write('Q1', 'GYROSCOPE X_0 (degree/s)')
worksheet.write('R1', 'GYROSCOPE X_1 (degree/s)')
worksheet.write('S1', 'GYROSCOPE X_2 (degree/s)')
worksheet.write('T1', 'GYROSCOPE X_3 (degree/s)')
worksheet.write('U1', 'GYROSCOPE X_4 (degree/s)')

worksheet.write('V1', 'GYROSCOPE Y_0 (degree/s)')
worksheet.write('W1', 'GYROSCOPE Y_1 (degree/s)')
worksheet.write('X1', 'GYROSCOPE Y_2 (degree/s)')
worksheet.write('Y1', 'GYROSCOPE Y_3 (degree/s)')
worksheet.write('Z1', 'GYROSCOPE Y_4 (degree/s)')

worksheet.write('AA1', 'GYROSCOPE Z_0 (degree/s)')
worksheet.write('AB1', 'GYROSCOPE Z_1 (degree/s)')
worksheet.write('AC1', 'GYROSCOPE Z_2 (degree/s)')
worksheet.write('AD1', 'GYROSCOPE Z_3 (degree/s)')
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
imu_controller_regex = regex.compile(r"\b(imu_controller_(\d))\b")
majority_vote_controller_regex = regex.compile(r"\bmajority_vote_controller_0\b")
accel_regex = regex.compile(r'accelerometer:\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)')
gyro_regex = regex.compile(r'gyroscope:\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)')
fused_angle_regex = regex.compile(r'fused_angle:\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)')

time = ""
row = 1
sensor_num = 0

for i in infile.readlines():
    if time_regex.match(i) and len(i) == 13:
        time = i.rstrip('\n')
        if time != "00:00:00:000":
            row = row + 1
        worksheet.write(row, 0, time)
    elif imu_controller_regex.search(i):
        sensor_num = int(imu_controller_regex.search(i).group(2))
    elif majority_vote_controller_regex.search(i):
        sensor_num = -1
    elif fused_angle_regex.match(i):
        worksheet.write(row, 37, fused_angle_regex.search(i).group(1))
        worksheet.write(row, 38, fused_angle_regex.search(i).group(2))
        worksheet.write(row, 39, fused_angle_regex.search(i).group(3))

    if sensor_num >= 0:
        offset = sensor_num
        if accel_regex.match(i):
            worksheet.write(row, offset + 1, accel_regex.search(i).group(1))
            worksheet.write(row, offset + 6, accel_regex.search(i).group(2))
            worksheet.write(row, offset + 11, accel_regex.search(i).group(3))
        elif gyro_regex.match(i):
            worksheet.write(row, offset + 16, gyro_regex.search(i).group(1))
            worksheet.write(row, offset + 21, gyro_regex.search(i).group(2))
            worksheet.write(row, offset + 26, gyro_regex.search(i).group(3))
    elif sensor_num == -1:
        if accel_regex.match(i):
            worksheet.write(row, 31, accel_regex.search(i).group(1))
            worksheet.write(row, 32, accel_regex.search(i).group(2))
            worksheet.write(row, 33, accel_regex.search(i).group(3))
        elif gyro_regex.match(i):
            worksheet.write(row, 34, gyro_regex.search(i).group(1))
            worksheet.write(row, 35, gyro_regex.search(i).group(2))
            worksheet.write(row, 36, gyro_regex.search(i).group(3))

workbook.close()
