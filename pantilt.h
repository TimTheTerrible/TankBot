#ifndef __pantilit_h__
#define __pantilit_h__

#include <Servo.h>

#define DEBUG_PANTILT 0x2000

class PanTilt
{
  public:

  bool begin( int, int, int);
  void setPan( int );
  void setTilt( int );
  void setRoll( int );

  private:

  int m_pan;
  int m_tilt;
  int m_roll;
  Servo pan;
  Servo tilt;
  Servo roll;
};

extern PanTilt pantilt;

#endif

