#include <Adafruit_PWMServoDriver.h>
#include "myPWMServoDriver.h"

/*
 * myPWMServoDriver
 */

myPWMServoDriver servoDriver = myPWMServoDriver();

myPWMServo * myPWMServoDriver::getServo(uint8_t servoNum) {
  return new myPWMServo(servoNum);
}

/*
 * myPWMServo
 */

myPWMServo::myPWMServo(uint8_t servoNum) {
  m_servoNum = servoNum;
}

void myPWMServo::setAngle(uint16_t angle) {
  m_scaledAngle = map(angle, 0, 180, m_minAngle, m_maxAngle);
  servoDriver.setPin(m_servoNum, m_scaledAngle, 0);
}

void myPWMServo::setScale(uint16_t minAngle, uint16_t maxAngle) {
  // TODO: range checking
  m_minAngle = minAngle;
  m_maxAngle = maxAngle;
}

uint16_t myPWMServo::getAngle() {
  return m_scaledAngle;
}

