#include <LiquidCrystal.h>
#include <SPI.h>
#define DP_WIDTH 128
#define DP_HEIGHT 32

Adafruit_SSD1306 display(DP_WIDTH, DP_HEIGHT, &Wire);

void Dp_Init()
{
  display.drawLine(0, 0, 127, 0, WHITE); //Line Top
  display.drawLine(0, 0, 0, 31, WHITE); //Line Left
  display.drawLine(127, 0, 127, 31, WHITE); //Line Right
  display.drawLine(0, 31, 127, 31, WHITE); //Line Bottom
}