#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "myPWMServoDriver.h"

#include "debugprint.h"
#include "spektrum.h"
#include "pantilt.h"
#include "tracks.h"

#define VERSION "0.0.1"

#define LEDPIN 13

#define TRACK_SPEED_SERVO  0
#define TRACK_STEER_SERVO  1
#define TRACK_GEAR_SERVO   2

#define GIMBAL_PAN_SERVO   4
#define GIMBAL_TILT_SERVO  5
#define GIMBAL_ROLL_SERVO  6

#define HEADLIGHT_SERVO    14

uint32_t itsShowTime = 0;

myPWMServo * headlight;

void setup () {
  // Enable debug output
  // Debug = DEBUG_TRACK;

  // Set up the status LED and turn it on
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, HIGH);

  // Start the serial console port
  Serial.begin(115200);

  // Wait for the it to wake up
  //while(!Serial);
  delay(1000);
  
  debugprint(DEBUG_TRACE, "TankBot %s", VERSION);
  
  // Set up the receiver
  rx.begin();

  // Set up the servo driver
  servoDriver.begin();  
  servoDriver.setPWMFreq(60);
    
  // Set up the camera gimbal
  pantilt.begin(GIMBAL_PAN_SERVO, GIMBAL_TILT_SERVO, GIMBAL_ROLL_SERVO);
  pantilt.setPanScale(45,135);
  pantilt.setTiltScale(10,170);
  pantilt.setRollScale(10,170);

  // Set up the track driver
  tracks.begin(TRACK_SPEED_SERVO, TRACK_STEER_SERVO, TRACK_GEAR_SERVO);
  tracks.setThrottleScale(10,170);
  tracks.setSteeringScale(10,170);

  // Set up the headlight
  headlight = servoDriver.getServo(HEADLIGHT_SERVO);
  headlight->setAngle(180); // full brightness

  debugprint(DEBUG_TRACE, "Setup is complete!");
  
  // Shut off the status LED
  digitalWrite(LEDPIN, LOW);  
}

void showChannels ( SpektrumChannels channels) {
  debugprint(DEBUG_TRACE, "\nAIL  ELE  THR  RUD  GEAR AUX1 AUX2 AUX3 AUX4 AUX5 AUX6 AUX7 AUX8");
  debugprint(DEBUG_TRACE, "%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d\n",
    channels.aileron, channels.elevator, channels.throttle, channels.rudder,
    channels.gear, channels.aux1, channels.aux2, channels.aux3, channels.aux4,
    channels.aux5, channels.aux6, channels.aux7, channels.aux8
  );
}
  
void loop () {
  SpektrumChannels channels = rx.getChannels();

  if ( millis() > itsShowTime ) {
    showChannels(channels);
    tracks.showDebug();
    pantilt.showDebug();
    
    // Reset the delay to 1s
    itsShowTime = millis() + 1000;
  }

  // Handle track motion/steering
  int gearPos = rx.switchPos(CHAN_GEAR, 3);
  
  switch ( gearPos ) {
    case 0:
      tracks.setThrottleScale(90,90);
      tracks.setSteeringScale(90,90);
      break;
    case 1:
      // Low Gear
      tracks.setThrottleScale(65,115);
      tracks.setSteeringScale(65,115);
      break;
    case 2:
      // Full throttle
      tracks.setThrottleScale(45,135);
      tracks.setSteeringScale(45,135);
      break;
    default:
      debugprint(DEBUG_ERROR, "Invalid switch position: %d", gearPos);
      break;
  }

  tracks.setThrottle(channels.throttle);
  tracks.setSteering(channels.rudder);
  //tracks.setGear(channels.gear);
 
  // Handle camera motion
  pantilt.setPan(channels.aileron);
  pantilt.setTilt(channels.elevator);
  pantilt.setRoll(channels.aux1);

  // Handle the headlight
  headlight->setAngle(channels.aux2);

}
