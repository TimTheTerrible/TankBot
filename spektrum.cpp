#include <HardwareSerial.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debugprint.h"
#include "spektrum.h"

SpektrumRx rx;

int msgIndex = 0;
int rxMsgLen = MAX_MSG_LEN;
char inputBuffer[MAX_MSG_LEN];
char prevByte;

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

/*
 * SpektrumRx Class Methods
 */

bool SpektrumRx::begin () {
  // Set up the serial port
  Serial1.begin(115200);

  // TODO: figure out what type of tx we're bound to,
  // which is the same as saying, how many channels 
  // should we expect to decode?
  
  debugprint(DEBUG_TRACE, "Receiver intialized!");
  return true;
}

void SpektrumRx::parse( uint8_t * input) {
  char bMSB[9];
  char bLSB[9];
  char bWord[17];

  debugprint(DEBUG_TRACE, "Parsing new message...");
  
  debugprint(DEBUG_TRACE, "HDR: %2.2hx:%2.2hx", input[0], input[1]);

  for ( int i = 2; i < MAX_MSG_LEN; i += 2) {
    
    // What are the two bytes?
    strncpy(bMSB, byte_to_binary(input[i]), 9);
    strncpy(bLSB, byte_to_binary(input[i+1]), 9);
    debugprint(DEBUG_TRACE, "MSB: %2.2hx %s LSB: %2.2hx %s", input[i], bMSB, input[i+1], bLSB);
    
    // Assemble the bytes into a word
    uint16_t msgWord = input[i] << 8; msgWord = msgWord | input[i+1];
    strncpy(bWord, word_to_binary(msgWord), 17);
    debugprint(DEBUG_TRACE, "msgWord: %4.4hx %s", msgWord, bWord);

    // Calculate the channel number and value
    int channelNum = ( msgWord & SRX_CHAN_MASK ) >> SRX_VAL_MASK_LEN;
    int channelVal = msgWord & SRX_VAL_MASK;
    debugprint(DEBUG_TRACE, "CHAN: %4d VAL: %4d", channelNum, channelVal);

    // TODO: clean up the value of channelVal

    // Store the value in a channel
    switch ( channelNum ) {
      case CHAN_AILERON:
        m_aileron = channelVal;
        break;
      case CHAN_ELEVATOR:
        m_elevator = channelVal;
        break;
      case CHAN_THROTTLE:
        m_throttle = channelVal;
        break;
      case CHAN_RUDDER:
        m_rudder = channelVal;
        break;
      case CHAN_AUX1:
        m_aux1 = channelVal;
        break;
      case CHAN_AUX2:
        m_aux2 = channelVal;
        break;
      case CHAN_AUX3:
        m_aux3 = channelVal;
        break;
      case CHAN_AUX4:
        m_aux4 = channelVal;
        break;
      case CHAN_AUX5:
        m_aux5 = channelVal;
        break;
      default:
        deubgprint(DEBUG_ERROR, "Invalid channel number: %d", channelNum);
        break;
    }
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

