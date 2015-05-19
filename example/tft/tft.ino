#include <ArduinoRobot.h>

#include "easyTFT.h"

EasyTFT* easyTFT [] = {0,0};

void setup()
{

	Robot.begin();
	Robot.beginTFT();
	Robot.beginSpeaker();

	easyTFT[0] = new EasyTFT(30, 30);
	easyTFT[1] = new EasyTFT(30, 60);

}

void loop()
{

	easyTFT[0]->text("ToNorth");
	easyTFT[1]->text((int)Robot.compassRead());
	delay(3000);

}
