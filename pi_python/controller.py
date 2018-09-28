import serial
import time
import datetime
import sys

#get time integers
def getTimeAsInt():
    thisTime   = datetime.datetime.now()
    splitTime  = str(thisTime).split(' ')
    fullTimeString = splitTime[1]
    cutTime = fullTimeString.split(':')
    print('fine grained time = ' + cutTime[0] + ':' + cutTime[1] + ':' + cutTime[2])
    return int(cutTime[0] + cutTime[1])

#send time
def sendTimeIntToArduino(serialObj, n):
    serialObj.write(('d%s'%n).encode())
    

#set up serial class object
try:
    ser=serial.Serial("/dev/ttyACM0", 9600)
except:
    ser=serial.Serial("/dev/ttyACM1", 9600)
    
ser.baudrate=9600

while True:
    #send time as integer to Arduino once a second
     timeAsInt = getTimeAsInt()
     sendTimeIntToArduino(ser, timeAsInt)
     print('sending this integer to Arduino : ' + str(timeAsInt))
     time.sleep(1)
     #print('received this integer from Arduino : ' + str(ser.readline()))
