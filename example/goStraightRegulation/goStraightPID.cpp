#include "goStraightPID.h";

#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

const float StraightPID::KP = 0.4;
const float StraightPID::KI = 0.3;
const float StraightPID::KD = 0.0;

const int StraightPID::MinDiff = 0;

StraightPID::StraightPID(float goal)
  : goal(goal), initilized(false)
{}

void StraightPID::setGoal(float goal) {

  this->goal = goal;

}
 
float StraightPID::correct() {

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
    Robot.motorsWrite(250+correction,250-correction);
  } else {
    // CCW turn 
    //TODO
    Robot.motorsWrite(250-correction,250+correction);
  }
  
  return correction;
  
}

float StraightPID::currentValue() {

  return Robot.compassRead();

}

float StraightPID::error(){
  float error = (int)(this->goal-this->currentValue())% 360;
  if(error > 180){
    error = error-360;
  }else if(error <-180){
    error = error + 360;
  }
  return error;
}

void StraightPID::stop() {
  initilized = false;
}

bool StraightPID::isGoalReach() {

  return goal == currentValue();

}
