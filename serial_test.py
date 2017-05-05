import serial
import time
ser = serial.Serial('COM3', 9600, timeout=0)


while 1:
 try:
  f=open('pressure.dat','w') 
  pressure = ser.readline()
  pres_str = str(pressure)
  print(pres_str)
  f.write(pres_str)
  f.close()
  time.sleep(10) # sleep time in seconds
 except ser.SerialTimeoutException:
  print('Data could not be read')
  time.sleep(10)
