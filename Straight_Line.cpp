#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor, int speed);

int main(){
//Ensures RPi is operational
init(1);
//Set motor speed
set_motor(1,40);
set_motor(2,40);
//Set length of times that motors will be active
Sleep(5,0);
//Stop Motors
set_motor(1,0);
set_motor(2,0);
return 0;}
