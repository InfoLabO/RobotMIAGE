#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial serial(D0,D1);
void setup() {
  
  Robot.begin();
  Robot.beginSpeaker();
//  pinMode(13,OUTPUT);
  serial.begin(9600);
  Robot.beep(BEEP_SIMPLE);
}

void loop() {

  if(serial.available() > 0)
    Robot.beep(BEEP_SIMPLE);
//    digitalWrite(13, HIGH);
  
  delay(300);
//  digitalWrite(13,LOW);

  delay(300);
  
}
