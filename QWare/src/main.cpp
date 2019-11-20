#include <Arduino.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <I2C_eeprom.h>
#include <USBCore.h>
#define USB_VID 0x03eb
#define USB_PID 0x2ff4
long freq1=0;
long freq2=0;
StaticJsonDocument<200> datarep;
I2C_eeprom datastore(0x50,0x2000);
void setup() {
  datastore.begin();
  datastore.setBlock(0,0,128);
  datastore.determineSize();
  Serial.begin(115200);
  SerialUSB.begin(115200);
  pinMode(PF0,INPUT);
  pinMode(PF1,INPUT);
  pinMode(PB7,INPUT);
  pinMode(PB6,INPUT);
  Serial.println("Siwat INC QSCOPE R1 Ready | Standalone Mode");
  attachInterrupt(digitalPinToInterrupt(PB7),freq1count,RISING);
  attachInterrupt(digitalPinToInterrupt(PB6),freq2count,RISING);
}

void loop() {
  datarep["CH1"]=analogRead(PF0);
  datarep["CH2"]=analogRead(PF1);
  datarep["timestamp"]=millis();
  datarep["freq1"]=freq1;
  datarep["freq2"]=freq2;
  serializeJson(datarep,SerialUSB);
}
void freq1count(){
  detachInterrupt(digitalPinToInterrupt(PB7));
  freq1++;
}
void freq2count(){
  detachInterrupt(digitalPinToInterrupt(PB6));
  freq2++;
}
