from arduino import Arduino
import serial
import logging
import sys

COM_PORT = "COM3"
BAUD_RATE = 9600

if __name__ == "__main__":

    # Attempt to connect to arduino device
    try:
        connection = serial.Serial(port=COM_PORT, baudrate=BAUD_RATE, timeout=.1)
    except serial.SerialException:
        logging.error("Could not connect to device on {} with baud {}.".format(COM_PORT, BAUD_RATE))
        sys.exit(1)
        

    # Continue if connection was successful
    proc = Arduino(connection)
    for i in range(10):
        print(proc.cmd_get_temp_humid())