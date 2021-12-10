import serial  # sudo pip install pyserial should work

serial_port = '/dev/cu.usbmodem1301';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
write_to_file_path = "pdr.txt";
line1 = 0

output_file = open(write_to_file_path, "w+");
ser = serial.Serial(serial_port, baud_rate)
while(line1 < 100):
    line = ser.readline();
    line = line.decode("utf-8") #ser.readline returns a binary, convert to string
    line1 = int(line)
    print(line);
    output_file.write(line);
