#make a script that sendes a hex file to the microcontroller

import serial
import time
import sys

received_Port = sys.argv[1]
received_Baudrate = sys.argv[2]
file_path = sys.argv[3]

#open the serial port
ser = serial.Serial(received_Port, int(received_Baudrate),timeout=0.0001)
print("Port: " + received_Port)
print("Baudrate: " + received_Baudrate,type(received_Baudrate))
print("Opening port")
time.sleep(1)
# ser.open()
print("Port opened")
#open the hex file
print("Opening hex file")
hex_file = open(file_path,"r")
print("Hex file opened")
#read the hex file
print("Reading hex file")
hex_file_content = hex_file.read()
print("Hex file read")
#send the hex file line by line and wait for the microcontroller to send back a message ok
print("Sending hex file")
for line in hex_file_content.splitlines():
    print(line)
    # ser.write(line.encode())
    for char in line:
        # time.sleep(0.000000001)
        ser.write(char.encode())
    ser.write(b'\n')
    # time.sleep(0.1)
    while True:
        if ser.in_waiting >0:
            # print(ser.readline())
            if ser.readline() == b'ok':
                print("ok received")
                break
            
print("File sent sucssesfully")
ser.close()
