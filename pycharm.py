import serial
port = "COM5"
baudrate = 9600

try:

    ser = serial.Serial(port, baudrate=baudrate)

    while True:
        command = input()
        line = ser.readline().decode().strip()
        ser.write(command.encode())
        if line:
            print("Received:", line)


except serial.SerialException as se:
    print("Serial port error:", str(se))

except KeyboardInterrupt:
    pass

finally:
    if ser.is_open:
        ser.close()
