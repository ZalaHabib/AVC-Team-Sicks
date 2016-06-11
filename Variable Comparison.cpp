# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);

int main(){
  int intTest = 10;
  double dblTest = 10;
  double outTest = (intTest/20)*20;
  printf("%f",outTest);
  outTest = (dblTest/20)*20;
  printf("\n%f",outTest);
return 0;};
