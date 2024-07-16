# pyArduinoDisplay

 <p align="right"> <img src="https://komarev.com/ghpvc/?username=merwin-asm-april&label=Project%20views&color=0e75b6&style=flat" /> </p>

## Overview

`pyArduinoDisplay` is a Python module designed to control an SSD1306 OLED Display connected to an Arduino from the host device. This module allows you to send various commands to the Arduino to manipulate the display, such as drawing pixels, printing text, and displaying images.

**Developed by:** Merwin.M

## Installation

To use `pyArduinoDisplay`, ensure you have the necessary libraries installed:
```bash
pip install pillow numpy
```
then copy the modules code from pyarduinodisplay.py!

## Directory Structure

| File/Directory        | Description                                    |
|-----------------------|------------------------------------------------|
| `pyarduinodisplay.py` | Python module containing the display control logic. |
| `arduino/arduino.ino` | Arduino sketch to handle commands from the host. |
| `example_temp_graph.py` | Example script to display a live temperature graph on the SSD1306 OLED display. |


## Supported Displays

| Display Model          | Description                                    |
|------------------------|------------------------------------------------|
| `SSD1306 OLED Display` | A popular 128x64 pixel OLED display.            |

## Arduino Code

Ensure your Arduino is flashed with the code found in `arduino/arduino.ino`.

```cpp
// Arduino Code (arduino/arduino.ino)
// Add your Arduino code here
```
## Python Module

### Class: `pyArduinoDisplay`

#### Initialization
```python
pyArduinoDisplay(port)
```

- **Parameters:**
  - `port` (str): The serial port to connect to (e.g., '/dev/ttyUSB0' or 'COM3').


#### Methods

| Method                   | Description                                                                                                 |
|--------------------------|-------------------------------------------------------------------------------------------------------------|
| `send(data)`             | Send data to the Arduino.                                                                                   |
| `draw_pixel(x, y, c)`    | Draw a pixel at (x, y) with color `c` (1 for white, 0 for black).                                           |
| `println(x, y, c1, c2, f, text)` | Print text at (x, y) with foreground color `c1`, background color `c2`, and font size `f`.             |
| `print(x, y, c1, c2, f, text)`   | Print text at (x, y) with foreground color `c1`, background color `c2`, and font size `f`.             |
| `dim()`                  | Dim the display.                                                                                            |
| `bright()`               | Brighten the display.                                                                                       |
| `invertColors(f=False)`  | Invert the display colors.                                                                                  |
| `display()`              | Refresh the display to show any changes.                                                                    |
| `clear()`                | Clear the display.                                                                                          |
| `resize_image(image_path, new_width, new_height)` | Resize the image to new dimensions.                                                  |
| `image_to_black_and_white_array(image)` | Convert the image to a black and white array.                                                      |
| `displayImage(x, y, height, width, img)` | Display an image at (x, y) with specified dimensions.                                                |
| `playVideo(x, y, height, width, video)` | Play a video (method not implemented).                                                          |
| `createImage(x, y, height, width, img)` | Create an image and store it as a serialized object.                                               |
| `showImage(img)`         | Show a previously created image.                                                                             |
| `forceStopVideo()`       | Stop playing a video (method not implemented).                                                               |

### Example Code

An example script `example_temp_graph.py` is provided to display a live temperature graph on the SSD1306 OLED display. See the [Example Code](#example-code) section for details on how to use it.

## Usage

1. Upload the Arduino sketch (`arduino/arduino.ino`) to your Arduino board.
2. Install the required Python libraries.
3. Run the example script `example_temp_graph.py` to see the live temperature graph on the OLED display.

## License

This project is licensed under the MIT License.
