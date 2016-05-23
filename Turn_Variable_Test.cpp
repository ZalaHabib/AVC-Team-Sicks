#include <stdio.h>
#include <time.h>

int main(){
  //This code was written to test if it was variable types that were stopping our pi from turning properly
  //Set up variables
  int int_test = 50;
  double dbl_test = 50;
  double out = (int_test/100)*20
  printf("%f\n",out); //Test output with integer
  out = (dbl_test/100)*20
  printf("%f\n",out); //Test output with double
return 0;}
