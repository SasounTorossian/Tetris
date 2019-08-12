#include "Stone.h"

#define BUTTON_LEFT 9
#define BUTTON_RIGHT 11
#define BUTTON_ROT 10
#define BUTTON_DOWN 8

bool BUTTON_LEFT_LAST = false;
bool BUTTON_RIGHT_LAST = false;
bool BUTTON_ROT_LAST = false;
bool BUTTON_DOWN_LAST = false;
long points = 0;

Stone currentStone;

void Te_Init()
{
  currentStone = St_InitStone();
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_ROT, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  digitalWrite(BUTTON_LEFT, HIGH); // turn on pullup resistors
  digitalWrite(BUTTON_RIGHT, HIGH); // turn on pullup resistors
  digitalWrite(BUTTON_ROT, HIGH); // turn on pullup resistors
  digitalWrite(BUTTON_DOWN, HIGH); // turn on pullup resistors
}

void Te_Draw()
{
  St_Print(currentStone, WHITE);
  display.display();
  St_Print(currentStone, BLACK);
}

void Te_DeleteRow(int row)
{
  for (int i = 0; i < 15; i++)
  {
    display.drawLine(row, 1, row, 30, INVERSE); //CLear line
    display.drawLine(0, 0, 127, 0, WHITE); //Line Top
    display.drawLine(0, 0, 0, 31, WHITE); //Line Left
    display.drawLine(127, 0, 127, 31, WHITE); //Line Right
    display.drawLine(0, 31, 127, 31, WHITE); //Line Bottom
    display.display();
    delay(90);
  }
  display.drawLine(row, 1, row, 30, INVERSE); //CLear line
  display.drawLine(0, 0, 127, 0, WHITE); //Line Top
  display.drawLine(0, 0, 0, 31, WHITE); //Line Left
  display.drawLine(127, 0, 127, 31, WHITE); //Line Right
  display.drawLine(0, 31, 127, 31, WHITE); //Line Bottom
  display.display();
  for (int zeile = row; zeile > 2; zeile--)
  {
    for (int y = 1; y < TE_HEIGHT + 1; y++)
    {
      display.drawPixel(zeile, y, display.getPixel(zeile - 1, y)?WHITE:BLACK);
    }
  }
}

void Te_CheckRows()
{
  byte rowWins = 0;
  for (int row = TE_WIDTH; row > 0; row--)
  {
    bool rowFull = true;
    for (int y = 1; y < TE_HEIGHT; y++)
    {
      if (!display.getPixel(row, y)) //Open piece in line
      {
        rowFull = false;
        break;
      }
    }
    if (rowFull) // Is current line full?
    {
      rowWins++;
      Te_DeleteRow(row);
      row++;
    }
  }
  // if (rowWins > 0)
  //   Te_AddPoints(random(9, 15) * (10 + pow(3,rowWins) * 10));
}

void Te_Reload()
{
  for (int row = 1; row < TE_HEIGHT + 1; row++)
  {
    display.drawLine(1, row, 30, row, WHITE);
    display.display();
    delay(60);
  }
  delay(400);
  for (int row = TE_HEIGHT; row >= 1 ; row--)
  {
    display.drawLine(1, row, 30, row, BLACK);
    display.display();
    delay(60);
  }
  currentStone = St_InitStone();
  points = 0;
}


void Te_Update(long frameCount)
{
  if (frameCount % 40  == 0)
  {
    currentStone.x++;
    if (St_HitTest(currentStone)) // Stein ist unten Angekommen.
    {
      currentStone.x--;
      for(int i = 0; i < 5; i++)
      {
        St_Print(currentStone, WHITE);
        display.display();
        delay(60);
        St_Print(currentStone, BLACK);
        display.display();
        delay(60);
      }
      St_Print(currentStone, WHITE);
      currentStone = St_InitStone();
      display.display();
      if (St_HitTest(currentStone))
      {
        // lcd.setCursor(3, 1);
        // lcd.write("Game Over!");
        // GAME OVER SCREEN
        delay(1000);
        while (!digitalRead(BUTTON_LEFT) || !digitalRead(BUTTON_RIGHT));
        Te_Reload();
      }
      // Te_AddPoints(random(1, 4) * 10);
      Te_CheckRows();
      return;
    }
  }

  if(frameCount % 10) // Allows constant press of down button
  {
    BUTTON_DOWN_LAST=false;
  }

  if (!digitalRead(BUTTON_LEFT))
  {
    Serial.println("State of BUTTON_LEFT is PRESSED");
    if (!BUTTON_LEFT_LAST)
    {
      BUTTON_LEFT_LAST = true;

      // Try to move stone once, check collision. Move again, then check collision again
      Serial.println("Current Stone y++");
      currentStone.y++;
      if (St_HitTest(currentStone))
      {
        Serial.println("Current Stone y--");
        currentStone.y--;
      }
      currentStone.y++;
      if (St_HitTest(currentStone))
      {
        Serial.println("Current Stone y--");
        currentStone.y--;
      }
    }
  }
  else BUTTON_LEFT_LAST = false;

  if (!digitalRead(BUTTON_RIGHT))
  {
    if (!BUTTON_RIGHT_LAST)
    {
      BUTTON_RIGHT_LAST = true;

      currentStone.y--;
      if (St_HitTest(currentStone))
      {
        currentStone.y++;
      }
      currentStone.y--;
      if (St_HitTest(currentStone))
      {
        currentStone.y++;
      }
    }
  }
  else BUTTON_RIGHT_LAST = false;

  if (!digitalRead(BUTTON_ROT))
  {
    if (!BUTTON_ROT_LAST)
    {
      BUTTON_ROT_LAST = true;

      // Try to move stone once, check collision. Move again, then check collision again
      St_Rotate(&currentStone);
      if (St_HitTest(currentStone))
        St_BackRotate(&currentStone);
    }
  }
  else BUTTON_ROT_LAST = false;

  if (!digitalRead(BUTTON_DOWN))
  { 
    if (!BUTTON_DOWN_LAST)
    {
      BUTTON_DOWN_LAST = true;

      // Try to move stone once, check collision. Move again, then check collision again
      currentStone.x++;
      currentStone.x++;
      if (St_HitTest(currentStone))
      {
        currentStone.x--;
        currentStone.x--;
      }
    }
  }
  else BUTTON_DOWN_LAST = false;

}

