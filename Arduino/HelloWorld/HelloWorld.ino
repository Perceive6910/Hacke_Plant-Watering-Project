#include <Arduboy2.h>

/*
Hello, World! example
June 11, 2015
Copyright (C) 2015 David Martinez
All rights reserved.
This code is the most basic barebones code for writing a program for Arduboy.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
*/


// make an instance of arduboy used for many functions
Arduboy2 arduboy;


// This function runs once in your game.
// use it for anything that needs to be set only once in your game.
void setup() {
  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(15);
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  static uint8_t fcnt = 0;
  static uint8_t dtime = 0;

  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // first we clear our screen to black
  arduboy.clear();

  // we set our cursor 5 pixels to the right and 10 down from the top
  // (positions start at 0, 0)
  arduboy.setCursor(4, 9);

  // then we print to screen what is in the Quotation marks ""
  arduboy.print(F("VidTest: "));
  arduboy.print(fcnt>>4);
  arduboy.print(F("\nms/frame: "));
  arduboy.print(dtime);
  arduboy.print(F("\nfps: "));
  arduboy.print(1000/dtime);

  fcnt++;
  if(fcnt & 0x0f == 0x0f) {
    arduboy.invert((fcnt & 0x10));   
    arduboy.allPixelsOn((fcnt & 0x20));   
    arduboy.flipVertical((fcnt & 0x40));   
    arduboy.flipHorizontal((fcnt & 0x80));   
  }

  // then we finaly we tell the arduboy to display what we just wrote to the display
  dtime = millis();
  arduboy.display();
  dtime = millis() - dtime;
}