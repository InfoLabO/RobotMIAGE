#include "orientationLibrary.h";

#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

const float PidOrientation::KP = 0.4;
const float PidOrientation::KI = 0.3;
const float PidOrientation::KD = 0.0;

const int PidOrientation::MinDiff = 130;

PidOrientation::PidOrientation(float goal)
  : goal(goal), initilized(false)
{}

void PidOrientation::setGoal(float goal) {

  this->goal = goal;

}
 
float PidOrientation::correct() {

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
  if(currentTime - lastTime < 0.25)
    delay((0.25-(currentTime - lastTime))*1000);

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
  clockWise = correction > 0;
  diff = abs(correction) + MinDiff;
  if( diff > 510) diff = 510;
  
  // If correction is really low
  if(-1 < correction && correction < 1) {
    
    Robot.motorsWrite(0,0);
    return 0.0;
    
  }
  
  motorSpeed = diff/2;
  
  // CW turn
  if(clockWise) {
    
    Robot.motorsWrite(-motorSpeed,motorSpeed);

  } else {
    
    // CCW turn 
    Robot.motorsWrite(motorSpeed,-motorSpeed);

  }
  
  return correction;
  
}

float PidOrientation::currentValue() {

  return Robot.compassRead();

}

float PidOrientation::error(){
  float error = (int)(this->goal-this->currentValue())% 360;
  if(error > 180){
    error = error-360;
  }else if(error <-180){
    error = error + 360;
  }
  return error;
}

void PidOrientation::stop() {
  initilized = false;
}

bool PidOrientation::isGoalReach() {

  return goal == currentValue();

}
