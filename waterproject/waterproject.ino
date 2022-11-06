#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "time.h"

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int pinMoisture = A0; //pin for moisture sensor
const int pinUp = A1; //pin for up button
const int pinDown = A2; //pin for down button
const int pinMiddle = A6; //pin for middle/enter button
const int pinFan = 5; //pin for fan motor
const int pinPump = 3; //pin for water pump
const int fanTime = 4000; //time fan runs in ms
const int pumpTime = 4000; //time pump runs in ms

//moisture sensor variables
int moisture = 0; //moisture as integer value
int dryValue = 256; //integer value of moisture when too dry
int wetValue = 870; //integer value of moisture when too wet
// button variables
bool up; //up button bool
bool down; //down button bool
bool middle; //middle/enter button bool
bool menuMode; //bool for going back to main menu
int menuDefault; //menu to show on boot of board
/// store values for cyles of loop
int waterCycle = 0; //number of water cycles completed as integer
int fanCycle = 0; //number of fan cycles completed as integer

//displays and swaps menu
void menuButtons(int selectedMenu) {

  // d

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 20);
  display.println("Water");

  display.setCursor(15, 35);
  display.println("Fan");

  display.setCursor(15, 50);
  display.println("Diagnostics");


  int x = 5;
  int y = 0;
  if (selectedMenu == 1) {
    y = 20;
  }

  else if (selectedMenu == 2) {
    y = 35;
  } else if (selectedMenu == 3) {
    y = 50;
  }
  drawRect(x, y+2);
}

//// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!setup!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  pinMode(pinPump, OUTPUT);
  pinMode(pinFan, OUTPUT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Plant");
  display.setCursor(3, 20);
  display.println("Watering");
  display.display();
  delay(3000);
  menuDefault = 3;
  menuMode = false;
}
///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!loop!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void loop() {
  display.clearDisplay();
  //idk how buttons are gonna open menus
  up = ButtonPress(pinUp);
  middle = ButtonPress(pinMiddle);
  down = ButtonPress(pinDown);
  moisture = analogRead(pinMoisture);
  /// change how the menu is viewed
  if (menuMode) {
    menuDefault = changeMenu(menuDefault, up, down);
    menuButtons(menuDefault);
    if (middle) {
      menuMode = false;
    }
  } else {
    menuSelect(menuDefault);

    if (up || down) {
      menuMode = true;
    }
  }

/// check if cycles are to happen
waterCycle = runCycles(waterCycle,3600, pumpTime, pinPump);
fanCycle = runCycles(fanCycle,1800,fanTime,pinFan);
  

 
  display.display();
  waterCycle++;
  fanCycle++;
}

bool ButtonPress(int pin) {
  int val = analogRead(pin);
  if (val == 1023) {
    delay(500);
    return true;
  } else {
    return false;
  }
}


int changeMenu(int menuPrev, bool up, bool down) {

  if (up) {
    menuPrev--;
  } else if (down) {
    menuPrev++;
  } else {
    return menuPrev;
  }

  menuPrev = (menuPrev > 3 ? 1 : (menuPrev < 1 ? 3 : menuPrev));
  return menuPrev;
}

void drawRect(int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      display.drawPixel(x + j, y, SSD1306_WHITE);
    }
    y++;
  }
}

void menuSelect(int selectedMenu) {
  if (selectedMenu == 1) {
    menuOne(middle, pinPump, pumpTime);
  }

  else if (selectedMenu == 2) {
    menuTwo(middle, pinFan, fanTime);
  } else if (selectedMenu == 3) {
    diagnostics(moisture);
  }
}

void menuOne(bool button, int pinPump, int time) {
  // put your setup code here, to run once:
  // 164 by 120 (x,y)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 2);
  display.println("Would you like to");
  display.setCursor(1, 20);
  display.println("Water the Plant?");


  /// get pump
  if (button) {
    digitalWrite(pinPump, HIGH);
    delay(time);
    digitalWrite(pinPump, LOW);
  }
}
void menuTwo(bool button, int pinFan, int time) {
  // put your setup code here, to run once:
  // 164 by 120 (x,y)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 2);
  display.println("Would you like to");
  display.setCursor(1, 20);
  display.println("Fan the Plant?");


  /// get fan
  if (button) {
    digitalWrite(pinFan, HIGH);
    delay(time);
    digitalWrite(pinFan, LOW);
  }
}
void diagnostics(int moisture) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 2);
  display.println("Diagnostics");
  display.setCursor(1, 20);
  display.print("Moisture Percent: ");
  display.print(100-(moisture*100/1023));
  display.setCursor(1,40);
  display.println("Hrs since water:");
  display.setCursor(110, 40);
  display.print(String(hrs(waterCycle)));
}
