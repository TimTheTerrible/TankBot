#include <Servo.h>
#include "pantilt.h"
#include "WProgram.h"

PanTilt pantilt;

bool PanTilt::begin( int panPin, int tiltPin, int rollPin ) {
  pan.attach(panPin);
  tilt.attach(tiltPin);
  roll.attach(rollPin);
  return true;
}

void PanTilt::setPan( int angle ) {
  pan.write(map(angle, 2048, 0, 45, 135));
}

void PanTilt::setTilt( int angle ) {
  tilt.write(map(angle, 2048, 0, 10, 170));
}

void PanTilt::setRoll( int angle ) {
  roll.write(map(angle, 0, 2048, 10, 170));
}

