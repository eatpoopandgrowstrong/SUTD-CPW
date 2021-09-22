import SerialComm as SC
import tkinter as tk
import ctypes

import importlib

importlib.reload(SC)
'''
Idea is to have 

'''
class Mainwindow:

    def __init__(self,master):
        '''
        Throw all startup and connections here, for now 
        '''

        root.grid()

        self.TestButton = tk.Button(

            master, 
            text = "Spin 1 round",
            command = lambda: print("Hello World")

        )

        self.TestButton.grid(column = 1, row = 1)

        print("UI created")

    def ConnectToArduino():

        ArduinoPortsList = SC.ListArduinoConnectedPorts()
        SC.ConnectToArduino(ArduinoPortsList, 115200, 0.01)
        SC.WaitForArduino()
        SC.CommCheck()

        print("Connected to Arduino")


    '''
    
    '''

if __name__ == "__main__":

    ctypes.windll.shcore.SetProcessDpiAwareness(1)      # For High DPI
    print("Stage 1")
    root = tk.Tk()
    mainwindow = Mainwindow(root)
    root.mainloop()
    
    # If there is 
    
    try:
        SC.DisconnectFromArduino()              # If the Arduino has not been manually disconnected, try ser.close()
    except:                                     # Helps with plugging in and unplugging constantly
        pass


