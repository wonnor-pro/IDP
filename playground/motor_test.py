import serial  # Serial imported for Serial communication
import time  # Required to use delay functions

def main():
    # Create Serial port object called arduinoSerialData
    ArduinoSerial = serial.Serial('/dev/cu.usbmodem146102', 9600)

    time.sleep(2)

    # Check connection
    print(ArduinoSerial.readline())
    print("Connected")
    # assert here

    while 1:
        data = input("Enter {} to clarify direction and speed".format("dir,pace&dir,pace..."))
        ArduinoSerial.write(bytes(data.encode('ascii')))

        time.sleep(1)


if __name__ == "__main__":
    main()



