#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



// Define relay pin
const int relayPin = 26;


// Define led pins
const int ledPin1 = 22;
const int ledPin2 = 23;
const int ledPin3 = 24;
const int ledPin4 = 25;


// Define button pins
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 4;
const int buttonPin4 = 5;

// Variables to store button states
int buttonState1 = HIGH;
int buttonState2 = HIGH;
int buttonState3 = HIGH;
int buttonState4 = HIGH;

// Previous button states
int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
int lastButtonState3 = HIGH;
int lastButtonState4 = HIGH;



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  9 //D1
#define OLED_CLK   10 // D0
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

String data = "";  // Variable to store incoming serial data


struct ParsedValues {
  int X, Y, Z1, Z2;
  float A;
  String T;
};

ParsedValues parseInput(String input);
void printParsedValues(ParsedValues values);



void setup() {
Serial.begin(115200);

pinMode(relayPin, OUTPUT);


pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(ledPin4, OUTPUT);

// Initialize button pins as inputs with pull-up resistors
pinMode(buttonPin1, INPUT_PULLUP);
pinMode(buttonPin2, INPUT_PULLUP);
pinMode(buttonPin3, INPUT_PULLUP);
pinMode(buttonPin4, INPUT_PULLUP);

display.begin(SSD1306_SWITCHCAPVCC);
display.clearDisplay();
display.dim(true);
display.display();
}

void loop() {


  while (Serial.available() > 0) {
    
    String data = Serial.readStringUntil('\n'); // Read data from Serial Monitor

    if (data.length() > 0) {
      
      if (data == "CLEAR") {
      Serial.println("CLEAR - CMD");
      display.clearDisplay();
      display.display();
      }
        
      else if (data == "led1-on") {
                digitalWrite(ledPin1, HIGH);

      }
            else if (data == "led2-on") {
                digitalWrite(ledPin2, HIGH);

      }
            else if (data == "led3-on") {
                digitalWrite(ledPin3, HIGH);

      }
            else if (data == "led4-on") {
                digitalWrite(ledPin4, HIGH);

      }
            else if (data == "led1-off") {
                digitalWrite(ledPin1, LOW);

      }
            else if (data == "led2-off") {
                digitalWrite(ledPin2, LOW);

      }
            else if (data == "led3-off") {
                digitalWrite(ledPin3, LOW);

      }
                  else if (data == "led4-off") {
                digitalWrite(ledPin4, LOW);

      }
                  else if (data == "relay-on") {
                digitalWrite(relayPin, HIGH);

      }
                        else if (data == "relay-off") {
                digitalWrite(relayPin, LOW);

      }
       else if (data == "DISPLAY"){
        Serial.println("DISPLAY - CMD");
        display.display();
      }

              else if (data == "INVRT"){
        Serial.println("INVRT - CMD");
        display.invertDisplay(true);
     display.clearDisplay();
        display.setTextSize(2); 
                display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.setCursor(0, 0);
      display.println("INVT");

      }
        else if (data == "DEINVRT"){
        Serial.println("DEINVRT - CMD");
        display.invertDisplay(false);
      }
             else if (data == "DIM"){
        Serial.println("DIM - CMD");
        display.dim(1);
      }
                   else if (data == "BRIGHT"){
        Serial.println("BRIGHT - CMD");
        display.dim(0);
      }

       else if (data.startsWith("IMG") ) { // Check if the received string starts with "IMG"
               Serial.println("IMG - CMD");

           String dataString = data.substring(3);  // Remove "IMG" from the beginning
      processData2(dataString);  // Process the remaining data

    }

      else if (data.startsWith("PRINTLN:")){

        Serial.println("PRINTLN - CMD"); 

        ParsedValues parsedValues = parseInput(data);
        
        Serial.println(parsedValues.X);
        Serial.println(parsedValues.Y);
        Serial.println(parsedValues.Z1);
        Serial.println(parsedValues.Z2);
        Serial.println(parsedValues.A);
        Serial.println(parsedValues.T);
        Serial.println("................");

        display.clearDisplay();
        display.setTextSize(parsedValues.A); 
      if (parsedValues.Z1 == 1){
      if (parsedValues.Z2 == 0){
        display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

      }
      else{
        display.setTextColor(SSD1306_WHITE, SSD1306_WHITE);

      }
      }
      if (parsedValues.Z1 == 0){
      if (parsedValues.Z2 == 0){
        display.setTextColor(SSD1306_BLACK, SSD1306_BLACK);

      }
      else{
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);

      }
      }
      display.setCursor(parsedValues.X, parsedValues.Y);
      display.println(parsedValues.T);
        }
      
      else if (data.startsWith("PRINT:")){

        Serial.println("PRINT - CMD"); 

        ParsedValues parsedValues = parseInput(data);
        
        Serial.println(parsedValues.X);
        Serial.println(parsedValues.Y);
        Serial.println(parsedValues.Z1);
        Serial.println(parsedValues.Z2);
        Serial.println(parsedValues.A);
        Serial.println(parsedValues.T);
        Serial.println("................");

        display.clearDisplay();
        display.setTextSize(parsedValues.A); 
      if (parsedValues.Z1 == 1){
      if (parsedValues.Z2 == 0){
        display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);

      }
      else{
        display.setTextColor(SSD1306_WHITE, SSD1306_WHITE);

      }
      }
      if (parsedValues.Z1 == 0){
      if (parsedValues.Z2 == 0){
        display.setTextColor(SSD1306_BLACK, SSD1306_BLACK);

      }
      else{
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);

      }
      }
      display.setCursor(parsedValues.X, parsedValues.Y);
      display.print(parsedValues.T);
        }
    
        
    
    else{
            Serial.println("PIXEL - CMD");


      int x, y, z;
      sscanf(data.c_str(), "%d:%d:%d", &x, &y, &z); // Parse the data

      // Call the xyz function with x, y, and z integers
  display.setCursor(0, 0);
  if (z == 1){
  display.drawPixel(x, y, SSD1306_WHITE);
  }
  else{
  display.drawPixel(x, y, SSD1306_BLACK);
  }
    }
    
  
}
}

 // Read button states
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  // Check if button 1 is pressed
  if (buttonState1 == LOW && lastButtonState1 == HIGH) {
    Serial.println("on:1");
    lastButtonState1 = LOW;
  } else if (buttonState1 == HIGH && lastButtonState1 == LOW) {
    Serial.println("off:1");
    lastButtonState1 = HIGH;
  }

  // Check if button 2 is pressed
  if (buttonState2 == LOW && lastButtonState2 == HIGH) {
    Serial.println("on:2");
    lastButtonState2 = LOW;
  } else if (buttonState2 == HIGH && lastButtonState2 == LOW) {
    Serial.println("off:2");
    lastButtonState2 = HIGH;
  }

  // Check if button 3 is pressed
  if (buttonState3 == LOW && lastButtonState3 == HIGH) {
    Serial.println("on:3");
    lastButtonState3 = LOW;
  } else if (buttonState3 == HIGH && lastButtonState3 == LOW) {
    Serial.println("off:3");
    lastButtonState3 = HIGH;
  }

  // Check if button 4 is pressed
  if (buttonState4 == LOW && lastButtonState4 == HIGH) {
    Serial.println("on:4");
    lastButtonState4 = LOW;
  } else if (buttonState4 == HIGH && lastButtonState4 == LOW) {
    Serial.println("off:4");
    lastButtonState4 = HIGH;
  }

  // Add a small delay to debounce the buttons
  delay(50);
}

ParsedValues parseInput(String input) {
  ParsedValues values;
  
  char charBuf[input.length() + 1];
  input.toCharArray(charBuf, input.length() + 1);
  
  char *token = strtok(charBuf, ":");
  
  if(token != NULL) {
    // First token is ignored as it's the "PRINTLN" command
    token = strtok(NULL, ":");
    
    if(token != NULL) values.X = atoi(token);
    token = strtok(NULL, ":");
    
    if(token != NULL) values.Y = atoi(token);
    token = strtok(NULL, ":");
    
    if(token != NULL) values.Z1 = atoi(token);
    token = strtok(NULL, ":");
    
    if(token != NULL) values.Z2 = atoi(token);
    token = strtok(NULL, ":");
    
    if(token != NULL) values.A = atof(token);
    token = strtok(NULL, ":");
    
    if(token != NULL) values.T = String(token);
  }
  
  return values;

}

void processData2(String data) {
  int colonIndex;
  String x, y;
  
  while ((colonIndex = data.indexOf(':')) != -1) {  // Loop until no more ':' is found
    x = data.substring(0, colonIndex);  // Extract x value
    data.remove(0, colonIndex + 1);  // Remove the extracted x value and the ':'
    
    if ((colonIndex = data.indexOf(':')) != -1) {  // Check if another ':' exists
      y = data.substring(0, colonIndex);  // Extract y value
      data.remove(0, colonIndex + 1);  // Remove the extracted y value and the ':'
      
      xy(x.toInt(), y.toInt());  // Convert x and y to integers and call the xy function
    }
  }
}


void xy(int x, int y) {
  // Your function to handle x and y values
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(", y: ");
  Serial.println(y);

  // display.setCursor(0, 0);
  display.drawPixel(x, y, SSD1306_WHITE);
  // display.display();
}


