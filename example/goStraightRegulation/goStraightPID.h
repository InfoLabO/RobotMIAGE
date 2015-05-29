#pragma once

class StraightPID {

 private:
  
  static const float KP;
  static const float KI;
  static const float KD;

  static const int MinDiff;

  bool initilized;
  
  float lastTime;
  float sumError;
  float lastError;
  int sensorPin ;
  float goal;

 public:

  StraightPID(float goal,int sensorPin);

  void setGoal(float goal);
  
  float correct();
  float currentValue();
  float error();
  void stop();
  
  bool isGoalReach();
  
};
