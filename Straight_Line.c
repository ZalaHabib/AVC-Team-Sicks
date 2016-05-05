#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);
extern "C" int SetMotor(int motor, int dir, int speed);

int main(int dir, int speed, int time){
//Ensures RPi is operational
init(0);
//Set motor direction and speed
SetMotor(1,dir,speed);
SetMotor(2,dir,speed);
//Set length of times that motors will be active
Sleep(time,0);
//Stop Motors
SetMotor(1,1,0);
SetMotor(2,1,0);
return 0;}

