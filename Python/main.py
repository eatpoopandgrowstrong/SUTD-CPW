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
        SC.StartMarker = '<'
        SC.EndMarker = '>'

        root.grid()
        

        self.SpeedVar = tk.IntVar()
        self.SpeedVar.set(1)

        #master.bind("<Up>", self.up_on_press)


        self.TestButton = tk.Button(

            master, 
            text = "Spin 1 round",
            command = lambda: print(self.SpeedVar.get())

        )

        self.Level1Button = tk.Button(

            master,
            text = "Level 1",
            #command = lambda: print("Level 1 Selected")
            command = lambda: SC.ser.write("<Level1>".encode())

        )

        self.Level2Button = tk.Button(

            master,
            text = "Level 2",
            #command = lambda: print("Level 2 Selected")
            command = lambda: SC.ser.write("<Level2>".encode())

        )

        self.Level3Button = tk.Button(

            master,
            text = "Level 3",
            #   command = lambda: print("Level 3 Selected")
            command = lambda: SC.ser.write("<Level3>".encode())

        )

        self.Speed1RadioButton = tk.Radiobutton(

            master,
            text = "Speed 1",
            variable = self.SpeedVar,
            value = 1,
            #command = lambda: print("1 pressed")
            command = lambda: SC.ser.write("<Fast>".encode())
        )

        self.Speed2RadioButton = tk.Radiobutton(

            master,
            text = "Speed 2",
            variable = self.SpeedVar,
            value = 2,
            #command = lambda: print("2 pressed")
            command = lambda: SC.ser.write("<Slow>".encode())
        )


        self.Level3Button.grid(column = 0, row = 0)
        self.Level2Button.grid(column = 0, row = 1)
        self.Level1Button.grid(column = 0, row = 2)

        self.Speed1RadioButton.grid(column = 2, row = 0)
        self.Speed2RadioButton.grid(column = 2, row = 1)

        self.TestButton.grid(column = 4, row = 0)

        for x in range(4):
           
            root.grid_columnconfigure(x, weight = 1)

        for y in range(2):
          
            root.grid_rowconfigure(y, weight = 1)

        master.bind("<Up>",self.UpOnPress)
        master.bind("<KeyRelease-Up>",self.UpOnRelease)

        master.bind("<Down>",self.DownOnPress)
        master.bind("<KeyRelease-Down>",self.DownOnRelease)


        self.ConnectToArduino()
    
    def ConnectToArduino(self):

        print("Stage 2")
        ArduinoPortsList = SC.ListArduinoConnectedPorts()
        SC.ConnectToArduino(ArduinoPortsList, 115200, 0.01)
        SC.WaitForArduino()
        SC.CommCheck()

        print("Connected to Arduino")

    def UpOnPress(self, event):
        
        SC.ser.write("<Forward>".encode())
        print("Up Pressed")

    def UpOnRelease(self, event):

        print("Up Released")
        SC.ser.write("<Stop>".encode())

    def DownOnPress(self, event):
        
        SC.ser.write("<Backward>".encode())
        print("Down Pressed")

    def DownOnRelease(self, event):
        
        print("Down Released")
        SC.ser.write("<Stop>".encode())
    '''
    def SelectFast(self):

        SC.ser.write("<Fast>")

    def SelectSlow(self):

        pass
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


