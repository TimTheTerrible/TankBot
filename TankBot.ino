#include "debugprint.h"
#include "spektrum.h"

#define VERSION "0.0.1"

#define LEDPIN 13

long itsShowTime = 0;

void setup () {
  // Enable debug output
  // Debug = DEBUG_ERROR; // leave it at the default

  // Set up the status LED and turn it on
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);

  // Start the serial console port
  Serial.begin(115200);

  // Wait for the it to wake up
  while(!Serial);
  
  debugprint(DEBUG_TRACE, "TankBot %s", VERSION);
  
  // Set up the receiver
  rx.begin();

  debugprint(DEBUG_TRACE, "Setup is complete!");
  // Shut off the status LED
  digitalWrite(LEDPIN, LOW);  
}

void showChannels () {
  
  if ( millis() > itsShowTime ) {
    
    debugprint(DEBUG_TRACE, "AIL  ELE  THR  RUD  GEAR AUX1 AUX2 AUX3 AUX4");
    debugprint(DEBUG_TRACE, "%4d %4d %4d %4d %4d %4d %4d %4d %4d ",
      rx.aileron(), rx.elevator(), rx.throttle(), rx.rudder(),
      rx.gear(), rx.aux1(), rx.aux2(), rx.aux3(), rx.aux4()
    );
    
    itsShowTime = millis() + 1000;
  }
}
  
void loop () {

  showChannels();

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
