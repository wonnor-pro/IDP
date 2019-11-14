import serial  # Serial imported for Serial communication
import time  # Required to use delay functions

# Create Serial port object called arduinoSerialData
ArduinoSerial = serial.Serial('/dev/cu.usbmodem141102', 9600)

# wait for 2 secounds for the communication to get established
time.sleep(2)

# read the serial data and print it as line
print(ArduinoSerial.readline())
print("Enter \"yes\" to turn ON LED and \"no\" to turn OFF LED")

while 1:  # Do this forever
    # get input from user
    var = input()

    # print the intput for confirmation
    print("you entered", var)

    # if the value is yes
    if (var == '1'):
        # send 'yes'
        ArduinoSerial.write(bytes(var.encode('ascii')))
        print("LED turned ON")
        time.sleep(1)

    # if the value is no
    if (var == '0'):
        # send 'no
        ArduinoSerial.write(bytes(var.encode('ascii')))
        print("LED turned OFF")
        time.sleep(1)

