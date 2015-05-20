#include "USSensorUtils.h";

// Return the distance in cm of a specifical pin (M0 to M7 for us)
float getDistance(int pin) {
  // read the value from the sensor
  int sensorValue = Robot.analogRead(pin);
  //Convert the sensor input to cm.
  float distance_cm = sensorValue * 1.5;
  //return distance_cm;
  return distance_cm;
}
 
//Print the distance of an obstacle in front of the pin sensor  
void printDistanceOnTFT(int pin){
  Robot.background(0, 0, 255);
  Robot.setCursor(44, 60);
  Robot.stroke(0, 255, 0);
  Robot.print(getDistance(pin));  
}
