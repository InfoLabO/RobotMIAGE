#pragma once

class PidOrientation {

 private:
  
  static const float KP;
  static const float KI;
  static const float KD;

  static const int MinDiff;

  bool initilized;
  
  unsigned long lastTime;
  float sumError;
  float lastError;

  float goal;

 public:

  PidOrientation(int goal);
  
  void correct();
  float currentValue();
  float error();
  void stop();
  
  bool isGoalReach();
  
};
