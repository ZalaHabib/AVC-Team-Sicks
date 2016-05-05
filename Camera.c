# include <stdio.h>
# include <time.h>

extern "C" int InitHardware();#include <stdio.h>
#include <time.h>

\\these load specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);

int main(){
    //This sets up the RPi hardware and ensures 
    //everything is working correctly
    init(0);
    //Initialises variables for finding colour of pixel
    //and the running total
    int total;
    char c;
    //Takes picture to analyse
    take_picture();
    for(y=115,y<125,y++){
       for(x=0,x<320,x++){
	  //Read pixel
          c = get_pixel(x,y,3);
	  //Print value for debugging purposes
          printf("%d\n",c); 
          //If pixel is white, add to total
          if(c>128){
	  total = total + (x-320);
	};
       };
    //Print total
    printf("\n%d\n",total);
return 0;}
