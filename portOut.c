#include "common.h"

void outInitialize()
{
    LIGHT_DDR  = 0xFF; // Output 
    LIGHT_PORT = 0xFF; // Lights On
}

void setLights(uchar lights)
{
    LIGHT_PORT = lights;
}
