#include "debugprint.h"
#include "pantilt.h"
#include "myPWMServoDriver.h"

PanTilt pantilt;

bool PanTilt::begin( uint8_t panServo, uint8_t tiltServo, uint8_t rollServo ) {
  m_pan = servoDriver.getServo(panServo);
  m_tilt = servoDriver.getServo(tiltServo);
  m_roll = servoDriver.getServo(rollServo);
  return true;
}

void PanTilt::setPan( uint16_t angle ) {
  debugprint(DEBUG_PANTILT, "pan angle set to %d", angle);
  m_pan->setAngle(map(angle, 2048, 0, m_panScaleMin, m_panScaleMax));
}

void PanTilt::setPanScale(uint8_t minVal, uint8_t maxVal) {
  debugprint(DEBUG_PANTILT, "pan scale set to (%d,%d)", minVal, maxVal);
  m_panScaleMin = minVal >=0 ? minVal : 0;
  m_panScaleMax = maxVal <= 180 ? maxVal : 180;
}

void PanTilt::setTilt( uint16_t angle ) {
  debugprint(DEBUG_PANTILT, "tilt angle set to %d", angle);
  m_tilt->setAngle(map(angle, 2048, 0, m_tiltScaleMin, m_tiltScaleMax));
}

void PanTilt::setTiltScale(uint8_t minVal, uint8_t maxVal) {
  debugprint(DEBUG_PANTILT, "tilt scale set to (%d,%d)", minVal, maxVal);
  m_tiltScaleMin = minVal >=0 ? minVal : 0;
  m_tiltScaleMax = maxVal <= 180 ? maxVal : 180;
}

void PanTilt::setRoll( uint16_t angle ) {
  debugprint(DEBUG_PANTILT, "roll angle set to %d", angle);
  m_roll->setAngle(map(angle, 0, 2048, m_rollScaleMin, m_rollScaleMax));
}

void PanTilt::setRollScale(uint8_t minVal, uint8_t maxVal) {
  debugprint(DEBUG_PANTILT, "roll scale set to (%d,%d)", minVal, maxVal);
  m_rollScaleMin = minVal >=0 ? minVal : 0;
  m_rollScaleMax = maxVal <= 180 ? maxVal : 180;
}

void PanTilt::showDebug() {
  debugprint(DEBUG_TRACE, "\nPant-Tilt Debugging");
  debugprint(DEBUG_TRACE, "Pan angle: %d Range: %d to %d", m_pan->getAngle(), m_panScaleMin, m_panScaleMax);
  debugprint(DEBUG_TRACE, "Tilt angle: %d Range: %d to %d", m_tilt->getAngle(), m_tiltScaleMin, m_tiltScaleMax);
  debugprint(DEBUG_TRACE, "Roll angle: %d Range: %d to %d", m_roll->getAngle(), m_rollScaleMin, m_rollScaleMax);
}

