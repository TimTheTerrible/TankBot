#ifndef __spektrum_h__
#define __spektrum_h__

#define MAX_MSG_LEN 16

#define SRX_CHAN_MASK    0xFC00
#define SRX_VAL_MASK_LEN 10
#define SRX_VAL_MASK     0x03FF

#define CHAN_AILERON  1
#define CHAN_ELEVATOR 2
#define CHAN_THROTTLE 3
#define CHAN_RUDDER   4
#define CHAN_AUX1     5
#define CHAN_AUX2     6
#define CHAN_AUX3     7
#define CHAN_AUX4     8
#define CHAN_AUX5     9

class SpektrumRx
{
  public:

  bool begin();
  void parse( char * );

  int aileron();
  int elevator();
  int rudder();
  int throttle();
  int aux1();
  int aux2();
  int aux3();
  int aux4();
  int aux5();

  private:

  int m_aileron;
  int m_elevator;
  int m_rudder;
  int m_throttle;
  int m_aux1;
  int m_aux2;
  int m_aux3;
  int m_aux4;
  int m_aux5;
};

extern SpektrumRx rx;

#endif
