import numpy as np
import serial as ps
import matplotlib.pyplot as plt



ser = ps.Serial()
ser.baudrate = 57600
ser.port = 'COM8'
ser.open()
xPos = [0,0]
yPos = [0,0]

def gridMake(x,y):
    setall = [[x[0],y[0]],[x[1],y[1]]]
    for i in range(25):
        for j in range(25):
            if [i,j] == setall[0]:
                print "C",1,
            if [i,j] == setall[1]:
                print "C",2,
            else:
                print "_",
            print " ",
        print
    

try:
    while True:
        call = []
        try:
            a = ser.read()
            while(a != '#'):
                call.append(a)
                a = ser.read()
            line = ''.join(call)
            print line
            if(len(line)>2):
                xpos = 0
                ypos = 0
                if (line[0] == 'C' and line[1] == 'C'):
                    carNameCall = int(line[2])
                    for i in range(len(line[5:])):
                        if(line[i+5] != 'Y'):
                            xpos = xpos*10 +int(line[i+5])
                        else:
                            break
                    ypos = int(line[5+i+2:])
                    print "car = ",carNameCall," Position = ",xpos,",",ypos
                    xPos[carNameCall-1] = xpos
                    yPos[carNameCall-1] = ypos
                    gridMake(xPos,yPos)
                
        except KeyboardInterrupt:
            exit(0)

except KeyboardInterrupt:
    print "Goodbye"
    exit(0)


'''
ser = ps.Serial()
ser.baudrate = 57600
ser.port = 'COM8'
ser.open()


try:
    while 1:
        call = []
        a = ser.read()
        while(a != '#'):
            call.append(a)
            a = ser.read()
        print ''.join(call)
except KeyboardInterrupt:
    exit()
'''