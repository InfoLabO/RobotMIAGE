#pragma once

class PidOrientation {

 private:
  
  static const float KP;
  static const float KI;
  static const float KD;

  static const int MinDiff;

  bool initilized;
  
  float lastTime;
  float sumError;
  float lastError;

  float goal;

 public:

  PidOrientation(float goal);

  void setGoal(float goal);
  
  float correct();
  float currentValue();
  float error();
  void stop();
  
  bool isGoalReach();
  
};
