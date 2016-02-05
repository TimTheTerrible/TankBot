#include <stdint.h>

#ifndef __spektrum_h__
#define __spektrum_h__

#define DEBUG_PARSE       0x0100
#define DEBUG_SERIAL      0x0200

#define MAX_MSG_LEN       16

#define SRX_VAL_MASK_LEN  11
#define SRX_VAL_MASK      0x07FF

#define CHAN_THROTTLE     16
#define CHAN_AILERON      1
#define CHAN_ELEVATOR     2
#define CHAN_RUDDER       3
#define CHAN_GEAR         4
#define CHAN_AUX1         5
#define CHAN_AUX2         6
#define CHAN_AUX3         7
#define CHAN_AUX4         8
#define CHAN_AUX5         9
#define CHAN_AUX6         10
#define CHAN_AUX7         11
#define CHAN_AUX8         12

typedef struct SpektrumChannels {
  int throttle = 1024;
  int aileron = 1024;
  int elevator = 1024;
  int rudder = 1024;
  int gear = 1024;
  int aux1 = 1024;
  int aux2 = 1024;
  int aux3 = 1024;
  int aux4 = 1024;
  int aux5 = 1024;
  int aux6 = 1024;
  int aux7 = 1024;
  int aux8 = 1024;
} SpektrumChannels;

class SpektrumRx
{
  public:

  bool begin();
  void parse( uint8_t * );
  SpektrumChannels getChannels();
  int switchPos( int, int );

  private:

  SpektrumChannels m_channels;

};

extern SpektrumRx rx;

#endif
