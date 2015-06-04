#include <ArduinoRobot.h>

#include "USSEnsorUtils.h";
#include <Wire.h>
#include <SPI.h>

// pin is used by the sensors
USSensor *usSensor;
int USLValue;
int USRValue;

void setup() {
  Serial.begin(9600);
  Robot.begin();
  Robot.beginTFT();
  usSensor = new USSensor();
  usSensor->init();
}

void loop() {
  USRValue = usSensor->getLeftDistance();
  USLValue = usSensor->getRightDistance();
  if(usSensor->getFrontDistance()<25 || USLValue<12 || USRValue<12){
    
    Robot.motorsStop();
    if(USLValue<12){
        Robot.motorsWrite(80 , -80) ; 
    }else if(USRValue<12){
      Robot.motorsWrite(-80 , 80) ; 
    }else {
        if(USRValue< USLValue){
         Robot.motorsWrite(-80 , 80) ; 
        }else{
           Robot.motorsWrite(80 , -80) ; 
         } 
    }
     
  }else{
    Robot.motorsWrite(200,200);
    }
}
