# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int Sleep(int sec, int usec);

int main(){
    //This sets up the RPi hardware and ensures 
    //everything is working correctly
    init(0);
    //Initialises variables for finding colour of pixel, the running total, and the number of white pixels for averaging
    long total = 0;
    int white = 0;
    int pixel;
    //Takes picture to analyse
    take_picture();
    for(y=115,y<125,y++){
       for(x=0,x<320,x++){
	  //Read pixel
          pixel = get_pixel(x,y,3);
	  //Print value for debugging purposes
          printf("%d\n",pixel); 
          //If pixel is white, add to total
          if(pixel>128){
	  total = total + (x-160);
	  white++;
	};
       };
    //Find average if white pixels were present
    if(white>0){
    	total=total/white;
    };
    //Print total
    printf("\n%d\n",total);
return 0;}
