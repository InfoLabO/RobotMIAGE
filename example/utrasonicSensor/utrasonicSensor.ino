#include <ArduinoRobot.h>

#include "USSEnsorUtils.h";
#include <Wire.h>
#include <SPI.h>

// pin is used by the sensors
int rightPin = M0;
int frontRightPin = M1;
int frontPin = M2;
int frontLeftPin = M3;
int leftPin = M4;
int backleftPin = M5;
int backPin = M6;
int backRightPin = M7;


void setup() {
  Serial.begin(9600);
  Robot.begin();
  Robot.beginTFT();
}

void loop() {
  if(getDistance(frontPin)<30){
    Robot.motorsStop();
  }else{
    Robot.motorsWrite(170,170);
   }
}
