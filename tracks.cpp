#include "WProgram.h"
#include "tracks.h"
#include "debugprint.h"
#include "myPWMServoDriver.h"

Tracks tracks;

bool Tracks::begin( uint8_t throttleServo, uint8_t steeringServo, uint8_t gearServo ) {
  m_throttle = servoDriver.getServo(throttleServo);
  m_steering = servoDriver.getServo(steeringServo);
  m_gear = servoDriver.getServo(gearServo);
  return true;
}

void Tracks::setThrottle(uint16_t angle) {
  debugprint(DEBUG_TRACK, "throttle set to %d", angle);
  m_throttle->setAngle(map(angle, 0, 2048, m_throttleScaleMin, m_throttleScaleMax));
}

void Tracks::setThrottleScale(uint8_t minVal, uint8_t maxVal) {
  debugprint(DEBUG_TRACK, "throttle scale set to (%d,%d)", minVal, maxVal);
  m_throttleScaleMin = minVal >= 0 ? minVal : 0;
  m_throttleScaleMax = maxVal <= 180 ? maxVal : 180;
}

void Tracks::setSteering(uint16_t angle) {
  debugprint(DEBUG_TRACK, "steering set to %d", angle);
  m_steering->setAngle(map(angle, 0, 2048, m_steeringScaleMin, m_steeringScaleMax));
}

void Tracks::setSteeringScale(uint8_t minVal, uint8_t maxVal) {
  debugprint(DEBUG_TRACK, "steering scale set to (%d,%d)", minVal, maxVal);
  m_steeringScaleMin = minVal >= 0 ? minVal : 0;
  m_steeringScaleMax = maxVal <= 180 ? maxVal : 180;
}

void Tracks::setGear(uint16_t angle) {
  debugprint(DEBUG_TRACK, "gear set to %d", angle);
  m_gear->setAngle(map(angle, 0, 2048, 0, 180));
}

void Tracks::setGearScale(uint8_t minVal, uint8_t maxVal) {
  debugprint(DEBUG_TRACK, "gear scale set to (%d,%d)", minVal, maxVal);
  m_gearScaleMin = minVal >= 0 ? minVal : 0;
  m_gearScaleMax = maxVal <= 180 ? maxVal : 180;
}

void Tracks::showDebug() {
  debugprint(DEBUG_TRACE, "\nTracks Debugging");
  debugprint(DEBUG_TRACE, "Throttle angle: %d Range: %d to %d", m_throttle->getAngle(), m_throttleScaleMin, m_throttleScaleMax);
  debugprint(DEBUG_TRACE, "Steering angle: %d Range: %d to %d", m_steering->getAngle(), m_steeringScaleMin, m_steeringScaleMax);
  debugprint(DEBUG_TRACE, "Gear angle: %d Range: %d to %d", m_gear->getAngle(), m_gearScaleMin, m_gearScaleMax);
}

