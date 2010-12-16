/* Name: main.c
 * Project: hid-mouse, a very simple HID example
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-07
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: main.c 692 2008-11-07 15:07:40Z cs $
 */

/*
This example should run on most AVRs with only little changes. No special
hardware resources except INT0 are used. You may have to change usbconfig.h for
different I/O pins for USB. Please note that USB D+ must be the INT0 pin, or
at least be connected to INT0 as well.

We use VID/PID 0x046D/0xC00E which is taken from a Logitech mouse. Don't
publish any hardware using these IDs! This is for demonstration only!
*/

#include "common.h"

uint8_t reportBuffer[5];
uint8_t i,ps2data[3];


int main(void)
{
	outInitialize();
	usbInitialize();

	setLights(0x00); 

	initTrackBall();

	for(;;){ 
		wdt_reset();
		usbPoll();
		if(usbInterruptIsReady()){
			wdt_reset();
			readTrackBall();
			fillReportBuffer();
			// called after every poll of the interrupt endpoint
			// This is a push to the host
			usbSetInterrupt((void *)&reportBuffer, sizeof(reportBuffer));
		}
	}
	return 0;
}
