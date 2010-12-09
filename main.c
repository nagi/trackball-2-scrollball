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

uchar reportBuffer[3];

	int BATcode;
	int MouseID;
	int mode=0;
	int ack;
	int mouseinf;
	int deltax;
	int deltay;
	int posx;
	int posy;
	int leftbuttonpressed;
	int middlebuttonpressed;
	int rightbuttonpressed;


int main(void)
{
	inInitialize();
	outInitialize();
	usbInitialize();

	setLights(0x00); 
  //ps2_Reset();

	wdt_reset();
	if(ps2Initialize())
	{
		setLights(0x01);
		DBG1(0x01,0,0);
	}
	else
	{
		setLights(0x02);
		DBG1(0x02,0,0);
	}

	for(;;){ 
		wdt_reset();
		usbPoll();
		getInput();
		grabbit();
		if(usbInterruptIsReady()){
			// called after every poll of the interrupt endpoint
			// This is a push to the host
			usbSetInterrupt((void *)&reportBuffer, sizeof(reportBuffer));
		}
	}
	return 0;
}

int ps2Initialize(void)
{
	DBG1(0x0A,0,0);
	BATcode=Read_ps2data();
	if(BATcode!=0xAA)return 0;		// The mouse is defect
	MouseID=Read_ps2data();       // Receive MouseID (Should be 0x00, standard mouse)
//Write_ps2data(0xEA);		      // Set stream mode
//	if(Read_ps2data()!=0xFA)      // Stream mode not supported on this mouse (like my Compaq mouse)
//	{
		Write_ps2data(0xF0);  // Set remote mode
		ack = Read_ps2data();       // Ignore acknowledge
		mode=1;
//	}
	DBG1(0x0A,&BATcode,1);
	DBG1(0x0A,&MouseID,1);
	DBG1(0x0A,&ack,1);
	DBG1(0x0A,&mode,1);
	return 1;
}

void grabbit()
{
	DBG1(0x0B,0,1);
	ack=0;
	if(mode==1)       // If remote mode
	{
		Write_ps2data(0xEB);    // Read data
		ack=Read_ps2data();
	}
	DBG1(0x0B,&ack,1);
	if((ack==0xFA)||(mode==0))  // If mouse send acknowledge or is in stream mode
	{
		mouseinf=Read_ps2data();
		deltax=Read_ps2data();
		deltay=Read_ps2data();
		if(mouseinf&0x10)deltax-=0x100;	// Add sign bit to deltax
		if(mouseinf&0x20)deltay-=0x100;	// Add sign bit to deltay
		posx+=deltax;   // Absolute X position
		posy+=deltay;   // Absolute Y position
		if(mouseinf&0x01)leftbuttonpressed=1;         // Get leftbutton status
		else leftbuttonpressed=0;
		if(mouseinf&0x04)middlebuttonpressed=1;       // Get middlebutton status
		else middlebuttonpressed=0;
		if(mouseinf&0x02)rightbuttonpressed=1;        // Get rightbutton status
		else rightbuttonpressed=0;
	}
}
