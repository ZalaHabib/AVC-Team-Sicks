# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);

extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);

extern "C" int set_motor(int motor , int speed );

float kp = 0.15; //proportional error constant
float kd = 0.05; //derivative error constant
float ki = 0; //integration error constant 
double prev_error = 0; //previous error signal for derivation
double total_error = 0; //total error signal for integration

int Q3test(){
  //Initialises variables for finding colour of pixel, the running total, and the number of white pixels for averaging
  double total = 0;
  int white;
  int left_white = 0;
  int pixel;
  //Takes picture to analyse
  take_picture();
  //Check for left path
  for(int x=0;x<160;x++){
    //Read pixel
    pixel = get_pixel(x,120,3);
    //If pixel is white, add to total
    if(pixel>128){
      left_white++;
      };
    };
  //Check white pixels in center in order to follow line without influence from far left and right
  for(int y=118;y<122;y++){
    for(int x=110;x<210;x++){
      //Read pixel
      pixel = get_pixel(x,y,3);
      //If pixel is white, add to total
      if(pixel>128){
        total = total + (x-160);
        white++;
      };
    };
  };
  //Check if at intersection and act accordingly
  if(left_white>140){
    set_motor(1,50);
    set_motor(2,50);
    Sleep(0,500000);
    set_motor(1,-50);
    set_motor(2,50);
    Sleep(0,500000);
    int error = 1;
    while(error>=0){
      error = 0;
      for(int y=118;y<122;y++){
        for(int x=110;x<210;x++){
         //Read pixel
         pixel = get_pixel(x,y,3);
          //If pixel is white, add to total
          if(pixel>128){
            total = total + (x-160);
            white++;
            };
          };
        };
      };
      Sleep(0,50000);
    }
  //Find average if white pixels were present
  else if(white>0){
    total=total/white;
    //Print total
    printf("%s", "Base error value: ");
    printf("%f\n",total);
  
    //Perform PID
    double pid_sum; //Declares sum error variable
    double int_error; //Declares integral error variable
    double prop_error = total*kp; //Find proportional error
    double der_error = ((prop_error-prev_error)/0.05)*kd; //Find derivative error (assume camera check is every 2 seconds)
    prev_error = prop_error; //Update previous error for next iteration
    total_error = total_error + prop_error; //Update total error for integration
    int_error = total_error*ki; //Find integration error
    pid_sum = prop_error+der_error+int_error; //Find sum error
    double left_wheel=0;
    double right_wheel=0;
    if(pid_sum>0){
      left_wheel=((pid_sum/160)*50)+50;
      right_wheel=((-pid_sum/160)*300)+50;
    }
    else{
      left_wheel=((pid_sum/160)*300)+50;
      right_wheel=((-pid_sum/160)*50)+50;
    }
    set_motor(1,left_wheel);
    set_motor(2,right_wheel);
  }
  else{
    set_motor(1,50);
    set_motor(2,-50);
  };
return 0;}

int main(){
  init(1);
  for (int i = 0;1<300;i++){
    printf("%d\n",i);
    Q3test();
    Sleep(0,50000);
  }
return 0;}
