#include <ArduinoRobot.h>

#include "orientationLibrary.h";
#include <Wire.h>
#include <SPI.h>

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
  
  while(speed >= 50)
  {
    current = Robot.compassRead();
    Robot.debugPrint(current);
    
    if(abs(current - target) == 0)
    {
      Robot.motorsStop();
      delay(500);
      if(abs(Robot.compassRead() - target) != 0)
      {
        pointToCustom(angle, speed - 50);
      }
      break;
    }
    
    otherSide = (current + 180) % 360;
    lastWay = way;
    if(otherSide < current)
    {
      if(otherSide < target && target < current)
      {
        way = 1;
        Robot.motorsWrite(speed, -speed);
      }
      else
      {
        way = 0;
        Robot.motorsWrite(-speed, speed);
      }
    }
    else
    {
      if(current < target && target < otherSide)
      {
        way = 0;
        Robot.motorsWrite(-speed, speed);
      }
      else
      {
        way = 1;
        Robot.motorsWrite(speed, -speed);
      }
    }
    
    if(lastWay >= 0 && way != lastWay)
    {
      speed -= 10;
    }
  }
 }
 
 
int errAngular(int angleActuel,int angleObjectif){
   int erreur = (angleObjectif-angleActuel)% 360;
   if(erreur > 180){
       erreur = erreur-360;
   }else if(erreur <-180){
       erreur = erreur + 360;
   }
   return erreur;
 }
 
 void pidAngular(int erreur, int erreurPrecedente, int &ML,int &MR int &sommeErreur ,int kp ,int ki , int kd){
     sommeErreur+=erreur;
     int deltaErreur = erreur-erreurPrecedente;
     int pid  = kp*erreur + ki*sommeErreur + kd*deltaErreur;
     if(pid < 0){
       pid=0;
     }
     else if(pid > 255){
       pid = 255;
     }
     if(erreur>0){
       &ML = 255 - pid;
       &MR = pid -255 ;
     }else{
       &MR = 255 - pid;
       &ML = pid -255 ;
     }
     
 }
