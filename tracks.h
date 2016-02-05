#ifndef __tracks_h__
#define __tracks_h__

#include <Servo.h>

#define DEBUG_TRACK 0x1000

class Tracks
{
  public:

  bool begin( int, int, int );
  void setSpeed( int );
  void setSteering( int );
  void setFlip( int );

  private:

  int m_speed;
  int m_angle;
  Servo throttle;
  Servo steering;
  Servo flip;
};

extern Tracks tracks;

#endif
