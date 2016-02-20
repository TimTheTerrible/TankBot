/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

  Adapted to provide a simpler servo interface by tim@dforge.cc

 ****************************************************/

#ifndef _myPWMServoDriver_H
#define _myPWMServoDriver_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

class myPWMServo;

class myPWMServoDriver {
 public:
  myPWMServoDriver(uint8_t addr = 0x40);
  void begin(void);
  void reset(void);
  void setPWMFreq(float freq);
  void setPWM(uint8_t num, uint16_t on, uint16_t off);
  void setPin(uint8_t num, uint16_t val, bool invert=false);
  myPWMServo * getServo(uint8_t servoNum);

 private:
  uint8_t _i2caddr;

  uint8_t read8(uint8_t addr);
  void write8(uint8_t addr, uint8_t d);
};

class myPWMServo {
  public:
  myPWMServo(uint8_t servoNum);
  void setAngle(uint16_t angle);
  void setScale(uint16_t minAngle, uint16_t maxAngle);
  uint16_t getAngle();

  private:
  uint16_t m_minAngle = 150;
  uint16_t m_maxAngle = 600;
  uint16_t m_scaledAngle;
  uint8_t m_servoNum;
};

extern myPWMServoDriver servoDriver;

#endif
