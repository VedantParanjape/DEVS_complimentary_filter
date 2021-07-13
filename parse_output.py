import regex
import xlsxwriter

infile = open("top_model/outputs/DEVS_complimentary_output_state.txt")
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
accel_regex = regex.compile(r'accelerometer:\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)')
gyro_regex = regex.compile(r'gyroscope:\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)')
fused_angle_regex = regex.compile(r'fused_angle:\sx:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sy:\s([+-]?(?:[0-9]*[.])?[0-9]+)\sz:\s([+-]?(?:[0-9]*[.])?[0-9]+)')

time = ""
row = 0
for i in infile.readlines():
    if time_regex.match(i) and len(i) == 13:
        row = row + 1
        time = i.rstrip('\n')
        worksheet.write(row, 0, time)
    elif accel_regex.match(i):
        worksheet.write(row, 1, accel_regex.search(i).group(1))
        worksheet.write(row, 2, accel_regex.search(i).group(2))
        worksheet.write(row, 3, accel_regex.search(i).group(3))
    elif gyro_regex.match(i):
        worksheet.write(row, 4, gyro_regex.search(i).group(1))
        worksheet.write(row, 5, gyro_regex.search(i).group(2))
        worksheet.write(row, 6, gyro_regex.search(i).group(3))
    elif fused_angle_regex.match(i):
        worksheet.write(row, 7, fused_angle_regex.search(i).group(1))
        worksheet.write(row, 8, fused_angle_regex.search(i).group(2))
        worksheet.write(row, 9, fused_angle_regex.search(i).group(3))
workbook.close()
