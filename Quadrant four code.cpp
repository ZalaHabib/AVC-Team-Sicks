#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);

extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int main(){
  init(0);
  int initial_speed_left=60;
  int initial_speed_right=60;
  int speed_left;
  int speed_right;
  int left_reading;
  int centre_reading;
  int right_reading;

  while(true){
    speed_right = 0;
    speed_left= 0;
    set_motor(1,initial_speed_left);
    set_motor(2,initial_speed_right);
    left_reading = read_analog(1);
    centre_reading = read_analog(0);
    right_reading = read_analog(2);

//two methods below could be substitued for PID

    if(left_reading>right_reading){
      speed_left = 15;
      set_motor(2,initial_speed_left + speed_left);
      Sleep(0,100000);
    };
    if(left_reading<right_reading){
      speed_right = 15;
      set_motor(1,initial_speed_right + speed_right);
      Sleep(0,100000);
    };

//

    if(right_reading > 400 && centre_reading > 400 && left_reading > 400){
      set_motor(1,-initial_speed_right);
      Sleep(1,0);
    };
    if(left_reading > 400 && centre_reading > 400){
      set_motor(1,-initial_speed_right);
      Sleep(0,500000);
    };
    if(right_reading > 400 && centre_reading > 400){
      set_motor(2,-initial_speed_left);
      Sleep(0,500000);
    };
    if(centre_reading > 400){
      set_motor(1,-initial_speed_right);
      Sleep(0,500000);
    };
  };
return 0;};
