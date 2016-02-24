#ifndef __MYPWMSERVODRIVER_H__
#define __MYPWMSERVODRIVER_H__

#include <Adafruit_PWMServoDriver.h>

class myPWMServo;

class myPWMServoDriver : public Adafruit_PWMServoDriver {
 public:
   myPWMServo * getServo( uint8_t );
};

class myPWMServo {
  public:
    myPWMServo( myPWMServoDriver *, uint8_t );
    void setAngle( uint16_t );
    void setScale( uint16_t, uint16_t );
    uint16_t getAngle();

  private:
    myPWMServoDriver * m_servoDriver;
    uint8_t m_servoNum;
    uint16_t m_minAngle = 45;
    uint16_t m_maxAngle = 705;
    uint16_t m_scaledAngle = m_minAngle + ( ( m_maxAngle - m_minAngle ) / 2 );
};

extern myPWMServoDriver servoDriver;

#endif
