"""
pyArduinoDisplay

This can be used to control a SSD1306 OLED Display.

Devloped by Merwin.M
"""

from PIL import Image
import numpy as np
import pickle
import time
import math
import os




class pyArduinoDisplay:
    def __init__(self, port):
        """
        Initialize the pyArduinoDisplay class with the specified serial port, baudrate, and timeout.

        Parameters:
        - port (str): The serial port to connect to (e.g., '/dev/ttyUSB0' or 'COM3').
        - baudrate (int): The baudrate for the serial communication (default is 9600).
        - timeout (float): The timeout value for the serial communication in seconds (default is 1).
        """
        self.port = port
        self.curcolorsch = 0
        """
        try:
            self.serial_connection = serial.Serial(port=self.port, baudrate=self.baudrate, timeout=self.timeout)
            print(f"Connected to {self.port} at {self.baudrate} baudrate")
        except serial.SerialException as e:
            print(f"Error: {e}")
        """
    def send(self, data):
        """
        Send data to the Arduino.

        Parameters:
        - data (str): The data to send to the Arduino.
        """
        
        try:
            os.system(f"echo \"{data}\" | sudo tee {self.port}")
            time.sleep(0.01)

        except serial.SerialException as e:
            print(f"Error sending data: {e}")
    

    def draw_pixel(self, x, y, c):
        """
        x - x
        y - y
        c - 1 or 0 , if 1 White, if 0 Black
        """
        self.send(f"{x}:{y}:{c}")


    def println(self, x, y, c1, c2, f, text):
        """
        x - x
        y - y
        c1 - foreground color
        c2 - background color
        f  - font size
        text - Text to print
        """
        self.send(f"PRINTLN:{x}:{y}:{c1}:{c2}:{f}:{text}")


    def print(self, x, y, c1, c2, f, text):
        """
        x - x
        y - y
        c1 - foreground color
        c2 - background color
        f  - font size
        text - Text to print
        """
        self.send(f"PRINT:{x}:{y}:{c1}:{c2}:{f}:{text}")



    def dim(self):
        self.send("DIM")


    def bright(self):
        self.send("BRIGHT")


    def invertColors(self, f=False):

        if self.curcolorsch == 0 and f != True:
            self.send("INVRT")
            self.curcolorsch = 1
        else:
            self.send("DEINVRT")
            self.curcolorsch = 0


    def display(self):
        self.send("DISPLAY")


    def clear(self):
        self.send("CLEAR")
   
    def resize_image(self, image_path, new_width, new_height):
        """
        Resize the image to new_width x new_height dimensions.
        """
        with Image.open(image_path) as img:
            resized_img = img.resize((new_width, new_height))
            return resized_img

    def image_to_black_and_white_array(self, image):
        """
        Convert the image to black and white and generate an array.
        Black pixels have value 0 and white pixels have value 1.
        """
        # Convert the image to grayscale
        grayscale_img = image.convert('L')
    
        # Convert grayscale image to black and white
        bw_img = grayscale_img.point(lambda x: 0 if x < 128 else 255, '1')
    
        # Convert PIL image to numpy array
        bw_array = np.array(bw_img)
    
        # Normalize array to have values of 0 and 1
        bw_array = bw_array / 255
    
        return bw_array


    def displayImage(self, x, y, height, width, img):
        """
        For displaying an Image
        x - x
        y - y
        height - modified height of the img
        width - modified width of the img
        img - path to the image
        """

        resized_image = self.resize_image(img, height, width)  # Replace 100, 100 with desired dimensions
    
        # Convert image to black and white array
        bw_array = self.image_to_black_and_white_array(resized_image)
        l = ""
        print(len(bw_array))
        for y_ in bw_array:
            for x_ in y_:
                if math.ceil(x_) == 1:
                    l+= f"{x}:{y}:"
                    #print(f"{x}:{y}:{math.ceil(x_)}")
                x += 1
            y += 1
            x = 0

        print(l)
        l = l[0:len(l)-1]
        pps = 30*3
        chunks = l.split(":")
        chunks = [":".join(chunks[i:i+2*pps]) for i in range(0, len(chunks),2*pps)]

        for chunk in chunks:
            self.send("IMG"+chunk+":")
            time.sleep(0.2)
        time.sleep(0.1)

    def playVideo(self, x, y, height, width, video):
        pass

    def createImage(self, x, y, height, width, img):
        l_ = []
        t = time.time() 
        resized_image = self.resize_image(img, height, width)  # Replace 100, 100 with desired dimensions

        # Convert image to black and white array
        bw_array = self.image_to_black_and_white_array(resized_image)

        for y_ in bw_array:
            for x_ in y_:
                if math.ceil(x_) == 1:
                    l_.append(f"{x}:{y}:{math.ceil(x_)}")
                x += 1
            y += 1
            x = 0


        # Open a file in binary write mode
        with open(f'{img}.pkl', 'wb') as file:
            # Serialize and store the list using pickle
            pickle.dump(l_, file)
        
        """
        resized_image = self.resize_image(img, height, width)  # Replace 100, 100 with desired dimensions

        # Convert image to black and white array
        bw_array = self.image_to_black_and_white_array(resized_image)

        for y_ in bw_array:
            for x_ in y_:
                l_.append(f"{x}:{y}:{math.ceil(x_)}")
                x += 1
            y += 1
            x = 0
        """
        print("ImageCreation Time :", time.time() - t)
    def showImage(self, img):
        with open(img, 'rb') as file:
            # Deserialize the list using pickle
            l_ = pickle.load(file)

        for cmd in l_:
            time.sleep(0.2)
            self.send(cmd)
        
        self.display()

    def forceStopVideo(self):
        pass


if __name__ == '__main__':
    print("Testing pyArduinoDisplay")

    disp = pyArduinoDisplay("/dev/ttyUSB0")
    #disp.invertColors(f = True)
    #disp.print(0,0,0,1,2,"hello")
    #disp.clear()
    disp.displayImage(0,0,80,70,"dog.jpg")
    disp.display()
    #disp.createImage(0,0,25,25, "shush.jpg")
    #disp.showImage("shush.jpg.pkl")
