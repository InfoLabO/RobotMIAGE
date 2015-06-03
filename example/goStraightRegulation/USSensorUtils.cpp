#include "USSensorUtils.h";

const int USSensor::DigitalPin = D0;
const int USSensor::LeftPin = M4;
const int USSensor::RightPin = M0;
const int USSensor::FrontPin = M2;
const int USSensor::BackPin = M6;


void USSensor::init() {
  
  delay(250);
  pinMode(DigitalPin, OUTPUT); // la patte utilisée pour l'activation de la lecture des sonars
  digitalWrite(DigitalPin, HIGH);
  delayMicroseconds(25);
  digitalWrite(DigitalPin, LOW);
  pinMode(DigitalPin, INPUT);
  
}

float USSensor::getDistance(int pin) {
 
  int avg, prevprev, prev, last;
  
  prevprev = Robot.analogRead(pin);
  delay(10);
  
  prev = Robot.analogRead(pin);
  delay(10);
  
  do {
    
    prevprev = prev;
    prev = last;
    last = Robot.analogRead(pin);    
    avg = (prevprev + prev)>>1; // Average of 2 last distance
    
  } while (abs(avg-last)>2);
  
  return last; 
  
}

float USSensor::getRightDistance() {
  
  int left = getDistance(RightPin);
  
}

float USSensor::getLeftDistance() {
  
  int left = getDistance(LeftPin);
  
}

float USSensor::getFrontDistance() {
  
  return getDistance(FrontPin);
  
}

float USSensor::getBackDistance() {
  
  return getDistance(BackPin);
  
}
