import serial
import time

set = serial.Serial('/dev/ttyUSB0', 9600, timeout = 1.0)
time.sleep(3)
set.reset_input_buffer()
print("Mikrokontroller connected")

try :
    while True:
        time.sleep(0.01)
        if set.in_waiting > 0 :
            data = set.readline().decode('utf-8')
            print(data)
except KeyboardInterrupt:
    print("Close Serial Communication")
    set.close()





