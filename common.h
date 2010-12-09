#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"
#include "oddebug.h"        /* This is also an example for using debug macros */

#include "ps2.h"
#include "ps2mouse.h"

/* Carfull if you change these. inInitialize() assumes the button port is used for buttons exclusively, and that the joystick port uses the top four pins. */
//	#define JOY_PORT   PORTD
//	#define JOY_DDR    DDRD
//	#define JOY_IN     PIND
//	#define JUP     PIND4
//	#define JDOWN   PIND5
//	#define JLEFT   PIND6
//	#define JRIGHT  PIND7

#define BTN_PORT   PORTC
#define BTN_IN     PINC
#define BTN_DDR    DDRC
#define FM0     PINC0
#define FM1     PINC1
#define FM2     PINC2
#define FM3     PINC3
#define FM4     PINC4
#define JFIRE   PINC5

#define LIGHT_PORT   PORTB
#define LIGHT_IN     PINB
#define LIGHT_DDR    DDRB
#define L1      PB1
#define L2      PB2
#define L3      PB3
#define L4      PB4
#define L5      PB5

//====================================================================
extern uchar reportBuffer[3];
//====================================================================
extern usbMsgLen_t usbFunctionSetup(uchar data[8]);
//====================================================================
extern void inInitialize(void);
extern void getInput(void);
extern void testFillReport(void);
//====================================================================
extern void outInitialize(void);
extern void setLights(uchar lights);
//====================================================================
extern void usbInitialize(void);
extern void sendOutput(void);
