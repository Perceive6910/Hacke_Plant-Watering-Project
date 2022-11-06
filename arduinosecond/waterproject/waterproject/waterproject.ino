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
String lcdMenus[] = {
  "Plant Status",
  "Clock Cycle",
  "Moisture Value"
};
void menuButtons(int selectedMenu, bool buttonUp, bool buttonDown, bool buttonEnterMenus){
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

int menuSize;
int currentMenu;
int homeMenu;
void setup() {
  pinMode(pinUp, INPUT_PULLUP);
  pinMode(pinMiddle, INPUT_PULLUP);
  pinMode(pinDown, INPUT_PULLUP);
}




void loop() {
  //idk how buttons are gonna open menus
  
}
