#include "spektrum.h"

void SpektrumRx::SpektrumRx () {
  // Set everything to default values
}

boolean SpektrumRx::begin () {
  // Set up the serial port
  Serial1.begin(115200);

  // TODO: figure out what type of tx we're bound to,
  // which is the same as saying, how many channels 
  // should we expect to decode?
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

  // Read the incoming data
  while (Serial1.available()) {

    // get the new byte:
    byte inByte = (byte)Serial1.read();

    // add it to the input buffer
    inputBuffer[++index] = inByte

    // TODO: detect the end of the message
  }
}
