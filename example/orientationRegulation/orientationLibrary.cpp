#include "orientationLibrary.h";

#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

const float PidOrientation::KP = 1;
const float PidOrientation::KI = 1;
const float PidOrientation::KD = 1;

const int PidOrientation::MinDiff = 100;

PidOrientation::PidOrientation(float goal)
  : goal(goal), initilized(false)
{}

void PidOrientation::setGoal(float goal) {

  this->goal = goal;

}
 
void PidOrientation::correct() {

  float currentError;
  unsigned long currentTime;
  unsigned int deltaTime;
  float deltaError;
  float correction;
  bool clockWise;

  // Init case
  if(!initilized) {
    
    lastTime = currentTime;
    lastError = error();
    sumError = 0;
    initilized = true;

    return;

  }

  // Compute values
  currentError = error();
  currentTime = millis();
  deltaTime = lastTime - currentTime;
  lastTime = currentTime;
  sumError += currentError*deltaTime;
  deltaError = (currentError-lastError)/deltaTime;
  lastError = currentError;
  correction = KP*currentError + KI*sumError + KD*deltaError;

  clockWise = correction > 0;
  correction = abs(correction) + MinDiff/2;

  if(clockWise) {
    
    Robot.motorsWrite(correction,-correction);

  } else {
    
    Robot.motorsWrite(-correction,correction);

  }
  
}

float PidOrientation::currentValue() {

  return Robot.compassRead();

}

float PidOrientation::error(){
  float error = (int)(goal-currentValue())% 360;
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
