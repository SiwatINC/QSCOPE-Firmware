#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <I2C_eeprom.h>
#include <USBCore.h>
#define USB_VID 0x03eb
#define USB_PID 0x2ff4
#define BAUD 115200
//#define MINIMAL_FAST
#ifdef MINIMAL_FAST
#include "fastpollroutine.asm"
#endif
long freq1=0;
long freq2=0;
StaticJsonDocument<200> datarep;
I2C_eeprom datastore(0x50,0x2000);
void freq1count();
void freq2count();
void setup() {
  datastore.begin();
  datastore.setBlock(0,0,128);
  datastore.determineSize();
  Serial.begin(115200);
  SerialUSB.begin(115200);
  DDRF = B00111111;
  DDRB = B11111100;
  Serial.println("Siwat INC QSCOPE R1 Ready | Standalone Mode");
  attachInterrupt(digitalPinToInterrupt(PB7),freq1count,RISING);
  attachInterrupt(digitalPinToInterrupt(PB6),freq2count,RISING);
}

void loop() {
  datarep["timestamp"]=millis();
  datarep["CH1"]=analogRead(PF0);
  datarep["CH2"]=analogRead(PF1);
  datarep["freq1cnt"]=freq1;
  datarep["freq2cnt"]=freq2;
  serializeJson(datarep,SerialUSB);
}
void freq1count(){
  freq1++;
}
void freq2count(){
  freq2++;
}
ISR(INT6_vect){ //PB6 fc2
  freq2++;
}
ISR(INT7_vect){ //PB7 fc1
  freq1++;
}