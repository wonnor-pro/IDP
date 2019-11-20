import random
import time

N = 5
minedrows = []
minedcolumns = []
maprows = []
mapcolumns = []
rowsnum = N
columnsnum = N

for i in range(0, columnsnum):
    minedrows = []
    for i in range(0, rowsnum):
        minedrows.append(random.randint(-1,1))
    minedcolumns.append(minedrows)

for i in range(0, columnsnum):
    maprows = []
    for i in range(0, rowsnum):
        maprows.append(0)
    mapcolumns.append(maprows)

#The code above simply generates 2 two-dimensional arrays of the same size (where the size is dictated by the rowsnum and columnsnum parameters).
#One array has randomly generated 1s and 0s. The 1s symbolise a mine and the 0 symbolises no mine. 
#The other array is full of 0s to begin with as it records where the robot has travelled. 
#time.sleep(2) #Will use this later to mimic robot movement.

rowfinder = 0
poscolumn = 0
movecount = 0
indexfinder = len(minedrows)
rowflipper = 0

for item in minedcolumns:
    if rowflipper % 2 == 1:
        item.reverse()
    rowflipper = rowflipper + 1

for item1 in minedcolumns:
    currentindex = 0
    pos = 0
    for item2 in minedcolumns[rowfinder]:
        mapcolumns[poscolumn][pos] = 1
        pos = pos + 1
        movecount = movecount + 1
        print (movecount)
        print (minedcolumns)
        print (mapcolumns)
        currentindex = currentindex + 1
        if item2 == -1:
            print ("Rotate Mine")
            print ("Dispose Mine")
        if item2 == 1:
            print ("Dispose Mine")
        if currentindex == indexfinder:
            print ("Rotate 180")

    rowfinder = rowfinder + 1
    poscolumn = poscolumn + 1