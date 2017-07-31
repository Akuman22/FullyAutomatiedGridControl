import numpy as np
import serial as ps
import matplotlib.pyplot as plt
import math


ser = ps.Serial()
ser.baudrate = 57600
ser.port = 'COM14'
ser.open()
xPos = [12,14]
yPos = [12,10]
xDestination = [14,12]
yDestination = [11,12]
xNext = [12,24]
yNext = [12,24]
grid = [[1 for ii in range(25)]for ii in range(25)] 
Setall = [[]for ii in range(2)] 
destPos = 0;
X = 24 # size of grid 
Y = 24 # size of grid

def neighbors(x,y):
    return [[x+1,y],[x-1,y],[x,y+1],[x,y-1]]
    
    
def Energy(x,y,carName):
    if((x<25) and (y<25)):
        energy = np.sqrt(math.pow((xDestination[carName]-x),2) + 
                     math.pow((yDestination[carName]-y),2)) + grid[x][y]
        return energy
    else:
        return 100000
        
def PathMake(carName):
    if((xPos[carName] == xDestination[carName]) and (yPos[carName] == yDestination[carName])):
        print "Car ",carName+1," has reached the destination"
        print "Press Ctrl + C to assign new destination"
        for i in range(25):
            for j in range(25):
                if([i,j] in Setall[carName]):
                    
                    grid[i][j] = 1
        Setall[carName] = []
        return 0
    if(carName == 1):
        othercarName = 0
    if(carName == 0):
        othercarName = 1
    xx = neighbors(xPos[carName],yPos[carName])    
    yy = neighbors(xPos[othercarName],yPos[othercarName])
    tempEnergy = 10000;
    for i in range(len(xx)):
        if (((xx[i][0],xx[i][1]) not in yy) and 
            (Energy(xx[i][0],xx[i][1],carName) < tempEnergy)and
            (0<=xx[i][0]<=24) and (0<=xx[i][1]<=24)):
            tempEnergy = Energy(xx[i][0],xx[i][1],carName)
            print tempEnergy
            xNext[carName] = xx[i][0]
            yNext[carName] = xx[i][1]
    return 1
            

def gridMake(x,y):
    setall = [[x[0],y[0]],[x[1],y[1]]]
    for i in range(25):
        for j in range(25):
            if [i,j] == setall[0]:
                print "C",1,
            if [i,j] == setall[1]:
                print "C",2,
            if(grid[i][j] != 10000):
                print grid[i][j],
            if(grid[i][j] == 10000):
                print "X",
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
            if(len(line)>1):
                xpos = 0
                ypos = 0
                if(line[0] == 'A' and line[1] == 'C' and line[2] == 'K' ):
                    carNameCall = int(line[3])
                    for i in range(len(line[6:])):
                        if(line[i+6] != 'Y'):
                            xpos = xpos*10 +int(line[i+6])
                        else:
                            break
                    ypos = int(line[6+i+2:])
                    print "car = ",carNameCall," Position = ",xpos,",",ypos
                    xPos[carNameCall-1] = xpos
                    yPos[carNameCall-1] = ypos
                    if((xPos[carNameCall-1] != xDestination[carNameCall-1]) or
                       (yPos[carNameCall-1] != yDestination[carNameCall-1])):
                        grid[xPos[carNameCall-1]][yPos[carNameCall-1]]+=2
                    Setall[carNameCall-1].append([xpos,ypos])
                    gridMake(xPos,yPos)
                if(line[0] == 'C' and line[1].isdigit()):
                    ret = PathMake(int(line[1])-1)
                    ser.write(str(xNext[int(line[1])-1]))
                    ser.write('#')
                    ser.write(str(yNext[int(line[1])-1]))
                    ser.write('#')
                    print "Path sent = ",str(xNext[int(line[1])-1]),",",str(yNext[int(line[1])-1])
                elif(line[0] == 'C' and line[1] == 'C'):
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
                elif(line[0] == 'S' and line[1] == 'F'):
                    print "Car "+str(line[2])+" unresponsive"
                    print "Alerting Police"
                
        except KeyboardInterrupt:
            gridMake(xPos,yPos)
            print "Destination Car1 = ",xDestination[0],",",yDestination[0]
            print "Destination Car2 = ",xDestination[1],",",yDestination[1]
            print 
            print "1 -> Change Invalid Point"
            print "2 -> Change Valid Point"
            print "3 -> Change Destination Car1"
            print "4 -> Change Destination Car2"
            print "5 -> exit"
            choice = raw_input("What do you want to change?")
            print "You chose ", choice
            if (int(choice) == 1):
                countInv = 0
                print "List of invalid points = "
                for ii in range(X):
                    for jj in range(Y):
                        if(grid[ii][jj] == 10000):
                            print ii,",",jj
                            countInv +=1
                if(countInv > 0):
                    xpt = raw_input("Enter x coordinate")
                    ypt = raw_input("Enter y coordinate")
                    grid[int(xpt)][int(ypt)] = 1
            if (int(choice) == 2):
                ch = 'y'
                while(ch != 'n'):
                    xpt = raw_input("Enter x coordinate")
                    ypt = raw_input("Enter y coordinate")
                    grid[int(xpt)][int(ypt)] = 10000
                    gridMake(xPos,yPos)
                    ch = raw_input("change another? (y/n)")
            if (int(choice) == 3):              
                xDestination[0] = int(raw_input("Enter new xDestination"))
                yDestination[0] = int(raw_input("Enter new yDestination"))
            if (int(choice) == 4):              
                xDestination[1] = int(raw_input("Enter new xDestination"))
                yDestination[1] = int(raw_input("Enter new yDestination"))
            if (int(choice) == 5):              
                exit(0)
            else:
                pass

except KeyboardInterrupt:
    exit(0)
