#pragma once

#include <ArduinoRobot.h>

class USSensor {
  
  private:
  
    static const int DigitalPin;
    
    static const int RightPin;
    static const int LeftPin;
    static const int FrontPin;
    static const int BackPin;
  
    float getDistance(int pin);
  
  public:

    void init();
    
    float getRightDistance();
    float getLeftDistance();
    float getFrontDistance();
    float getBackDistance();
  
};

