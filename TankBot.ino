#include "debugprint.h"
#include "spektrum.h"

#define LEDPIN 13

SpektrumRx rx;

void setup () {
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);

  Serial.begin(115200);

  // Set up the receiver
  rx.begin(&Serial1);

  // Wait for the serial port(s) to wake up
  delay(1500);
  debugprint(DEBUG_TRACE, "Setup complete!");
  digitalWrite(LEDPIN, LOW);  
}

void loop () {
  if ( rx.msgReady ) {
    // Do something.
  }
}
