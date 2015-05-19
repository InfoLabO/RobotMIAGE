#include <ArduinoRobot.h>
#include <SPI.h>
#include <Wire.h>

char * oldM = 0;
int oldX, oldY;

void turnClock(int turnSpeed);
void turnAntiClock(int turnSpeed);

void pointTo(int angle, int tolerance);
void easyText(const char *m, int posX, int posY);
void textInt(int x, int posX, int posY);

void setup()
{

  Robot.begin();
  Robot.beginSD();
  Robot.beginTFT();
  Robot.beginSpeaker();

  Robot.drawBMP("logo.bmp", 0, 0);

}

void loop()
{
  
  easyText("To North", 30, 30);
  pointTo(0, 0);
  
  easyText("To West", 30, 30);
  pointTo(90, 0);
  
  easyText("To South", 30, 30);
  pointTo(180, 0);
  
  easyText("To East", 30, 30);
  pointTo(270, 0);
  
  Robot.beep();
  
  easyText("To North", 30, 30);
  pointTo(0, 0);
  
  easyText("To East", 30, 30);
  pointTo(270, 0);
  
  easyText("To South", 30, 30);
  pointTo(180, 0);
  
  easyText("To West", 30, 30);
  pointTo(90, 0);
  
  Robot.beep();
  
}

void pointTo(int angle, int tolerance) {
  
  const int turnSpeed = 100;
  
  int compass;
  int diff;
  
   do {
  
    compass = Robot.compassRead();
    diff = angle - compass;
    diff = diff >  180 ?  diff - 360 : diff;
    diff = diff < -180 ?  diff + 360 : diff;
    
    if( diff > 0)
      
      turnClock(turnSpeed);
      
    else
    
      turnAntiClock(turnSpeed);
      
    } while(abs(diff) > tolerance);
    
    Robot.motorsStop();
  
}

void turnClock(int turnSpeed) {
  
  Robot.motorsWrite(-turnSpeed, turnSpeed);
  
}

void turnAntiClock(int turnSpeed) {
  
  Robot.motorsWrite(turnSpeed, -turnSpeed);
  
}

void easyText(const char *m, int posX, int posY) {

  int i = 0;
  
  if( oldM != 0) {
    
    Robot.stroke(255,255,255);
    Robot.text(oldM,oldX,oldY);
  
    delete [] oldM;
    
  }
  
  Robot.stroke(0,0,0);
  Robot.text(m,posX,posY);
  
  while(m[i] != '\0') {
    
    ++i;
    
  }
  
  oldM = new char[i+2];
  
  for(int i2 = 0; i2 <= i; ++i2)
  
    oldM[i2] = m[i2];
  
  oldX = posX;
  oldY = posY;
  
}

void textInt(int r, int posX, int posY) {
  
  char * sint = new char[12];
  int i = 0;
  
  while(r != 0) {
    
    sint[i] = char((r % 10) + 48);
    r /= 10;
    ++i;
    
  }
  
  sint[i] = '\0';
  
  easyText(sint, posX, posY);
  
  delete [] sint;
  
}
  

