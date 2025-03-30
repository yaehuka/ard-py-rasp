import serial
port = "COM8"
baudrate = 9600
s = []
dec  = 'latin1' # Möglichkeiten: utf-8, cp1252, iso-8859-1, latin1, utf-16
ser = serial.Serial(port, baudrate=baudrate)
try:



    while True:
        command = input()
        line = ser.readline().decode().strip()
        ser.write(command.encode())
        if line:
            if not(line == "-1"):
                s.append(line)
                print("Received:", line)
        print(s)


except serial.SerialException as se:
    print("Serial port error:", str(se))

except KeyboardInterrupt:
    pass
finally:
    if ser.is_open:
        ser.close()
