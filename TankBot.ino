#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
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

#define NUM_PIXELS         12
#define HEADLIGHT_PIN      2

Adafruit_NeoPixel headlight = Adafruit_NeoPixel(NUM_PIXELS, HEADLIGHT_PIN, NEO_GRB + NEO_KHZ800);

uint32_t debugInterval = 0;

uint8_t oldHeadlightPos = -1;

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
  pantilt.setTiltScale(45,135);
  pantilt.setRollScale(0,180);

  // Set up the track driver
  tracks.begin(TRACK_SPEED_SERVO, TRACK_STEER_SERVO, TRACK_GEAR_SERVO);
  tracks.setThrottleScale(10,170);
  tracks.setSteeringScale(10,170);

  // Set up the headlight
  headlight.begin();
  
  debugprint(DEBUG_TRACE, "headlight.numPixels() = %d", headlight.numPixels());
  
  uint32_t color = headlight.Color(128,128,128);
  
  for ( uint8_t i = 0; i < headlight.numPixels(); i++ ) {
    headlight.setPixelColor(i, color);
  }
  headlight.show();

  debugprint(DEBUG_TRACE, "Setup is complete!");
  
  // Shut off the status LED
  digitalWrite(LEDPIN, LOW);  
}

void showChannels ( SpektrumChannels channels) {
  debugprint(DEBUG_TRACE, "\nAIL  ELE  THR  RUD  GEAR AUX1 AUX2 AUX3 AUX4 AUX5 AUX6 AUX7 AUX8");
  debugprint(DEBUG_TRACE, "%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d",
    channels.aileron, channels.elevator, channels.throttle, channels.rudder,
    channels.gear, channels.aux1, channels.aux2, channels.aux3, channels.aux4,
    channels.aux5, channels.aux6, channels.aux7, channels.aux8
  );
}
  
void loop () {
  SpektrumChannels channels = rx.getChannels();

  if ( millis() > debugInterval ) {
    showChannels(channels);
    tracks.showDebug();
    pantilt.showDebug();
    debugprint(DEBUG_TRACE, "Last Headlight Setting: %d", oldHeadlightPos);
    
    // Reset the delay to 1s
    debugInterval = millis() + 1000;
  }

  // Handle track motion/steering
  uint8_t gearPos = rx.switchPos(CHAN_GEAR, 3);
  
  switch ( gearPos ) {
    case 0:
      // Park
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
      debugprint(DEBUG_ERROR, "Invalid gear switch position: %d", gearPos);
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
  uint8_t headlightPos = rx.switchPos(CHAN_AUX2, 3);
  
  if ( headlightPos != oldHeadlightPos ) {
    debugprint(DEBUG_TRACE, "headlight switch changed!");
    switch ( headlightPos ) {
      case 0:
        // Off
        headlight.setBrightness(64);
        break;
      case 1:
        // Low brightness
        headlight.setBrightness(128);
        break;
      case 2:
        // Full brightness
        headlight.setBrightness(255);
        break;
      default:
        debugprint(DEBUG_ERROR, "Invalid headlight switch position: %d", headlightPos);
        break;
    }
    headlight.show();
    oldHeadlightPos = headlightPos;
  }
}
