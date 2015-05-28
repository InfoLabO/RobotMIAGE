#include "pidWall.h";
#include "USSensorUtils.h";

#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

const float PidWall::KP = 0.4;
const float PidWall::KI = 0.3;
const float PidWall::KD = 0.0;

const int PidWall::MinDiff = 0;

PidWall::PidWall(float goal ,int sensorPin)
  : goal(goal), initilized(false),sensorPin(sensorPin)
{}

void PidWall::setGoal(float goal) {

  this->goal = goal;

}
 
float PidWall::correct() {

  float currentError;
  float currentTime;
  float deltaTime;
  float deltaError;
  float correction;
  bool clockWise;
  unsigned int diff;
  unsigned int motorSpeed;

  // Init case
  if(!initilized) {
    
    lastTime = millis()/1000.0;
    lastError = this->error();
    sumError = 0;
    initilized = true;

    return 0.0;

  }

  currentTime = millis()/1000.0;
  
  // Get current values
  currentError = this->error();
  currentTime = millis()/1000.0;
  
  // Compute pid
  deltaTime = currentTime - lastTime;
  sumError += currentError*deltaTime;
  deltaError = (currentError-lastError)/deltaTime;
  correction = KP*currentError + KI*sumError + KD*deltaError;
  
  // Memorize values for next step
  lastTime = currentTime;
  lastError = currentError;

  // Apply correction on motors
  clockWise = currentError > 0;
  diff = abs(correction) + MinDiff;
  if( diff > 30) diff = 30;
  
  
  // If correction is really low
  if(-1 < correction && correction < 1) {
    Robot.motorsWrite(255,255);
    return 0.0;
  }
  
  motorSpeed = diff/2;
  
  if(clockWise) {
    // CW turn
    //TODO
  } else {
    // CCW turn 
    //TODO
  }
  
  return correction;
  
}

float PidWall::currentValue() {

  return getDistance(sensorPin);

}

float PidWall::error(){
  return (int)(this->currentValue()-this->goal);
}

void PidWall::stop() {
  initilized = false;
}

bool PidWall::isGoalReach() {

  return goal == currentValue();

}
