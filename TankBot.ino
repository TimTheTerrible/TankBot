#include <Servo.h>
#include "debugprint.h"
#include "spektrum.h"
#include "pantilt.h"
#include "tracks.h"

#define VERSION "0.0.1"

#define LEDPIN 13

#define TRACK_SPEED_PIN  4
#define TRACK_STEER_PIN  5
#define TRACK_GEAR_PIN   6

#define GIMBAL_PAN_PIN   20
#define GIMBAL_TILT_PIN  21
#define GIMBAL_ROLL_PIN  22

#define HEADLIGHT_PIN    14
#define NUM_PIXELS       12

uint32_t itsShowTime = 0;

void setup () {
  // Enable debug output
  Debug = DEBUG_NONE; // leave it at the default

  // Set up the status LED and turn it on
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);

  // Start the serial console port
  Serial.begin(115200);

  // Wait for the it to wake up
  //while(!Serial);
  
  debugprint(DEBUG_TRACE, "TankBot %s", VERSION);
  
  // Set up the receiver
  rx.begin();

  // Set up the camera gimbal
  pantilt.begin(GIMBAL_PAN_PIN, GIMBAL_TILT_PIN, GIMBAL_ROLL_PIN);
  pantilt.setPanScale(45,135);
  pantilt.setTiltScale(10,170);
  pantilt.setRollScale(10,170);

  // Set up the track driver
  tracks.begin(TRACK_SPEED_PIN, TRACK_STEER_PIN, TRACK_GEAR_PIN);
  tracks.setSpeedScale(10,170);
  tracks.setSteeringScale(10,170);

  // Set up the headlight
  pinMode(HEADLIGHT_PIN, OUTPUT);
  digitalWrite(HEADLIGHT_PIN, LOW);

  debugprint(DEBUG_TRACE, "Setup is complete!");
  
  // Shut off the status LED
  digitalWrite(LEDPIN, LOW);  
}

void showChannels ( SpektrumChannels channels) {
  debugprint(DEBUG_TRACE, "AIL  ELE  THR  RUD  GEAR AUX1 AUX2 AUX3 AUX4 AUX5 AUX6 AUX7 AUX8");
  debugprint(DEBUG_TRACE, "%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d ",
    channels.aileron, channels.elevator, channels.throttle, channels.rudder,
    channels.gear, channels.aux1, channels.aux2, channels.aux3, channels.aux4,
    channels.aux5, channels.aux6, channels.aux7, channels.aux8
  );
}
  
void loop () {
  SpektrumChannels channels = rx.getChannels();

  if ( millis() > itsShowTime ) {
    showChannels(channels);
    // Reset the delay to 1s
    itsShowTime = millis() + 1000;
  }
  
  // Handle track motion/steering
  if ( channels.gear > 1200 ) {
    tracks.setSpeed(channels.throttle);
    tracks.setSteering(channels.rudder);
  }
  else {
    tracks.setSpeed(1024);
    tracks.setSteering(1024);
  }
 
  // Handle camera motion
  pantilt.setPan(channels.aileron);
  pantilt.setTilt(channels.elevator);
  pantilt.setRoll(channels.aux1);

}
