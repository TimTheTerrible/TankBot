/* 
+----------------------------------------------------------------------------------------------------------------------+ 
 | Simple Arduino Spektrum receiver V 1.0                                                                              | 
 | Released under GPL-V2 by DJRubberCow 2011                                                                           | 
 |                                                                                                                     | 
 | Read all about it under                                                                                             | 
 | http://www.rcpowers.com/forum/showthread.php?8922-Self-built-Spektrum-Receiver-using-the-SPM9594-(AR6200-Satellite) | 
 +---------------------------------------------------------------------------------------------------------------------+ 
 */ 

#include <Servo.h> 

Servo throttlePin3; 
Servo rudderPin4; 
Servo elevatorPin5; 
Servo aileronPin6; 
Servo gearPin7; 
Servo flapsPin8; 

int i = 0; 
int buffer[14]; 

int lastval=255; 
boolean foundSync=false; 
void loop() { 
  if(i<14) { 
    if(Serial.available()) { 
      int value = Serial.read(); 
      if(lastval == 24 && value == 0) { 
        foundSync = true; 
      }  
      else if(!foundSync) { 
        lastval = value; 
        return; 
      }  
      else { 
        // Found sync, fill buffer 
        buffer[i] = value; 
        i++;  
      } 
    } 
  }  
  else { 
    i = 0; 
    foundSync = false; 
    lastval = 255; 
    writeValues(); 
  } 
} 

void writeValues() { 
  // Now comes the data  
  // First: Sync byte which does not work 
  buffer[0]; 
  buffer[1]; 

  // Now: Aileron 
  int ail = buffer[2] & 3; 
  ail = ail <<8; 
  ail += buffer[3]; 

  // now: Flaps 
  int flaps = buffer[4] & 3; 
  flaps = flaps <<8;     
  flaps +=buffer[5]; 

  // now: elevator 
  int elev = buffer[6] & 3; 
  elev = elev <<8; 
  elev += buffer[7]; 

  // now: Rudder 
  int rud = buffer[8] & 3; 
  rud = rud<<8; 
  rud+= buffer[9]; 

  // now: Throttle 
  // We need some extra work here because  
  // the DX6i sends its throttle data rather weird 
  int thro = 0; 
  if((buffer[10] & 128) == 128) { 
    thro = buffer[10]; 
  } 
  else { 
    thro = buffer[10] & 3; 
    thro = thro<<8; 
    thro+= buffer[11]; 
  } 
  // now: Gear 
  int gear = buffer[12] & 3; 
  gear = gear<<8; 
  gear+= buffer[13]; 

  throttlePin3.writeFine(thro); 
  rudderPin4.writeFine(rud); 
  elevatorPin5.writeFine(elev); 
  aileronPin6.writeFine(ail); 
  gearPin7.writeFine(gear); 
  flapsPin8.writeFine(flaps); 

  lastval = 255; 
} 

void setup() { 

  Serial.begin(115200);  

  throttlePin3.attach(3); 
  throttlePin3.write(0); 

  rudderPin4.attach(4); 
  rudderPin4.write(90); 

  elevatorPin5.attach(5); 
  elevatorPin5.write(90); 

  aileronPin6.attach(6); 
  aileronPin6.write(90); 

  gearPin7.attach(7); 
  gearPin7.write(0); 

  flapsPin8.attach(8); 
  flapsPin8.write(0); 
} 
