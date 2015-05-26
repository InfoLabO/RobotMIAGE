#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>
long timer;

void setup(){
  Robot.begin();
 Robot.beginTFT();
  delay(3000);

  Robot.lineFollowConfig(11,5,50,10);//set PID parameters
  Robot.setMode(MODE_LINE_FOLLOW);
  timer=millis();
  while(!Robot.isActionDone()){
    //pauses line-following for 3 seconds every 5 seconds
    if(millis()-timer>=5000){
      Robot.pauseMode(true);
      delay(3000);
      Robot.pauseMode(false);
      timer=millis();
    }
    Robot.debugPrint(millis());
  }
  Robot.text("Done!",0,10);
  while(true);

}
void loop(){
}
