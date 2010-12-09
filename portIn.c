#include "common.h"

void inInitialize()
{
    BTN_PORT = 0xFF; // Pull up activate
    BTN_DDR  = 0x00; // Input 
    //JOY_PORT |= 0xF0;
    //JOY_DDR  &= 0x0F;
}

void getInput()
{
    static uchar xx, yy, buttons;
 //   //read joystick
 //   if (bit_is_clear(JOY_IN,JUP))
 //   {
 //       yy = 0;
 //   }
 //   else if (bit_is_clear(JOY_IN,JDOWN))
 //   {
 //       yy = 2;
 //   }
 //   else
 //   {
 //       yy = 1;
 //   }

 //   if (bit_is_clear(JOY_IN,JLEFT))
 //   {
 //       xx = 0;
 //   }
 //   else if (bit_is_clear(JOY_IN,JRIGHT))
 //   {
 //       xx = 2;
 //   }
 //   else
 //   {
 //       xx = 1;
 //   }
 yy = 1;
 xx = 1;

    //read buttons
    buttons = ~(BTN_IN | 0b11000000);
    // file report
    reportBuffer[0] = xx;
    reportBuffer[1] = yy;
    reportBuffer[2] = buttons;
}

