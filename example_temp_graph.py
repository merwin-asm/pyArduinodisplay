"""
Example code for pyArduinodisplay,
This code help in ploting live temp graph of the host system onto the display!
"""

import time
import matplotlib.pyplot as plt
from main import pyArduinoDisplay

class LiveGraph:
    def __init__(self):
        self.x_values = []
        self.y_values = []
        
    def fetch_cpu_temp(self):
        try:
            with open('/sys/class/thermal/thermal_zone0/temp', 'r') as f:
                temp = int(f.read().strip()) / 1000.0  # Convert temperature from millidegrees to degrees Celsius
            return temp
        except Exception as e:
            print(f"Error fetching CPU temperature: {e}")
            return None
    
    def update_graph(self):
        temp = self.fetch_cpu_temp()
        if temp is not None:
            self.x_values.append(time.time())  # Append current timestamp
            self.y_values.append(temp)
            
        plt.figure(figsize=(0.35, 0.35))  # Resize the figure to 60x60 pixels

        plt.plot(self.x_values, self.y_values, color='white',linewidth=2)
        plt.xlabel('')
        plt.ylabel('')
        plt.title('')
        plt.legend().remove()
        plt.gca().set_facecolor('black')  # Set background color to black
        #plt.grid(color='white', linestyle='-', linewidth=0.5)  # Add white grid lines
        plt.tick_params(axis='both', which='both', bottom=False, top=False, left=False, right=False, labelbottom=False, labelleft=False)  # Hide ticks and labels

    def save_frame(self, filename):
        self.update_graph()
        plt.savefig(filename,facecolor='black', edgecolor='black')
        print(f"Saved current frame as {filename}")

if __name__ == "__main__":
    graph = LiveGraph()
    disp = pyArduinoDisplay('/dev/ttyUSB0')    
    try:
        while True:
            graph.save_frame(f"frame.png")
            
            disp.clear()
            disp.displayImage(0,0,35,35,"frame.png")
            disp.display()
            time.sleep(0.6)
    except KeyboardInterrupt:
        print("Interrupted by user")
