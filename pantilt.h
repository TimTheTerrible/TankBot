#ifndef __pantilit_h__
#define __pantilit_h__

#include "myPWMServoDriver.h"

#define DEBUG_PANTILT 0x2000

class PanTilt
{
  public:
    bool begin( uint8_t, uint8_t, uint8_t );
    void setPan( uint16_t );
    void setPanScale( uint8_t, uint8_t );
    void setTilt( uint16_t );
    void setTiltScale( uint8_t, uint8_t );
    void setRoll( uint16_t );
    void setRollScale( uint8_t, uint8_t );
    void showDebug();

  private:
    uint8_t m_panScaleMin = 0;
    uint8_t m_panScaleMax = 180;
    uint8_t m_tiltScaleMin = 0;
    uint8_t m_tiltScaleMax = 180;
    uint8_t m_rollScaleMin = 0;
    uint8_t m_rollScaleMax = 180;
  
    myPWMServo * pan;
    myPWMServo * tilt;
    myPWMServo * roll;
};

extern PanTilt pantilt;

#endif

