#include "pidWall.h";
#include "USSensorUtils.h";

#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

const float PidWall::KP = 1.0;
const float PidWall::KI = 0.0;
const float PidWall::KD = 0.0;

PidWall::PidWall(float goal, int motorSpeed, USSensor *sensor)
  : goal(goal), motorSpeed(motorSpeed), sensor(sensor), initilized(false)
{

    maxDiff = (255 - motorSpeed)*2;

}

void PidWall::setGoal(float goal) {

  this->goal = goal;

}

void PidWall::setMotorSpeed(int MotorSpeed) {

  this->motorSpeed = motorSpeed;

}
 
float PidWall::correct() {

  float currentError;
  float currentTime;
  float deltaTime;
  float deltaError;
  float correction;
  bool clockWise;
  int diff;

  // Init case
  if(!initilized) {
    
    lastTime = millis()/1000.0;
    lastError = this->error();
    sumError = 0;
    initilized = true;

    return 0.0;

  }
  
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
  diff = abs(correction);
  if( diff > maxDiff) diff = maxDiff;
  
  if(clockWise) {
    // CW turn
    Robot.motorsWrite(motorSpeed + diff/2,motorSpeed - diff/2);
  } else {
    // CCW turn 
    Robot.motorsWrite(motorSpeed - diff/2,motorSpeed + diff/2);
  }
  
  return (clockWise ? diff : -diff);
  
}

float PidWall::currentValue() {

  return (sensor->getLeftDistance() - sensor->getRightDistance());

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
