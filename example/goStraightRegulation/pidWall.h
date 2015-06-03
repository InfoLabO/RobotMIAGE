#pragma once

#include "USSensorUtils.h"

class PidWall {

 private:
  
  static const float KP;
  static const float KI;
  static const float KD;

  bool initilized;
  
  float goal;
  int motorSpeed;
  USSensor *sensor;
  int maxDiff;
  
  float lastTime;
  float lastError;
  
  float sumError;

 public:

  PidWall(float goal, int motorSpeed, USSensor *sensor);

  void setGoal(float goal);
  void setMotorSpeed(int motorSpeed);
  
  float correct();
  float currentValue();
  float error();
  void stop();
  
  bool isGoalReach();
  
};
