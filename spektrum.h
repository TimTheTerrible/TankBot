#ifndef __spektrum_h__
#define __spektrum_h__

#define MAX_MSG_LEN 20

class SpektrumRx
{
  public:

  boolean begin();

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

  byte *inputbuffer[MAX_MESG_LEN];

  int m_aileron;
  int m_elevator;
  int m_rudder;
  int m_throttle;
  int m_aux1;
  int m_aux2;
  int m_aux3;
  int m_aux4;
  int m_aux5;
}

#endif
