#include "WProgram.h"
#include "tracks.h"
#include "debugprint.h"
#include "myPWMServoDriver.h"

Tracks tracks;

bool Tracks::begin( int steeringPin, int throttlePin, int gearPin ) {
  throttle = servoDriver.getServo(throttlePin);
  steering = servoDriver.getServo(steeringPin);
  gear = servoDriver.getServo(gearPin);
  return true;
}

void Tracks::setThrottle(int angle) {
  debugprint(DEBUG_TRACK, "throttle set to %d", angle);
  throttle->setAngle(map(angle, 0, 2048, m_throttleScaleMin, m_throttleScaleMax));
}

void Tracks::setThrottleScale(int min, int max) {
  debugprint(DEBUG_TRACK, "throttle scale set to (%d,%d)", min, max);
  m_throttleScaleMin = min;
  m_throttleScaleMax = max;
}

void Tracks::setSteering(int angle) {
  debugprint(DEBUG_TRACK, "steering set to %d", angle);
  steering->setAngle(map(angle, 0, 2048, m_steeringScaleMin, m_steeringScaleMax));
}

void Tracks::setSteeringScale(int min, int max) {
  debugprint(DEBUG_TRACK, "steering scale set to (%d,%d)", min, max);
  m_steeringScaleMin = min;
  m_steeringScaleMax = max;
}

void Tracks::setGear(int angle) {
  debugprint(DEBUG_TRACK, "gear set to %d", angle);
  gear->setAngle(map(angle, 0, 2048, 0, 180));
}

void Tracks::setGearScale(int min, int max) {
  debugprint(DEBUG_TRACK, "gear scale set to (%d,%d)", min, max);
  m_gearScaleMin = min;
  m_gearScaleMax = max;
}

void Tracks::showDebug() {
  debugprint(DEBUG_TRACE, "Throttle: %d Steering: %d Gear: %d", throttle->getAngle(), steering->getAngle(), gear->getAngle());
}

