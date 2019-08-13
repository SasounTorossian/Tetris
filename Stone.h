#include "Display.h"

#define TE_WIDTH (DP_WIDTH - 2)
#define TE_HEIGHT (DP_HEIGHT - 2)

enum Stone_Type {
  TStone = 0,
  LStone = 1,
  IStone = 2,
  SStone = 3,
  ZStone = 5,
  OStone = 4,
};

struct Stone {
  byte field[8];
  char x = 1;           // X position of stone start
  char y = TE_HEIGHT/2; // Y position of stone start
  char rot = 0;
  Stone_Type type;
};

Stone St_InitStone();

bool St_HitTest(Stone st)
{
  for(char x = 0; x < 8; x++) // rows of Stone
  {
    for(char y = 0; y < 8; y++) // columns of Stone
    {
      if(bitRead(st.field[y],x) == 1) // Is current stone pixel set?
      {
        char xT = st.x  + x; // Absolute x Position
        char yT = st.y + y;  // Absolute y Position
        if(xT < 1 || xT > TE_WIDTH || yT < 1 || yT > TE_HEIGHT) // Out of bounds.
        {
          Serial.print("HIT OUTWINDOW xT=");
          Serial.print(xT, DEC);
          Serial.print(" yT=");
          Serial.println(yT, DEC);
          return true;
        }
        if(display.getPixel(xT,yT)) // Touching other Stone.
        {
          Serial.print("HIT Pixel xT=");
          Serial.print(xT, DEC);
          Serial.print(" yT=");
          Serial.println(yT, DEC);
          return true;
        }
      }
    }
  }
  return false;
}

void St_Print(Stone st, uint16_t color)
{
  for(char x = 0; x < 8; x++)
  {
    for(char y = 0; y < 8; y++)
    {
      if(bitRead(st.field[y],x) == 1)
      {
        char xT = st.x  + x;
        char yT = st.y + y;
        if(xT < 1 || xT > TE_WIDTH || yT < 1 || yT > TE_HEIGHT) // Current stone window
          continue;
        display.drawPixel(xT, yT, color);
      }
    }
  }
}


void St_SetRot(Stone *st, char rot)
{
  (*st).rot = rot;
  switch((*st).type)
  {
    case TStone: 
    {
      switch(rot)
      {
        case 0: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B00110000;
          (*st).field[3] = B00110000;
          (*st).field[4] = B11111100;
          (*st).field[5] = B11111100;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;

        case 1: 
        {
          (*st).field[0] = B00110000;
          (*st).field[1] = B00110000;
          (*st).field[2] = B00111100;
          (*st).field[3] = B00111100;
          (*st).field[4] = B00110000;
          (*st).field[5] = B00110000;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;

        case 2: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B11111100;
          (*st).field[3] = B11111100;
          (*st).field[4] = B00110000;
          (*st).field[5] = B00110000;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;

        case 3: 
        {
          (*st).field[0] = B00001100;
          (*st).field[1] = B00001100;
          (*st).field[2] = B00111100;
          (*st).field[3] = B00111100;
          (*st).field[4] = B00001100;
          (*st).field[5] = B00001100;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;
      }
    } break;
    
    case LStone: 
    {
      switch(rot)
      {
        case 0: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B00001100;
          (*st).field[3] = B00001100;
          (*st).field[4] = B11111100;
          (*st).field[5] = B11111100;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;

        case 1: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B00110000;
          (*st).field[3] = B00110000;
          (*st).field[4] = B00110000;
          (*st).field[5] = B00110000;
          (*st).field[6] = B00111100;
          (*st).field[7] = B00111100;
          
        } break;

        case 2: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B11111100;
          (*st).field[3] = B11111100;
          (*st).field[4] = B11000000;
          (*st).field[5] = B11000000;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;

        case 3: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B00111100;
          (*st).field[3] = B00111100;
          (*st).field[4] = B00001100;
          (*st).field[5] = B00001100;
          (*st).field[6] = B00001100;
          (*st).field[7] = B00001100;
          
        } break;
      }
    } break;
    
    case IStone: 
    {
      switch(rot)
      {
        case 0: 
        case 2: 
        {
          (*st).field[0] = B00110000;
          (*st).field[1] = B00110000;
          (*st).field[2] = B00110000;
          (*st).field[3] = B00110000;
          (*st).field[4] = B00110000;
          (*st).field[5] = B00110000;
          (*st).field[6] = B00110000;
          (*st).field[7] = B00110000;
        } break;
        
        case 1:
        case 3: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B11111111;
          (*st).field[3] = B11111111;
          (*st).field[4] = B00000000;
          (*st).field[5] = B00000000;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;
      }
    } break;
    
    case SStone: 
    {
      switch(rot)
      {
        case 0: 
        case 2:
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B11110000;
          (*st).field[3] = B11110000;
          (*st).field[4] = B00111100;
          (*st).field[5] = B00111100;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;

        case 1: 
        case 3:
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B00001100;
          (*st).field[3] = B00001100;
          (*st).field[4] = B00111100;
          (*st).field[5] = B00111100;
          (*st).field[6] = B00110000;
          (*st).field[7] = B00110000;
          
        } break;

      }
    } break;

    case OStone: 
    {
      switch(rot)
      {
        case 0: 
        case 1: 
        case 2: 
        case 3: 
        {
          (*st).field[0] = B00000000;
          (*st).field[1] = B00000000;
          (*st).field[2] = B00111100;
          (*st).field[3] = B00111100;
          (*st).field[4] = B00111100;
          (*st).field[5] = B00111100;
          (*st).field[6] = B00000000;
          (*st).field[7] = B00000000;
        } break;
      }
    } break;
    
    default: break;
  }
}

void St_Rotate(Stone *st)
{
  St_SetRot(st, ((*st).rot+1)%4);
}

void St_BackRotate(Stone *st)
{
  char rot = (*st).rot - 1;
  if(rot == -1)
  rot = 3;
  St_SetRot(st, rot);
}

//Stones not trully Random
Stone St_InitStone()
{
  Stone st;
  st.type = (Stone_Type)random(0,5);
  St_SetRot(&st, 0);
  return st;
}

