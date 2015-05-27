#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

//#include "turn.h"
#include "orientationLibrary.h";

PidOrientation pidOrientation(0);

void setup()
{

  Robot.begin();
  Robot.beginTFT();
  Serial.begin(9600);

}

void loop()
{

  Robot.drawCompass(Robot.compassRead());
  Serial.print("error      : ");
  Serial.println(pidOrientation.error());
  Serial.print("correction : ");
  Serial.println(pidOrientation.correct());

  //delay(250);
  
}
