#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int pinMoisture = A0;
const int pinUp = A1;
const int pinDown = A2;
const int pinMiddle = A3;
int moisture = 0;
int dryValue = 256;
int wetValue = 870;
int menuSize;
int currentMenu;
int homeMenu;
int menuDefault;
// button variables
bool up;
bool down;
bool middle;

/// setup for the code


void setup() {
  pinMode(pinUp, INPUT_PULLUP);
  pinMode(pinMiddle, INPUT_PULLUP);
  pinMode(pinDown, INPUT_PULLUP);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.write("Plant");
  display.setCursor(3,1);
  display.write("Watering");
  display.display();
  delay(3000);
  menuDefault = 1;
}


/// menue items
String lcdMenus[] = {
  "Plant Status",
  "Clock Cycle",
  "Moisture Value"
};




void loop() {
  //idk how buttons are gonna open menus
  up = ButtonPress(pinUp);
middle = ButtonPress(pinMiddle);
down = ButtonPress(pinDown);

/// change how the menue is viewed
menuDefault = changeMenu(menuDefault,up,down);
menuButtons(menuDefault);


delay(20);
}
//displays and swaps menu

void menuButtons(int selectedMenu){
  if (selectedMenu == 1)
  {
    moisture = analogRead(pinMoisture);
    Serial.println(moisture);
    if (moisture <= dryValue)
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(display.width()/2-12,2);
      display.println("Plant is too dry");
    }
    else if (moisture >= wetValue)
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(display.width()/2-12,2);
      display.println("Plant is too wet"); 
    }
    else 
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(display.width()/2-12,2);
      display.println("Plant is perfect");
    }
  }
  else if (selectedMenu == 2)
  {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(display.width()/2-12,2);
      display.println("Plant is perfect");
  }
  else if (selectedMenu == 3)
  {
      moisture = analogRead(pinMoisture);
      Serial.println(moisture);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(display.width()/2-12,2);
      display.println("Current moisture");
      display.setCursor(display.width()/2-25,2);
      display.println(moisture);
  }
}

bool ButtonPress(int pin){
  int val = analogRead(pin);
  if (val == 1023){
    return true;
  }
  else{
    return false;
  }
}


int changeMenu(int menuPrev,bool up,bool down){
  
  if(up){
    menuPrev++;
  }
  else if(down){
  menuPrev--;
  }
  else{
    return menuPrev;
  }

  menuPrev = (menuPrev > 3 ? 3 : (menuPrev < 1 ? 3 :menuPrev));
  return menuPrev;
}
