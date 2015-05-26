#pragma once
#include <ArduinoRobot.h>

const int KP = 1;
const int KI = 1;
const int KD = 1;

unsigned long lastTime = 0;
float lastError = 0;
float sumError  = 0;

void turn(int angle);
void pointToCustom(int angle, int speed);
int errAngular(int angleActuel,int angleObjectif);
void pidAngular(int erreur, int erreurPrecedente, int &ML,int &MR int &sommeErreur);
