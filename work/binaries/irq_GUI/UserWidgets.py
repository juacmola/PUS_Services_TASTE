#!/usr/bin/env python3
# -*- coding: utf-8 -*-

''' Edit this module at will to create custom widgets that can send TC or
    receive TM - and do anything you like with the data.
    (c) 2016-2022 European Space Agency / Maxime Perrotin
'''

import sys
import os
import importlib


from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *

from asn1_value_editor import UserWidgetsCommon

__all__ = [
    "newTC"
]

# If you want to put all widgets in a single window
#g_mdiArea = None

def user_init_pre(mainWidget):
    ''' This function is called by the auto-generated GUI before the custom
    widgets are instantiated. You may create a MDI area to place the widgets
    in, or do any initialization procedure you need.
    '''
    ...
    # An example that creates a common window and makes sure that when
    # the main GUI is closed, it is also closed
    # global g_mdiArea
    # g_mdiArea = QMdiArea()
    # mainWidget.quitApplication.connect(g_mdiArea.close)
    # print("Initializing the TASTE-RIS GUI")


def user_init_post(instances):
    ''' Called after all instances have been created '''
    ''' This function is called after the initialization of all classes
    that were created during startup, i.e. the ones that returned true to
    the call "run_at_startup"
    All created TC/TM instances are provided ; use them if you need to
    connect signals and slots between them.
    '''
    ...
    #for each in instances:
    #    g_mdiArea.addSubWindow(each)
    #    each.show()
    #    print(f"Initialized {each.name}")
    #g_mdiArea.show()


class newTC(UserWidgetsCommon.TC):
    ''' User Widget for telecommand newTC  '''
    name = 'newTC'  # name on the GUI combo button

    def __init__(self, asn1_typename, parent):
        ''' Initialise the widget '''
        #super().__init__(asn1_typename, parent)
        #self._asn1_typename = asn1_typename

        # parent is the ASN.1 value editor
        # You can use it to send the telecomamnd to the application.
        # use self.parent.asn1Instance.Set(...)  # ASN.1 API
        # to set the parameter value (if any)
        # then self.parent.updateVariable() to update the editor window
        # then optionally self.parent.sendTC() to actually send the message
        # If you need to get the value set in the editor, use:
        # self.parent.getVariable(dest=self.parent.asn1Instance)

        #self.parent = parent
        #self.setWindowTitle("TC newTC")
        #self.show()


        super().__init__(asn1_typename, parent)
        self.parent = parent
        self.setWindowTitle("TC newTC")
        layout = QVBoxLayout()

        # Service Type
        self.service = QLineEdit()
        self.service.setPlaceholderText("Service Type")
        layout.addWidget(self.service)

        # Subservice Type
        self.subservice = QLineEdit()
        self.subservice.setPlaceholderText("Subservice Type")
        layout.addWidget(self.subservice)

        # Parameter (3 bytes)
        self.param = QLineEdit()
        self.param.setPlaceholderText("Parameter (3 bytes hex)")
        layout.addWidget(self.param)

        # Send button
        self.button = QPushButton("Send TC")
        self.button.clicked.connect(self.send_telecommand)
        layout.addWidget(self.button)

        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)

        self.show()



    def send_telecommand(self):
        service = int(self.service.text())
        subservice = int(self.subservice.text())

        # Convertir parámetro hexadecimal a bytes
        param_hex = self.param.text()
        param = bytes.fromhex(param_hex)

        if len(param) != 3:
            print("ERROR: param must contain exactly 3 bytes")
            return

        # Crear ASN.1 Telecommand
        tc = self.parent.asn1Instance

        tc.Set(
            {
                "service-type": service,
                "subservice-type": subservice,
                "param": param
            }
        )

        # Actualizar editor ASN.1
        self.parent.updateVariable()

        # Enviar a TCManager
        self.parent.sendTC()


    @staticmethod
    def run_at_startup():
        ''' Return true if you want this widget to be created automatically
        when the GUI starts. This is useful to initialize a complete GUI
        replacement in combination with the user_init function that can
        create a common GUI area for all widgets '''
        return False

    @staticmethod
    def applicable():
        ''' Return True to activate this widget '''
        return False

    @staticmethod
    def editorIsApplicable(editor):
        ''' Do not change this function '''
        return editor.messageName == "newTC"

'''
class Prueba(UserWidgetsCommon.TM):
    name = 'Prueba'

    def __init__(self, parent=None):
        super().__init__(parent)
        self.parent = parent
        self.setWindowTitle("Esto es prueba")
        self.show()

    @Slot()
    def new_tm(self):
        pass #print("[Prueba] Received TC")

    def update(self, value):
        pass

    @staticmethod
    def run_at_startup():
        return True

    @staticmethod
    def applicable():
        return True

    @staticmethod
    def editorIsApplicable(editor):
        return editor.messageName == "Prueba"
'''

if __name__ == '__main__':
    print('This module can only be imported from the main TASTE guis')
    sys.exit(-1)
