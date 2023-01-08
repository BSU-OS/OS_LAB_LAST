import serial

outputPort = serial.Serial('COM1')
outputPort.write("Hi from server".encode("ascii"))
inputPort = serial.Serial(
    port="COM4", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
)
while True:
    # Wait until there is data waiting in the serial buffer
    if inputPort.in_waiting > 0:

        # Read data out of the buffer until a carraige return / new line is found
        serialString = inputPort.readline()

        # Print the contents of the serial data
        success = False
        try:
            print(serialString.decode("Ascii"))
            success = True
        except:
            pass
        if success:
            break
#Важно наличие данных портов и их связка
#COM1<->COM2
#COM3<->COM4
#Можно создать виртуальные при помощи Virtual Serial Port
