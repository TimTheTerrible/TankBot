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

struct SpektrumChannels {
  int aileron = 0;
  int elevator = 0;
  int rudder = 0;
  int throttle = 0;
  int gear = 0;
  int aux1 = 0;
  int aux2 = 0;
  int aux3 = 0;
  int aux4 = 0;
  int aux5 = 0;
  int aux6 = 0;
  int aux7 = 0;
  int aux8 = 0;
};

class SpektrumRx
{
  public:

  bool begin();
  void parse( uint8_t * );
  SpektrumChannels getChannels();
  const char * lastFrame();

  private:

  SpektrumChannels m_channels;

};

extern SpektrumRx rx;

#endif
