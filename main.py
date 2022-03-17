mport
serial

# make sure COM# is correct before running script. COM# has to match arduino. To find COM# in Arduino IDE: Tools->port
serialPort = serial.Serial('COM5', baudrate=9600, timeout=2)

textfileName = input("Name textfile (no '.txt'): ")

TestData = open(textfileName + '.txt', 'w')

while True:
    data = serialPort.readline().decode('ascii')
    print(data)
    TestData.write(data)

TestData.close()
i