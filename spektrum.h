#include <stdint.h>

#ifndef __spektrum_h__
#define __spektrum_h__

#define DEBUG_PARSE       0x0100
#define DEBUG_SERIAL      0x0200

#define MAX_MSG_LEN       16

#define SRX_CHAN_MASK     0x7800
#define SRX_VAL_MASK_LEN  10
#define SRX_VAL_MASK      0x07FF

#define CHAN_THROTTLE     0
#define CHAN_AILERON      2
#define CHAN_ELEVATOR     4
#define CHAN_RUDDER       6
#define CHAN_GEAR         8
#define CHAN_AUX1         10
#define CHAN_AUX2         12
#define CHAN_AUX3         14
#define CHAN_AUX4         16

class SpektrumRx
{
  public:

  bool begin();
  void parse( uint8_t * );

  int aileron();
  int elevator();
  int rudder();
  int throttle();
  int gear();
  int aux1();
  int aux2();
  int aux3();
  int aux4();

  private:

  int m_aileron = 0;
  int m_elevator = 0;
  int m_rudder = 0;
  int m_throttle = 0;
  int m_gear = 0;
  int m_aux1 = 0;
  int m_aux2 = 0;
  int m_aux3 = 0;
  int m_aux4 = 0;
};

extern SpektrumRx rx;

#endif
