#ifndef __pantilit_h__
#define __pantilit_h__

#include "myPWMServoDriver.h"

#define DEBUG_PANTILT 0x2000

class PanTilt
{
  public:

  bool begin( int, int, int);
  void setPan( int );
  void setPanScale( int, int );
  void setTilt( int );
  void setTiltScale( int, int );
  void setRoll( int );
  void setRollScale( int, int );
  void showDebug();

  private:

  int m_panScaleMin = 0;
  int m_panScaleMax = 180;
  int m_tiltScaleMin = 0;
  int m_tiltScaleMax = 180;
  int m_rollScaleMin = 0;
  int m_rollScaleMax = 180;

  myPWMServo * pan;
  myPWMServo * tilt;
  myPWMServo * roll;
};

extern PanTilt pantilt;

#endif

