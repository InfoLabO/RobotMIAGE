#include "turn.h"

#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

void turn(int angle)
{
  int current = Robot.compassRead();
  pointToCustom((current + angle + 360) % 360, 150); 
}

void pointToCustom(int angle, int speed)
{
  int target = (angle + 360) % 360;
  int current = 0;
  int otherSide = 0;
  int lastWay = -1, way = -1;
  
  while(speed >= 50) {
    current = Robot.compassRead();
    Robot.debugPrint(current);
    
    if(abs(current - target) == 0) {
      Robot.motorsStop();
      delay(500);
      if(abs(Robot.compassRead() - target) != 0) {
	pointToCustom(angle, speed - 50);
      }
      break;
    }
    
    otherSide = (current + 180) % 360;
    lastWay = way;
    if(otherSide < current) {
      if(otherSide < target && target < current) {
        way = 1;
        Robot.motorsWrite(speed, -speed);
      } else {
        way = 0;
        Robot.motorsWrite(-speed, speed);
      }
    } else {
      if(current < target && target < otherSide) {
        way = 0;
        Robot.motorsWrite(-speed, speed);
      } else {
        way = 1;
        Robot.motorsWrite(speed, -speed);
      }
    }
    
    if(lastWay >= 0 && way != lastWay) {
      speed -= 10;
    }
  }
}
