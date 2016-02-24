#include "myPWMServoDriver.h"

/*
 * myPWMServoDriver
 */

myPWMServoDriver servoDriver = myPWMServoDriver();

myPWMServo * myPWMServoDriver::getServo(uint8_t servoNum) {
  return new myPWMServo(this, servoNum);
}

/*
 * myPWMServo
 */

myPWMServo::myPWMServo(myPWMServoDriver * driver, uint8_t servoNum) {
  m_servoDriver = driver;
  m_servoNum = servoNum;
}

void myPWMServo::setAngle(uint16_t angle) {
  // TODO: range checking
  m_scaledAngle = map(angle, 0, 180, m_minAngle, m_maxAngle);
  m_servoDriver->setPin(m_servoNum, m_scaledAngle, 0);
}

void myPWMServo::setScale(uint16_t minAngle, uint16_t maxAngle) {
  // TODO: range checking
  m_minAngle = minAngle;
  m_maxAngle = maxAngle;
}

uint16_t myPWMServo::getAngle() {
  return m_scaledAngle;
}

