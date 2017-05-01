import sys
from PyQt4.QtGui import *

from cubeGui import *

class GuiBrowser(QMainWindow, Ui_Dialog):

    def __init__(self, parent=None):

        super(GuiBrowser, self).__init__(parent)
        self.setupUi(self)

        # Init to initial state
        self.cubeBtns = []
        self.initialize()
        self.actualCube = []

        #   Connect Button Signals
        self.connectAllSquares()
        self.connectAllButtons()

    #   ------------ Functions

    def initialize(self):
        print("Initializing browser")
        row0 = [self.pb_0_0_0,self.pb_0_0_1,self.pb_0_0_2]
        row1 = [self.pb_0_1_0,self.pb_0_1_1,self.pb_0_1_2]
        row2 = [self.pb_0_2_0,self.pb_0_2_1,self.pb_0_2_2]
        face0 = [row0,row1,row2]
        
        row0 = [self.pb_1_0_0,self.pb_1_0_1,self.pb_1_0_2]
        row1 = [self.pb_1_1_0,self.pb_1_1_1,self.pb_1_1_2]
        row2 = [self.pb_1_2_0,self.pb_1_2_1,self.pb_1_2_2]
        face1 = [row0,row1,row2]
        
        row0 = [self.pb_2_0_0,self.pb_2_0_1,self.pb_2_0_2]
        row1 = [self.pb_2_1_0,self.pb_2_1_1,self.pb_2_1_2]
        row2 = [self.pb_2_2_0,self.pb_2_2_1,self.pb_2_2_2]
        face2 = [row0,row1,row2]
        
        row0 = [self.pb_3_0_0,self.pb_3_0_1,self.pb_3_0_2]
        row1 = [self.pb_3_1_0,self.pb_3_1_1,self.pb_3_1_2]
        row2 = [self.pb_3_2_0,self.pb_3_2_1,self.pb_3_2_2]
        face3 = [row0,row1,row2]
        
        row0 = [self.pb_4_0_0,self.pb_4_0_1,self.pb_4_0_2]
        row1 = [self.pb_4_1_0,self.pb_4_1_1,self.pb_4_1_2]
        row2 = [self.pb_4_2_0,self.pb_4_2_1,self.pb_4_2_2]
        face4 = [row0,row1,row2]
        
        row0 = [self.pb_5_0_0,self.pb_5_0_1,self.pb_5_0_2]
        row1 = [self.pb_5_1_0,self.pb_5_1_1,self.pb_5_1_2]
        row2 = [self.pb_5_2_0,self.pb_5_2_1,self.pb_5_2_2]
        face5 = [row0,row1,row2]

        self.cubeBtns = [face0,face1,face2,face3,face4,face5]

        for b in self.cubeBtns:
            print( b )

    def connectAllSquares(self):
        print("Connecting all squares")
        for face in self.cubeBtns:
            for row in face:
                for btn in row:
                    print( "Connecting : ", btn )
                    btn.clicked.connect( lambda: self.changeColor() )

    def connectAllButtons(self):
        print("Connecting all buttons")
        self.btnScanCube.clicked.connect( lambda: self.loadCube() )
        self.btnSendData.clicked.connect( lambda: self.sendData() )


    def changeColor(self):
        print("Changing color of a button : ", self.sender())
        sender = self.sender()
        msgBox = QMessageBox()
        blueBtn = msgBox.addButton(self.tr("Blue"), QMessageBox.ActionRole)
        orngBtn = msgBox.addButton(self.tr("Orange"), QMessageBox.ActionRole)
        grnBtn = msgBox.addButton(self.tr("Green"), QMessageBox.ActionRole)
        redBtn = msgBox.addButton(self.tr("Red"), QMessageBox.ActionRole)
        whtBtn = msgBox.addButton(self.tr("White"), QMessageBox.ActionRole)
        yelBtn = msgBox.addButton(self.tr("Yellow"), QMessageBox.ActionRole)

        msgBox.exec_()

        #   Get color
        if msgBox.clickedButton() == blueBtn:
            print("Setting color to blue")
            sender.setStyleSheet("background-color:rgb(0, 0, 255)")
        elif msgBox.clickedButton() == orngBtn:
            print("Setting color to orange")
            sender.setStyleSheet("background-color:rgb(255, 140, 0)")
        elif msgBox.clickedButton() == grnBtn:
            print("Setting color to green")
            sender.setStyleSheet("background-color:rgb(0, 170, 0)")
        elif msgBox.clickedButton() == redBtn:
            print("Setting color to red")
            sender.setStyleSheet("background-color:rgb(220, 0, 0)")
        elif msgBox.clickedButton() == whtBtn:
            print("Setting color to white")
            sender.setStyleSheet("background-color:rgb(255, 255, 255)")
        else:
            print("Setting color to yel")
            sender.setStyleSheet("background-color:rgb(244, 244, 0)")
        
    def scanCube(self):
        print("Scanning cube!")
        box = self.createMessageBox()
        ret = box.exec_()
        print( ret )

    def loadCube(self):
        print("Loading data from file")
        # Read
        f1 = open('colorsOutput1.txt', 'r')
        
        # Generate array
        final_nums_list = []
        for line in f1:
            f_nums_list = [[], [], []]
            cnt = 0
            for c in line:
                if c >= '0' and c <= '5':
                    c_i = int(c)
                    f_nums_list[int(cnt/3)].append(c_i)
                    cnt += 1
            final_nums_list.append(f_nums_list)

        print ( final_nums_list)
        
        # set cube colors
        self.actualCube = final_nums_list
        print( "Loaded cube")
        print (self.actualCube)

        # set button colors
        self.setColors( self.actualCube )

        print( "Done loading")
        self.sendData()

    def setColors( self, cube ):
        
        for i in range(len(self.cubeBtns)):
            for row in range(len(self.cubeBtns[i])):
                r = []
                for btn in range(len(self.cubeBtns[i][row])):
                    #   get button color
                    color = cube[i][row][btn]
                    #   set button color
                    
                    if color == 0:
                        print("Setting color to blue")
                        self.cubeBtns[i][row][btn].setStyleSheet("background-color:rgb(0, 0, 255)")
                    elif color == 1:
                        print("Setting color to orange")
                        self.cubeBtns[i][row][btn].setStyleSheet("background-color:rgb(255, 140, 0)")
                    elif color == 2:
                        print("Setting color to green")
                        self.cubeBtns[i][row][btn].setStyleSheet("background-color:rgb(0, 170, 0)")
                    elif color == 3:
                        print("Setting color to red")
                        self.cubeBtns[i][row][btn].setStyleSheet("background-color:rgb(220, 0, 0)")
                    elif color == 4:
                        print("Setting color to white")
                        self.cubeBtns[i][row][btn].setStyleSheet("background-color:rgb(255, 255, 255)")
                    else:
                        print("Setting color to yel")
                        self.cubeBtns[i][row][btn].setStyleSheet("background-color:rgb(244, 244, 0)")

    def sendData(self):
        print("Sending cube data!")
        cube = self.getCubeData()
        # WRITING TO FILE
        f = open('colorsOutput1.txt', 'w')
        print( "seding the cube")
        print("cube")
        
        for item in cube:
            print( "Item")
            print( item )
            f.write(str(item) + "\n")

    #   ------------ Helper functions

    def createMessageBox(self):
        dialogBox = QMessageBox()
        dialogBox.setText( "Start scanning cube" )
        dialogBox.setStandardButtons(QMessageBox.Yes | QMessageBox.Cancel | QMessageBox.No)
        return dialogBox

    def getCubeData(self):
        # Get colors from button matrix and generate cube matrix
        cubeMatrix = []

        for face in self.cubeBtns:
            f = []
            for row in face:
                r = []
                for btn in row:
                    print( "Getting color :", btn )
                    print(btn.palette().color(1).getRgb())
                    red,g,b,a = btn.palette().color(1).getRgb()
                    color = self.getColor(red,g,b)
                    print( "Color :", color )
                    r.append(color)
                f.append(r)
            cubeMatrix.append(f)

        print( cubeMatrix )
        return cubeMatrix

    def getColor(self, r,g,b):
        if( r == 255 and g == 255 and b == 255 ):
            #   White
            return 4
        if( r == 0 and g == 0 and b == 255 ):
            #   Blue
            return 0
        if( r == 255 and g == 140 and b == 0 ):
            #   Orange
            return 1
        if( r == 0 and g == 170 and b == 0 ):
            #   Green
            return 2
        if( r == 220 and g == 0 and b == 0 ):
            #   Red
            return 3
        else:
            #   Yellow
            return 5
        


def window():
    app = QApplication( sys.argv )

    # Stuff begins here
    browser = GuiBrowser()
    #MainWindow = QMainWindow()
    #ui = Ui_Dialog()
    #ui.setupUi(MainWindow)
    #MainWindow.show()
    #print( "Hello world" )
    browser.show()
    sys.exit(app.exec_())

def main():
    window()

if __name__ == "__main__":
    main()
