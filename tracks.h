#ifndef __tracks_h__
#define __tracks_h__

#include "myPWMServoDriver.h"

#define DEBUG_TRACK 0x1000

class Tracks
{
  public:
    bool begin( uint8_t, uint8_t, uint8_t );
    void setThrottle( uint8_t );
    void setThrottleScale( uint8_t, uint8_t );
    void setSteering( uint8_t );
    void setSteeringScale( uint8_t, uint8_t );
    void setGear( uint8_t );
    void setGearScale( uint8_t, uint8_t );
    void showDebug();

  private:
    uint8_t m_throttleScaleMin = 0;
    uint8_t m_throttleScaleMax = 180;
    uint8_t m_steeringScaleMin = 0;
    uint8_t m_steeringScaleMax = 180;
    uint8_t m_gearScaleMin = 0;
    uint8_t m_gearScaleMax = 180;
  
    myPWMServo * throttle;
    myPWMServo * steering;
    myPWMServo * gear;
};

extern Tracks tracks;

#endif
