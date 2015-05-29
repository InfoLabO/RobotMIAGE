#include "pidWall.h";
#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

PidWall pidWall(30,M0 );

void setup() {
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
} 

void loop() {
  pidWall.correct();
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
