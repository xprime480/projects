#!/usr/bin/python3

# pqt_tooltip1.py
# exploring PyQT's tooltip and color text (html)
# Henri
import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
class Tooltip(QWidget):
    def __init__(self, parent=None):
        QWidget.__init__(self, parent)
        # setGeometry(x_pos, y_pos, width, height)
        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Tooltip')
        btn_hello = QPushButton("Push Button")
        btn_hello.setToolTip('Press <b>me</b> for the greeting')
        self.connect(btn_hello, SIGNAL("clicked()"), self.on_click)
        self.label = QLabel()
        grid = QGridLayout()
        grid.addWidget(btn_hello, 0, 0, 1, 1)
        grid.addWidget(self.label, 1, 0, 1, 3)
        self.setLayout(grid)
    def on_click(self):
        s = "<font size=6 color='red'>Hello stranger!</font>"
        self.label.setText(s)
app = QApplication(sys.argv)
tooltip = Tooltip()
tooltip.show()
app.exec_()
