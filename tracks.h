#ifndef __tracks_h__
#define __tracks_h__

#include <Servo.h>

#define DEBUG_TRACK 0x1000

class Tracks
{
  public:

  bool begin( int, int, int );
  void setSpeed( int );
  void setSpeedScale( int, int );
  void setSteering( int );
  void setSteeringScale( int, int );
  void setGear( int );
  void setGearScale( int, int );

  private:

  int m_speedScaleMin = 0;
  int m_speedScaleMax = 180;
  int m_steeringScaleMin = 0;
  int m_steeringScaleMax = 180;
  
  Servo throttle;
  Servo steering;
  Servo gear;
};

extern Tracks tracks;

#endif
