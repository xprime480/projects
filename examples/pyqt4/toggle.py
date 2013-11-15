#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
ZetCode PyQt4 tutorial

In this example, we create three toggle buttons.
They will control the background color of a
QtGui.QFrame.

author: Jan Bodnar
website: zetcode.com
last edited: September 2011
"""

import sys
from PyQt4 import QtGui

class Example(QtGui.QWidget):

    def __init__(self):
        super(Example, self).__init__()

        self.initUI()


    def initUI(self):

        self.col = QtGui.QColor(0, 0, 0)

        self.makeButton('Red')  .move(10, 10)
        self.makeButton('Green').move(10, 60)
        self.makeButton('Blue') .move(10,110)

        self.makeSquare()

        self.setGeometry(300, 300, 280, 170)
        self.setWindowTitle('Toggle button')

        self.show()

    def makeButton(self, text) :

        b = QtGui.QPushButton(text, self)
        b.setCheckable(True)
        b.clicked[bool].connect(self.setColor)

        return b

    def makeSquare(self) :

        self.square = QtGui.QFrame(self)
        self.square.setGeometry(150, 20, 100, 100)
        self.square.setStyleSheet("QWidget { background-color: %s }" %
            self.col.name())


    def setColor(self, pressed):

        source = self.sender()

        if pressed:
            val = 255
        else: val = 0

        if source.text() == "Red":
            self.col.setRed(val)
        elif source.text() == "Green":
            self.col.setGreen(val)
        else:
            self.col.setBlue(val)

        self.square.setStyleSheet("QFrame { background-color: %s }" %
            self.col.name())


def main():

    app = QtGui.QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
