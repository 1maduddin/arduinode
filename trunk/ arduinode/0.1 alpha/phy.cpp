/* 
 * Copyright (c) 2011, Jan Clement
 * licenced under the GPL
 *
 * Author: Jan Clement <jan.clement@audiokits.de>
 *
 * This file is part of the arduiNode library
 * http://code.google.com/p/arduinode/
 */

#include "phy.h"

/***********************************************************************
 * TO DO:                                                              *
 * crc check, byte buffer???                                           *
 ***********************************************************************/




/************************************************************************
 * sends (b-a) bytes of data, headers are filled while sending          *
 ************************************************************************/
void phySendPacket(uchar to, uchar from, uchar type, uchar *data, uchar length) {
  enableIROut(38);
  PORTB |= 1;			// led on
  sendByte(STARTSYMBOL);
  sendByte(length + 4);	// add one for the pkt length info
  sendByte(to);
  sendByte(from);
  sendByte(type);
  for(uchar i=0; i<length; i++) {
    sendByte(data[i]);	// send i data bytes
  }
  enable_rcv();		// enable ir rcv
  PORTB &= 0;			// led off
}

void printPkt() {
  uchar i = 0; // start with pkt length
  while(i < rxbuff[0] && i < RX_BUFFER_SIZE) {
    Serial.print(rxbuff[i], HEX);
    Serial.print(" ");
    i++;
  }
}
