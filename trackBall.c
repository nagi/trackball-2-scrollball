#include "common.h"

uint8_t horizSignBit;
uint8_t vertSignBit;
int8_t PIX_TILL_SCROLL = 3;
int8_t posVert = 0; 
int8_t posHoriz = 0;

void initTrackBall(void){
	send_packet(0xff);
	read_packet(); //Ack
	read_packet(); //Bat
	read_packet(); //dev ID
	////
	send_packet(0xf4); //Enable Data reporting
	read_packet();	// Ack
	////
	//send_packet(0xe8); //Set Resolution
	//read_packet(); //Ack
	//send_packet(0x01); //8counts/mm
	//read_packet(); //Ack
	////
	//send_packet(0xf3); //SetSample rate
	//read_packet(); //Ack
	//send_packet(0x64); //200 smaples a second
	send_packet(0xf0); //Set remote mode
	read_packet(); //Ack
}

void readTrackBall(){
	send_packet(0xeb);
	read_packet(); //Ack
	for(i=0;i<3;i++){
		ps2data[i]=read_packet();
	}
	DBG1(0xDD,ps2data,3);
}

void fillReportBuffer(){
/*
   /-----------------------------------------------------------------------------------------------------------\
   |       | Bit 7      | Bit 6      | Bit 5      | Bit 4      | Bit 3     | Bit 2      | Bit 1     | Bit 0    |
   |-----------------------------------------------------------------------------------------------------------|
   |Byte 0 | Y overflow | X overflow | Y sign bit | X sign bit | Always 1  | Middle Btn | Right Btn | Left Btn |
   |-----------------------------------------------------------------------------------------------------------|
   |Byte 1 |      x movement without the sign bit                                                              |
   |-----------------------------------------------------------------------------------------------------------|
   |Byte 2 |      y movement without the sign bit                                                              |
   \-----------------------------------------------------------------------------------------------------------/  */

	// Fish usefull stuff out of first byte
	reportBuffer[0] = (0b00000001 & ps2data[0]); // Left Click Button
	reportBuffer[0] |= (0b00000010 & ps2data[0]); // Right Click Button

	/* The mouse can sends 9bit signed numbers (as per the PS/2 mouse protocol 
	 * specification), and my device descriptor specifies 8bit signed integers.
	 * In practice, I can't get my trackball to use all nine bits even if I spin
	 *  the trackball really fast, I'm just going to squish the 9bits into the 
	 *  8bit report by ignoreing the unused bit. */

	horizSignBit = (ps2data[0] & 0b00010000) << 3;
	vertSignBit  = (ps2data[0] & 0b00100000) << 2;

	posHoriz = (ps2data[1] & 0b01111111) | horizSignBit;
	posVert  = (ps2data[2] & 0b01111111) | vertSignBit;

  reportBuffer[3] = posVert / PIX_TILL_SCROLL;
  reportBuffer[4] = posHoriz / PIX_TILL_SCROLL;

	/* I don't want to send Vertical & Horizontal scroll messages at the same time,
	 * so if the mouse is moving generlly vertically, then don't send horizontal scroll
	 * info in the report */

	if(posVert < 0) posVert = posVert * -1;
	if(posHoriz < 0) posHoriz = posHoriz * -1;

	if(posVert > posHoriz){
		reportBuffer[4] = 0;
	}
	else if (posHoriz > posVert) {
		reportBuffer[3] = 0;
	}
	else {
		reportBuffer[3] = 0;
		reportBuffer[4] = 0;
	}

	DBG1(0xDE,&horizSignBit,1);
	DBG1(0xDE,&posHoriz,1);
	DBG1(0xDE,&vertSignBit,1);
	DBG1(0xDE,&posVert,1);
}
