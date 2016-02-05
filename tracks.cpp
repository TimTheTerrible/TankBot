#include <Servo.h>
#include "tracks.h"
#include "debugprint.h"
#include "WProgram.h"

Tracks tracks;

bool Tracks::begin( int steeringPin, int throttlePin, int flipPin ) {
  throttle.attach(throttlePin);
  steering.attach(steeringPin);
  return true;
}

void Tracks::setSpeed(int speed) {
  debugprint(DEBUG_TRACK, "throttle set to %d", speed);
  throttle.write(map(speed, 0, 2048, 10, 170));
}

void Tracks::setSteering(int angle) {
  debugprint(DEBUG_TRACK, "steering set to %d", angle);
  steering.write(map(angle, 0, 2048, 10, 170));
}

void Tracks::setFlip(int flipIt) {
  debugprint(DEBUG_TRACK, "flip set to %d", flipIt);
  flip.write(map(flipIt, 0, 2048, 1, 180));
}

