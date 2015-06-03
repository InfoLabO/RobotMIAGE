#include "goStraightPID.h";
#include "USSensorUtils.h"
#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

StraightPID straightPID(110, 250);

void setup() {
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
  Serial.begin(9600);
} 

void loop() {
  
  Serial.print("Oriantation    :");
  Serial.println(Robot.compassRead());
  Serial.print("error      : ");
  Serial.println(straightPID.error());
  Serial.print("correction : ");
  Serial.println(straightPID.correct());
  Serial.println("---------------------------------------");
  
  delay(250);
  
}

/**
Turning left 
**/
void turnLeft(){
  Robot.motorsWrite(0 , 125 ) ; 
  
}

/**
Turning Right 
**/
void turnRight(){
  Robot.motorsWrite(125 , 0 ) ; 
}

/**
Stopping the robot 
**/
void stopIt() {   
  Robot.stop() ; 
}

/**
Going straight
**/
void goStraight(){
  Robot.motorsWrite(255 , 255 ) ; 
  delay(1000);
}
