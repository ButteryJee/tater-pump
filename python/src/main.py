from arduino import Arduino
import serial

COM_PORT = "COM3"
BAUD_RATE = 9600
ARDUINO = serial.Serial(port=COM_PORT, baudrate=BAUD_RATE, timeout=.1)

if __name__ == "__main__":
    proc = Arduino(ARDUINO)
    for i in range(10):
        print(proc.cmd_get_temp_humid())