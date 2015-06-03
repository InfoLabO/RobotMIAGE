#pragma once

class StraightPID {

 private:
  
  static const float KP;
  static const float KI;
  static const float KD;

  static const unsigned int MaxDiff;

  bool initilized;

  // In dregree between 0 and 359 increase in clock wise
  float goal;
  int motorSpeed;

  // Time in second
  float lastTime;
  
  float sumError;
  float lastError;

 public:

  StraightPID(float goal, int motorSpeed);

  void setGoal(float goal);
  void setMotorSpeed(float motorSpeed);
  
  float correct();
  float currentValue();
  float error();
  void stop();
  
  bool isGoalReach();
  
};
