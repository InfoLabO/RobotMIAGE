#pragma once
#include <ArduinoRobot.h>

void turn(int angle);
void pointToCustom(int angle, int speed);
int errAngular(int angleActuel,int angleObjectif);
void pidAngular(int erreur, int erreurPrecedente, int &ML,int &MR int &sommeErreur);
