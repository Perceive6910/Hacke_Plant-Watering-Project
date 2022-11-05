/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Writt 
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Code for joy axis
const int xanalogPin = A3;  // potentiometer wiper (middle terminal) connected to analog pin 3
const int yanalogPin = A2;  // potentiometer wiper (middle terminal) connected to analog pin 3
const int buttonPush = A0;  // for buttone pres
const int analogMin = 520;// both used for determining "dead zone"
const int analogMax = 520;
const float speed = 4; // controll speed of mouse
const int stop = 2;         // stop program if on
const int mouseSpeed = 2; // delay in miliseconds 
// outside leads to ground and +5V
int inpin =0; /// stores value if stoppin
int xval = 0;     // variable to store the value read
int yval = 0;     //store y vall
int push = 0;     // stores pushbutton value
int pressed = 0;  //prevent over doing it
int mouseX = 0; /// track mouse movement
int mouseY = 0;// track mouse movement

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  /*  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
*/
  
}

void loop() {
  xval = analogRead(xanalogPin);  // read the input pin
    yval = analogRead(yanalogPin);  // read the input pin
    push = analogRead(buttonPush);  // store button press

}
/// get mouse direction
char Direction(int val){
  char move = 0;
  
  if (val < analogMin){
    move = ((100.00*(analogMin - val))/(analogMin*100.00))*speed; 
                 
    move = move*(-1);
  }
    if (val > analogMax){
                    
    move = ((100.00*(val - analogMax))/(analogMax*100.00))*speed; 
    
  }
  return move;
}





