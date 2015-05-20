
#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

void setup() {
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
  Robot.displayLogos();
} 

void loop() {
  goStraight();
  stopIt();
  delay(1000);
  turnRight();
  delay(1000);
  goStraight();
  turnLeft();
  delay(1000);
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
