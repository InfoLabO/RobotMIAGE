#pragma once

class PidWall {

 private:
  
  static const float KP;
  static const float KI;
  static const float KD;

  bool initilized;
  
  float lastTime;
  float sumError;
  float lastError;
  int sensorPin ;
  float goal;

 public:

  PidWall(float goal,int sensorPin);

  void setGoal(float goal);
  
  float correct();
  float currentValue();
  float error();
  void stop();
  
  bool isGoalReach();
  
};
