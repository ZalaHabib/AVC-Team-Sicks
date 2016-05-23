# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);

extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);

extern "C" int set_motor(int motor , int speed );

float kp = 0; //proportional error constant
float kd = 0; //derivative error constant
float ki = 0; //integration error constant 
int prev_error = 0; //previous error signal for derivation
int total_error = 0; //total error signal for integration


int Q3(){
  //Initialises variables for finding colour of pixel, the running total, and the number of white pixels for averaging
  long total = 0;
  int white;
  int left_white = 0;
  int right_white=0;
  int straight_white=0;
  int pixel;
  //Takes picture to analyse
  take_picture();
  //Check for left path
  for(int x=0;x<160;x++){
    //Read pixel
    pixel = get_pixel(x,120,3);
    //If pixel is white, add to total
    if(pixel>128){
      total = total + (x-160);
      left_white++;
      };
    };
  //Check for right path
  for(int x=160;x<320;x++){
    //Read pixel
    pixel = get_pixel(x,120,3);
    //If pixel is white, add to total
    if(pixel>128){
      total = total + (x-160);
      right_white++;
      };
    };
  //Find amount of horizontal white pixels for average if not at intersection
  white = left_white+right_white;
  //Check if straight path ahead
  for(int y=0;x<120;y++){
    //Read pixel
    pixel = get_pixel(160,y,3);
    //If pixel is white, add to total
    if(pixel>128){
      straight_white++;
      };
    };
  //Check if at intersection and act accordingly
  if((left_white>155 && straight_white>115) || (left_white>155 && right_white>155)){
    set_motor(1,-50);
    set_motor(2,50);
    Sleep(0,5);
  }
  else if(straight_white>115&&right_white>155){
    set_motor(1,50);
    set_motor(2,50);
    Sleep(0,5);
  }
  //Find average if white pixels were present
  else if(white>0){
    total=total/white;
    //Print total
    printf("%s", "Base error value: ");
    printf("%d\n",total);
  
    //Perform PID
    int pid_sum; //Declares sum error variable
    int int_error; //Declares integral error variable
    int prop_error = total*kp; //Find proportional error
    int der_error = ((prop_error-error_array[1])*0.1)*kd; //Find derivative error (assume camera check is every 2 seconds)
    prev_error = prop_error; //Update previous error for next iteration
    total_error = total_error + prop_error; //Update total error for integration
    int_error = total_error*ki; //Find integration error
    pid_sum = prop_error+der_error+int_error; //Find sum error
    int left_wheel=0;
    int right_wheel=0;
    if(error>0){
      left_wheel=((error/160)*50)+50;
      right_wheel=((-error/160)*300)+50;
    }
    else{
      left_wheel=((error/160)*300)+50;
      right_wheel=((-error/160)*50)+50;
    }
    set_motor(1,left_wheel);
    set_motor(2,right_wheel);
    };
}
  else{
    set_motor(1,-50);
    set_motor(2,50);
  };
}


int main(){
  init(1);
  for (int i = 0; i<120;i++){
    Q3();
    Sleep(0,1);
  }
return 0;}
