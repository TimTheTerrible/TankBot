#include <Servo.h>
#include "debugprint.h"
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
  debugprint(DEBUG_PANTILT, "pan angle set to %d", angle);
  pan.write(map(angle, 2048, 0, m_panScaleMin, m_panScaleMax));
}

void PanTilt::setPanScale(int min, int max) {
  debugprint(DEBUG_PANTILT, "pan scale set to (%d,%d)", min, max);
  m_panScaleMin = min;
  m_panScaleMax = max;
}

void PanTilt::setTilt( int angle ) {
  debugprint(DEBUG_PANTILT, "pan angle set to %d", angle);
  tilt.write(map(angle, 2048, 0, m_tiltScaleMin, m_tiltScaleMax));
}

void PanTilt::setTiltScale(int min, int max) {
  debugprint(DEBUG_PANTILT, "tilt scale set to (%d,%d)", min, max);
  m_tiltScaleMin = min;
  m_tiltScaleMax = max;
}

void PanTilt::setRoll( int angle ) {
  debugprint(DEBUG_PANTILT, "pan angle set to %d", angle);
  roll.write(map(angle, 0, 2048, m_rollScaleMin, m_rollScaleMax));
}

void PanTilt::setRollScale(int min, int max) {
  debugprint(DEBUG_PANTILT, "roll scale set to (%d,%d)", min, max);
  m_rollScaleMin = min;
  m_rollScaleMax = max;
}

