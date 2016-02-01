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
  // Try while(!Serial);
  debugprint(DEBUG_TRACE, "Setup complete!");
  digitalWrite(LEDPIN, LOW);  
}

void loop () {
  // Process the received values

  // Handle track motion/steering
  // Translate +ELEV into +LTRACK and +RTRACK (move fwd)
  // Translate -ELEV into -LTRACK and -RTRACK (move rev)
  // Translate +AIL into +LTRACK and -RTRACK (turn right)
  // Translate -AIL into -LTRACK and +RTRACK (turn left)

  // Handle camera motion
  // Translate +THRO into -TILT
  // Translate -THRO into +TILT
  // Translate +RUDD into +PAN
  // Translate -RUDD into -PAN

  // Update the outputs
}
