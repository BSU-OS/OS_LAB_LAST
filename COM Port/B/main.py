import serial

inputPort = serial.Serial(
    port="COM2", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
)
outputPort = serial.Serial('COM3')
serialString = ""  # Used to hold data coming over UART

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
            outputPort.write("Hi from client".encode("Ascii"))
            break
