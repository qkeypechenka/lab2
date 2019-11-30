from matplotlib import pyplot as plt
from collections import deque
import serial

ser = serial.Serial("/dev/cu.usbserial-1410", 115200)
plt.ion()

distances = deque(maxlen=20)

line, = plt.plot(distances)
plt.ylim([10, 40])
plt.axes(projection='polar')
plt.show()
while True:
    while ser.in_waiting == 0:
        continue
    distance = float(ser.readline())
    angle = float(ser.readline())

    distances.append(distance)
    ymin = float(min(distances)) - 20
    ymax = float(max(distances)) + 20
    plt.ylim([ymin, ymax])

    line.set_xdata(len(distances))
    line.set_ydata(distances)
    plt.polar(angle, distance, 'p')
    plt.draw()
    plt.pause(1e-19)
