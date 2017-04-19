import msvcrt
import serial

ser = serial.Serial()
ser.baudrate = 57600
ser.port = 'COM9'
ser.open()

while 1:
    if(msvcrt.getch()):
        input_char = msvcrt.getch()
        print(str(input_char))
    	ser.write(str(input_char))
    else:
	print ser.read()

