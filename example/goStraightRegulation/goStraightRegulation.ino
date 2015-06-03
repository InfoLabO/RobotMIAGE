#include "pidWall.h";
#include "USSensorUtils.h"
#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

USSensor *usSensor;
PidWall *pidWall;

void setup() {
  Robot.begin();
  Robot.beginTFT();
  Serial.begin(9600);
  usSensor = new USSensor();
  usSensor->init();
  pidWall = new PidWall(0, 105, usSensor);
} 

void loop() {
  
  Serial.print("value   :");
  Serial.println(Robot.analogRead(M4));
  Serial.print("error      : ");
  Serial.println(pidWall->error());
  Serial.print("correction : ");
  Serial.println(pidWall->correct());
  Serial.println("---------------------------------------");
  
  Robot.background(0, 0, 255);
  Robot.stroke(0, 255, 0);
  Robot.setCursor(0, 40);
  Robot.print("left : ");
  Robot.setCursor(80, 40);
  Robot.print(Robot.analogRead(M4));
  Robot.setCursor(0, 60);
  Robot.print("right : ");
  Robot.setCursor(80, 60);
  Robot.print(Robot.analogRead(M0));
  Robot.setCursor(0, 80);
  Robot.print("error : ");
  Robot.setCursor(80, 80);
  Robot.print(pidWall->error());
  Robot.setCursor(0, 100);
  Robot.print("correction : ");
  Robot.setCursor(80, 100);
  Robot.print(pidWall->correct());

}
