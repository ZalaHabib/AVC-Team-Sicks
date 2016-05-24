# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);

extern "C" int set_motor(int motor , int speed );


int main(){
  init(1);
  double error = -20;
  //Left wheel turns backwards
  double left_wheel=40;
  double right_wheel=46;
//  if(white<1){
//    if(prev_error>0)
      //If path was lost and was last to the left, turn left sharply
  //    left_wheel=200;
 //     right_wheel=200;
 //   }
  //  else{
      //If path was lost and was last to right, turn right sharply
   //   left_wheel=-200;
  //    right_wheel=-200;
  //  }
//  }
 // else{
    if(error>0){
      left_wheel=((error/160)*200)+left_wheel;
      right_wheel=((-error/160)*300)+right_wheel;
    }
    else if(error<0){
      left_wheel=((error/160)*200)+left_wheel;
      right_wheel=((-error/160)*300)+right_wheel;
    }
  printf("%d",left_wheel);
  printf("%d",right_wheel);
  set_motor(2,left_wheel);
  set_motor(1,right_wheel);
  Sleep(3,0);
  set_motor(1,0);
  set_motor(2,0);
return 0;}
