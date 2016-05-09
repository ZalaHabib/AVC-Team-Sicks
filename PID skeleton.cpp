# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);

int main(){
  //Establishes array used to hold data used for PID
  //error[0] = sum error signal
  //error[1] = previous error signal for derivation
  //error[2] = total error signal for integration
  //error[3] = current proportional error
  //error[4] = current derivative error
  //error[5] = current integration error
  int[5] error;
  for(int i = 0; i<6; i++){
    error[i]=0);
    };
  for(int i = 0;i<5;i++){ //Run code a number of times to debug
    error=cam_error(error);
    printf("%s", "Sum error value: ");
    printf("%d\n",error[0]);
    printf("%s", "Previous error value: ");
    printf("%d\n",error[1]);
    printf("%s", "Total error value: ");
    printf("%d\n",error[2]);
    printf("%s", "Proportional error value: ");
    printf("%d\n",error[3]);
    printf("%s", "Derivative error value: ");
    printf("%d\n",error[4]);
    printf("%s", "Integral error value: ");
    printf("%d\n\n\n",error[5]);
    Sleep(2,0);
    };
return 0;}

int[5] cam_error(int[5] error_array){
  //This sets up the RPi hardware and ensures 
  //everything is working correctly
  init(0);
  //Initialises variables for finding colour of pixel, the running total, and the number of white pixels for averaging
  long total = 0;
  int white = 0;
  int pixel;
  //Takes picture to analyse
  take_picture();
  for(int y=115;y<125;y++){
    for(int x=0;x<320;x++){
      //Read pixel
      pixel = get_pixel(x,y,3);
      //If pixel is white, add to total
      if(pixel>128){
        total = total + (x-160);
        white++;
        };
      };
    };
  //Find average if white pixels were present
  if(white>0){
    total=total/white;
    };
  //Print total
  printf("%s", "Base error value: ");
  printf("%d\n",total);
  
  //Perform PID
  //error_array[0] = sum error signal
  //error_array[1] = previous error signal for derivation
  //error_array[2] = total error signal for integration
  //error_array[3] = current proportional error
  //error_array[4] = current derivative error
  //error_array[5] = current integration error
  //establishes constants
  float kp = 0; //proportional error constant
  float kd = 0; //derivative error constant
  float ki = 0; //integration error constant
  error_array[3] = total*kp; //Find proportional error
  error_array[4] = ((error_array[3]-error_array[1])*0.2)*kd; //Find derivative error (assume camera check is every 2 seconds)
  error_array[1] = error_array[3]; //Update previous error for next iteration
  error_array[2] = error_array[2] + error_array[3]; //Update total error for integration
  error_array[5] = error_array[2]*ki; //Find integration error
  error_array[0] = error_array[3]+error_array[4]+error_array[5]; //Find sum error
return error_array;}
