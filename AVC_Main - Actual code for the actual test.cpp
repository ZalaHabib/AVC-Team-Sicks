# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int Sleep(int sec, int usec);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
extern "C" int open_screen_stream();

extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);

extern "C" int set_motor(int motor , int speed );


float kp = 0.15; //proportional error constant
float kd = 0.05; //derivative error constant
float ki = 0; //integration error constant
int prev_error = 0; //previous error signal for derivation
int total_error = 0; //total error signal for integration
int white;

int open_gate(){
  //printf("Opening Gate");
  connect_to_server("130.195.6.196", 1024);
  send_to_server("Please");
  char message[24];
  receive_from_server(message);
  send_to_server(message);
  //printf("Gate Hopefully Opened");
return 0;}

int cam_error(){
  //printf("Initialising Camera");
  //Initialises variables for finding colour of pixel, the running total, and the number of white pixels for averaging
  long total = 0;
  white = 0;
  int pixel;
  //Takes picture to analyse
  take_picture();
  for(int y=118;y<122;y++){
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
  //printf("Begin PID");
  int pid_sum; //Declares sum error variable
  int int_error; //Declares integral error variable
  int prop_error = total*kp; //Find proportional error
  int der_error = ((prop_error-prev_error)/0.05)*kd; //Find derivative error
  prev_error = prop_error; //Update previous error for next iteration
  total_error = total_error + prop_error; //Update total error for integration
  int_error = total_error*ki; //Find integration error
  pid_sum = prop_error+der_error+int_error; //Find sum error
  //printf("End PID");
return pid_sum;}

int turn(double error){
  //Right wheel turns backwards
  double left_wheel=60;
  double right_wheel=60;
  if(white<1){
    if(prev_error>0){
      //If path was lost and was last to the left, turn left sharply
      left_wheel=-50;
      right_wheel=50;
    }
    else{
      //If path was lost and was last to right, turn right sharply
      left_wheel=50;
      right_wheel=-50;
    };
  }
  else{
    if(error>0){
      left_wheel=((error/160)*200)+left_wheel;
      right_wheel=((-error/160)*250)+right_wheel;
    }
    else{
      left_wheel=((error/160)*250)+left_wheel;
      right_wheel=((-error/160)*200)+right_wheel;
    };
  };
  set_motor(1,left_wheel);
  set_motor(2,right_wheel);
return 0;}

int Q3(){
  //Initialises variables for finding colour of pixel, the running total, and the number of white pixels for averaging
  double total = 0;
  int white=0;
  int left_white = 0;
  int pixel;
  //Takes picture to analyse
  take_picture();
  //Check for left path
  for(int x=160;x<320;x++){
    //Read pixel
    pixel = get_pixel(x,120,3);
    //If pixel is white, add to total
    if(pixel>110){
      left_white++;
    };
  };
  //Check white pixels in center in order to follow line without influence from far left and right
  for(int y=118;y<122;y++){
    for(int x=60;x<300;x++){
      //Read pixel
      pixel = get_pixel(x,y,3);
      //If pixel is white, add to total
      if(pixel>128){
        total = total + (x-160);
        white++;
      };
    };
  };
  //Check if path to left exists, if so, turn left
  if(left_white>150){
    printf("radishes");
    set_motor(1,50);
    set_motor(2,50);
    Sleep(0,700000);
    set_motor(1,50);
    set_motor(2,-50);
    Sleep(0,700000);
    double error = 1;
    int error_white=0;
    while(error==0){
      error = 0;
      error_white=0;
      take_picture();
      for(int y=118;y<122;y++){
        for(int x=120;x<200;x++){
         //Read pixel
         pixel = get_pixel(x,y,3);
          //If pixel is white, add to total
          if(pixel>128){
            error = error + (x-160);
            error_white++;
          };
        };
      };
      error=error/error_white;
      printf("%d",error);
      Sleep(0,50000);
    };
  }
  //If white pixels are found ahead, perform PID
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
      right_wheel=((-pid_sum/160)*250)+50;
    }
    else{
      left_wheel=((pid_sum/160)*250)+50;
      right_wheel=((-pid_sum/160)*50)+50;
    }
    set_motor(1,left_wheel);
    set_motor(2,right_wheel);
  }
  //If path lost, turn right
  else{
    printf("turnips");
    set_motor(1,-50);
    set_motor(2,50);
    double error = 1;
    int error_white=0;
    while(error>=0){
      error = 0;
      error_white=0;
      take_picture();
      for(int y=118;y<122;y++){
        for(int x=100;x<220;x++){
         //Read pixel
         pixel = get_pixel(x,y,3);
          //If pixel is white, add to total
          if(pixel>128){
            error = error + (x-160);
            white++;
          };
        };
      };
      error=error/160;
      Sleep(0,50000);
    };
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

int main(){
  init(1);
  open_screen_stream();
  while(true){
    int error = cam_error();
    turn(error);
    Sleep(0,50000);
    if(white>1550){
      set_motor(1,60);
      set_motor(2,60);
      Sleep(1,0);
      while(true){
        Q3();
      };
    };
  };
  set_motor(1,0);
  set_motor(2,0);
return 0;}
