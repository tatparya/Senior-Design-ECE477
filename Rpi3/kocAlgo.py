import os
import sys
import time
import serial
import kociemba
import numpy as np

def kocConvert( cubeArray ):
    cubeOut = ""
    for element in cubeArray:
        if element == 0:
            cubeOut += 'L'
        elif element == 1:
            cubeOut += 'F'
        elif element == 2:
            cubeOut += 'R'
        elif element == 3:
            cubeOut += 'B'
        elif element == 4:
            cubeOut += 'U'
        elif element == 5:
            cubeOut += 'D'

    print( cubeOut )
    return cubeOut

def solveCube( cube ):
    sol = kociemba.solve( cube )

    print( sol )
    return sol

def kocConvertBack( element ):
    if element == 'L':
        return 0
    elif element == 'F':
        return 3
    elif element == 'R':
        return 2
    elif element == 'B':
        return 1
    elif element == 'U':
        return 5
    elif element == 'D':
        return 4


def kocConvertBackStr( element ):
    if element == 'L':
        return 'a'
    elif element == 'F':
        return 'd'
    elif element == 'R':
        return 'c'
    elif element == 'B':
        return 'b'
    elif element == 'U':
        return 'f'
    elif element == 'D':
        return 'e'

def parseSol( sol ):
    solParts = sol.split()

    moves = []
    face = 0

    print( solParts )
    
    for move in solParts:
        face = kocConvertBackStr( move[0] )

        if len( move ) == 2:
            if move[1] == '\'':
                face = chr( ord(face) + 6 )
                moves.append( face )
            else:
                moves.append( face )
                moves.append( face )
        else:
            moves.append( face )

    return moves

def changeNums( array ):
    for i in array:
        for j in i:
            for n in range( len(j) ):
                if j[n] == 4:
                    j[n] = 5
                elif j[n] == 5:
                    j[n] = 4
                elif j[n] == 1:
                    j[n] = 3
                elif j[n] == 3:
                    j[n] = 1

    return array

def getPos( element ):
    if element == 0:
        return 4
    elif element == 1:
        return 2
    elif element == 2:
        return 1
    elif element == 3:
        return 5
    elif element == 4:
        return 0
    elif element == 5:
        return 3 

def makeNewAr( array ):
    newAr = [[],[],[],[],[],[]]
    for i in array:
        flatAr = np.asarray( i )
        n = flatAr[1][1]
        pos = getPos( n )
        newAr[pos] = flatAr.flatten()
        #newAr[pos] = list(reversed(new))
        print( newAr[n] )

    print( newAr )
        
    return newAr

def sendData( array ):
    ser = serial.Serial(port='/dev/ttyS0',baudrate = 115200,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=0)

    ser.write(str(1).encode())
    time.sleep(1)
    for i in array:
        print( str(i).encode() )
        ser.write(str(i).encode())
        time.sleep(1)
        
    ser.write(str('x').encode())
    time.sleep(1)
    ser.close()

def makeCubeAr():
    f1 = open('colorsOutput1.txt', 'r')

    final_nums_list = []
    for line in f1:
        f_nums_list = [[], [], []]
        cnt = 0
        for c in line:
            if c >= '0' and c <= '5':
                c_i = int(c)
                f_nums_list[cnt/3].append(c_i)
                cnt += 1
        final_nums_list.append(f_nums_list)
        
    return final_nums_list

def main():
    cubeAr = makeCubeAr()

    print cubeAr
    
    newAr = changeNums( cubeAr )
    print( "Changed nums" )
    print( newAr )

    finalAr = makeNewAr( newAr )
    
    flat_array = np.asarray(finalAr)
    flat_array1 = flat_array.flatten()
    
    kocString = kocConvert( flat_array1 )

    solString = solveCube( kocString )

    finalList = parseSol( solString )

    print( finalList )

    for i in finalList:
        print(ord(i)-ord('a'))

    sendData( finalList )

if __name__ == "__main__":
    main()
