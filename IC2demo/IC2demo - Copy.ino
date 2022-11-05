/**************************************************************************
This is the bare bones code for the arduino SD1306 screen.
you can open this on your document very easily and run it.
There are no curret comands
 
**************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


const int up = 4;
const int middle = 3;
const int down =  2;






// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! this runs befor the main loop is initialized !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void setup() {
  Serial.begin(9600);
  pinMode(up,INPUT);//set setup pin
  pinMode(middle, INPUT);
  pinMode(down, INPUT);

  //Ignore this it just makes sure that the display loops 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! This is your main loop /program the majority of your code goes here !!!!!!!!!!!!!!!!!!1!
void loop() {

   int upOn = digitalRead(up);
    int middleOn = digitalRead(middle);
    int downOn = digitalRead(down);
    
    display.clearDisplay();
    
    printButton(upOn,middleOn,downOn);
    
    display.display();
  
    delay(20);
    Serial.print(upOn)
    
    

}

int printButton(int up, int middle, int down){
  
    int x = 10;
    int y = 10;
    display.setTextSize(1);
  if( up == 1){
    
    display.setCursor(x,y);
    display.println("up activated");
    }
    if( middle == 1){
    display.setCursor(x,y-12);
    display.println("middle activated");
    
  }
  if( down == 1){
    
    display.setCursor(x,y-24);
    display.println("up activated");
    
  }
  return 0;
}
