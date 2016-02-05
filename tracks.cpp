#include <Servo.h>
#include "tracks.h"
#include "debugprint.h"
#include "WProgram.h"

Tracks tracks;

bool Tracks::begin( int steeringPin, int throttlePin, int gearPin ) {
  throttle.attach(throttlePin);
  steering.attach(steeringPin);
  gear.attach(gearPin);
  return true;
}

void Tracks::setSpeed(int speed) {
  debugprint(DEBUG_TRACK, "throttle set to %d", speed);
  throttle.write(map(speed, 0, 2048, m_speedScaleMin, m_speedScaleMax));
}

void Tracks::setSpeedScale(int min, int max) {
  debugprint(DEBUG_TRACK, "throttle scale set to (%d,%d)", min, max);
  m_speedScaleMin = min;
  m_speedScaleMax = max;
}

void Tracks::setSteering(int angle) {
  debugprint(DEBUG_TRACK, "steering set to %d", angle);
  steering.write(map(angle, 0, 2048, m_steeringScaleMin, m_steeringScaleMax));
}

void Tracks::setSteeringScale(int min, int max) {
  debugprint(DEBUG_TRACK, "steering scale set to (%d,%d)", min, max);
  m_steeringScaleMin = min;
  m_steeringScaleMax = max;
}

void Tracks::setGear(int value) {
  debugprint(DEBUG_TRACK, "gear set to %d", value);
  gear.write(map(value, 0, 2048, 1, 180));
}

