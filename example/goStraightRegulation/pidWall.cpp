#include "pidWall.h";
#include "USSensorUtils.h";

#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

const float PidWall::KP = 0.5;
const float PidWall::KI = 0.0;
const float PidWall::KD = 0.0;

const unsigned int MaxDiff = 10;

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
  int motorSpeed;

  // Init case
  if(!initilized) {
    
    delay(250);
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
  clockWise = currentError < 0;
  diff = abs(correction);
  if( diff > MaxDiff) diff = MaxDiff;
  
  motorSpeed = 255 - MaxDiff;
  
  if(clockWise) {
    // CW turn
    Robot.motorsWrite(motorSpeed+diff,motorSpeed-diff);
  } else {
    // CCW turn 
    //TODO
    Robot.motorsWrite(motorSpeed-diff,motorSpeed+diff);
  }
  
  return diff;
  
}

float PidWall::currentValue() {

  return getDistance(sensorPin);

}

float PidWall::error(){
  return this->currentValue()-this->goal;
}

void PidWall::stop() {
  initilized = false;
}

bool PidWall::isGoalReach() {

  return goal == currentValue();

}
