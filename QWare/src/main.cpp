#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <USBCore.h>
#define BAUD 115200
//#define MINIMAL_FAST
long freq1=0;
long freq2=0;
StaticJsonDocument<200> datarep;
void freq1count();
void freq2count();
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  Serial.println("Siwat INC QSCOPE R1 Ready | Standalone Mode");
  attachInterrupt(digitalPinToInterrupt(10),freq1count,1);
  attachInterrupt(digitalPinToInterrupt(11),freq2count,1);
}

void loop() {
  datarep["timestamp"]=millis();
  datarep["CH1"]=analogRead(A5);
  datarep["CH2"]=analogRead(A4);
  datarep["freq1cnt"]=freq1;
  datarep["freq2cnt"]=freq2;
  serializeJson(datarep,Serial);
  serializeJson(datarep,Serial1);
  Serial.println();
}
void freq1count(){
  freq1++;
}
void freq2count(){
  freq2++;
}