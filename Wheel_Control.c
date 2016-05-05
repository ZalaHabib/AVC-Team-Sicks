#include <stdio.h>
#include <time.h>

extern "C" int InitHardware();
extern "C" int Sleep(int sec, int usec);
extern "C" int SetMotor(int motor, int dir, int speed);

int main(int dir, int speed, int time, int wheel){
//Ensures RPi is operational
InitHardware();
//Set motor direction and speed
SetMotor(wheel,dir,speed);
//Set length of times that motors will be active
Sleep(time,0);
//Stop Motors
SetMotor(wheel,dir,0);
return 0;}
