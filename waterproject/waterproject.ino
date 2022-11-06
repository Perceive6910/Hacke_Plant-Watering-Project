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

const int pinMoisture = A0;
const int pinUp = A1;
const int pinDown = A2;
const int pinMiddle = A6;
const int pinFan = 2;
const int pinPump = 3;

const int fanTime = 4000;
const int pumpTime = 4000;



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
int buttonPressCount = 1;  //number of button presses
int buttonItem = 0;        //current item button is on
int lastButtonItem = 0;    //last button item
bool menuMode;
/// store values for cyles of loop
int waterCycle = 0;
int fanCycle = 0;

/// menu items
String lcdMenus[] = {
  "Plant Status",
  "Clock Cycle",
  "Moisture Value"
};

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

template< typename T, size_t NumberOfSize >
size_t MenuItemsSize(T (&)[NumberOfSize]) {
  return NumberOfSize;
}
int menuItems = MenuItemsSize(lcdMenus) - 1;
int currentMenuItem = 0;
//// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!setup!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  //pinMode(pinUp, INPUT_PULLUP);
  // pinMode(pinMiddle, INPUT_PULLUP);
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
    diagnostics();
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
void diagnostics() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 2);
  display.println("diagnostics");
  display.setCursor(1, 20);
  display.print("Moisture: ");
  display.println((100-((moisture/100)*100)));
}
