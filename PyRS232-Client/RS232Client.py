import serial
ser = serial.Serial('/dev/ttyACM0',9600)  # open serial port
ser.write(b'255,0\n')



ser.close()

