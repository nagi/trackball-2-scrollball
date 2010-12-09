#include "common.h"

void outInitialize()
{
	  // PB6 & PB7 are XTAL 1 and 2, so I only see 6 lights
    LIGHT_DDR  = 0xFF; // Output 
    LIGHT_PORT = 0xFF; // Lights On
}

void setLights(uchar lights)
{
    LIGHT_PORT = lights;
}
