#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include "Tetris.h"

//TODO: Refactor Code: Renames, Convert from .ino, to .cpp. Use correct form of headers

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  //TODO: Add name
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  Dp_Init();
  Te_Init();
}


byte xC = 0;
byte yC = 0;
long frameCount = 0;

void loop() {
  frameCount++;
  Te_Draw();
  Te_Update(frameCount);
  delay(1);
}
