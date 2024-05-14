import serial
import folium
from folium import DivIcon
from haversine import haversine
import tkinter as tk
from tkinterhtml import HtmlFrame

# Define the serial port and baud rate
serial_port = '/dev/ttyACM0'  # Change this to your Tivc serial port
baud_rate = 9600

# Initialize serial communication
ser = serial.Serial(serial_port, baud_rate, timeout=0.5)
# Specify the file path

result = list()

for i in range(2):
    ser.write(b'U ')
    while True:
        # Read data from the serial port
        line = ser.readline().decode('utf-8').strip()
        print(line)
        if not line:
            break
        result.append(line)

points = list()

index = 0
for line in result:
    if index % 2 == 0:
        points.append(tuple(map(float, [result[index], result[index + 1]])))
    index += 1

my_map = folium.Map(location=points[0], zoom_start=18)

main_distance = 0
for i in range(len(points)):
    if i == 0:
        folium.Marker(points[i], popup='Start Point', icon=folium.Icon(color='green')).add_to(my_map)
        continue
    elif i == len(points)-1:
        folium.Marker(points[i], popup='End Point', icon=folium.Icon(color='red')).add_to(my_map)

    if i != 0:
        distance = haversine(points[i-1], points[i])
        if distance < 0.015:
            folium.PolyLine(locations=[points[i-1], points[i]], color='grey', dash_array='5, 5').add_to(my_map)
            main_distance += haversine(points[i-1], points[i])

folium.PolyLine(locations=[points[0], points[-1]], color='black', dash_array='5, 5').add_to(my_map)


folium.map.Marker(
    points[0],
    icon=DivIcon(
        icon_size=(250,36),
        icon_anchor=(0,0),
        html=f'<div style="font-size: 20pt">Distance is {round(main_distance * 1000)} meters</div>',
        )
    ).add_to(my_map)

my_map.show_in_browser()



