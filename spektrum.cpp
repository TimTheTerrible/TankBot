#include <HardwareSerial.h>
#include "debugprint.h"
#include "spektrum.h"
#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

SpektrumRx rx;

int msgIndex = 0;
int rxMsgLen = MAX_MSG_LEN;
char inputBuffer[MAX_MSG_LEN];
char prevByte;

bool SpektrumRx::begin () {
  // Set up the serial port
  Serial1.begin(115200);

  // TODO: figure out what type of tx we're bound to,
  // which is the same as saying, how many channels 
  // should we expect to decode?
  
  debugprint(DEBUG_TRACE, "Receiver intialized!");
  return true;
}

void SpektrumRx::parse( char * input) {
  char bMSB[9];
  char bLSB[9];

  debugprint(DEBUG_TRACE, "Parsing new message...");
  
  // Parse the message
  debugprint(DEBUG_TRACE, "HDR: %2.2hx:%2.2hx", input[0], input[1]);
  for ( int i = 2; i < MAX_MSG_LEN; i += 2) {
    
    // What are the two bytes?
    strncpy(bMSB, byte_to_binary(input[i]), 9);
    strncpy(bLSB, byte_to_binary(input[i+1]), 9);
    debugprint(DEBUG_TRACE, "MSB: %2.2hx %s LSB: %2.2hx %s", input[i], bMSB, input[i+1], bLSB);
    
    // Assemble the bytes into a word
    long msgWord = input[i] * 256 + input[i+1];
    strncpy(bMSB, byte_to_binary(msgWord >> 8), 9);
    strncpy(bLSB, byte_to_binary(msgWord & 0x0FFF), 9);
    debugprint(DEBUG_TRACE, "msgWord: %4.4hx %s:%s", msgWord, bMSB, bLSB);

    // Calculate the channel number and value
    int channelNum = ( msgWord & 0xF000 ) >> 12;
    int channelVal = msgWord & 0x0FFF;
    debugprint(DEBUG_TRACE, "CHAN: %4.4d VAL: %4.4d", channelNum, channelVal);
    // 0 2 1 
  }
}

int SpektrumRx::aileron() {
  return m_aileron;
}

int SpektrumRx::elevator() {
  return m_elevator;
}

int SpektrumRx::rudder() {
  return m_rudder;
}

int SpektrumRx::throttle() {
  return m_throttle;
}

int SpektrumRx::aux1() {
  return m_aux1;
}

int SpektrumRx::aux2() {
  return m_aux2;
}

int SpektrumRx::aux3() {
  return m_aux3;
}

int SpektrumRx::aux4() {
  return m_aux4;
}

int SpektrumRx::aux5() {
  return m_aux5;
}

/*
 * Serial Port Handler
 */

void serialEvent1() {
  //debugprint(DEBUG_TRACE, "serialEvent()!");

  // Read the incoming data
  while (Serial1.available()) {

    // get the new byte:
    char inByte = (char)Serial1.read();

    // add it to the input buffer
    inputBuffer[msgIndex++] = inByte;
  }

  if ( msgIndex == rxMsgLen ) {
    rx.parse(inputBuffer);
    msgIndex = 0;
  }
}
