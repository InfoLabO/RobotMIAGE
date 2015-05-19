#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int LeftMotorForward = 10 ; 
int LeftMotorReverse = 9 ; 
int RightMotorForward = 12 ; 
int RightMotorReverse = 13 ; 

void setup() {
  // put your setup code here, to run once:
        Robot.begin();
	Robot.beginTFT();
	Robot.beginSpeaker();
        pinMode(LeftMotorForward , OUTPUT) ;
        pinMode(RightMotorForward , OUTPUT);
        pinMode(LeftMotorReverse , OUTPUT);
        pinMode(RightMotorReverse , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RightMotorForward , HIGH) ; 
  digitalWrite ( LeftMotorForward , HIGH) ; 
  delay(1000);
  digitalWrite(RightMotorForward , LOW) ;
  digitalWrite(LeftMotorForward , LOW); 
  delay(1000); 
  
  
}
