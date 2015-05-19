#include <ArduinoRobot.h>
#include  <Wire.h>
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
        Robot.begin();
	Robot.beginTFT();
	Robot.beginSpeaker();
}

void loop() {
  // put your main code here, to run repeatedly:
  Robot.motorsWrite(255,255); //Make the robot go forward, full speed
  delay(3000);
  Robot.motorsStop();
  delay(1000);
  Robot.motorsWrite(-255,-255); //Make the robot go forward, full speed
  delay(3000);
}
