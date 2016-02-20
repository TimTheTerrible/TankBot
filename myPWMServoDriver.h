#ifndef __MYPWMSERVODRIVER_H__
#define __MYPWMSERVODRIVER_H__

#include <Adafruit_PWMServoDriver.h>

class myPWMServo;

class myPWMServoDriver : public Adafruit_PWMServoDriver {
 public:
   myPWMServo * getServo(uint8_t servoNum);
};

class myPWMServo {
  public:
    myPWMServo(uint8_t servoNum);
    void setAngle(uint16_t angle);
    void setScale(uint16_t minAngle, uint16_t maxAngle);
    uint16_t getAngle();

  private:
    uint8_t m_servoNum;
    uint16_t m_minAngle = 150;
    uint16_t m_maxAngle = 600;
    uint16_t m_scaledAngle;
};

extern myPWMServoDriver servoDriver;

#endif
