#ifndef __tracks_h__
#define __tracks_h__

#include "myPWMServoDriver.h"

#define DEBUG_TRACK 0x1000

class Tracks
{
  public:

  bool begin( int, int, int );
  void setThrottle( int );
  void setThrottleScale( int, int );
  void setSteering( int );
  void setSteeringScale( int, int );
  void setGear( int );
  void setGearScale( int, int );
  void showDebug();

  private:

  int m_throttleScaleMin = 0;
  int m_throttleScaleMax = 180;
  int m_steeringScaleMin = 0;
  int m_steeringScaleMax = 180;
  int m_gearScaleMin = 0;
  int m_gearScaleMax = 180;
  
  myPWMServo * throttle;
  myPWMServo * steering;
  myPWMServo * gear;
};

extern Tracks tracks;

#endif
