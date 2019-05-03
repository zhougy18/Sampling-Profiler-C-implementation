#include <stdlib.h>
#include "hotspots_sampling.h"

int a=0;
int b=1;

void func_a()
{
  int i;
  for (i = 0; i < 25*1000000; i++){
    a = b + i;  
  }
}

void func_b(){
  int i;
  for (i = 0; i < 150*1000000; i++){
    a = b + i;
  }
}

void func_c(){
  int i;
  for (i = 0; i < 500*1000000; i++){
    a = b + i;
  }
}

int main (int argc, char **argv){
  //sample at argv[1] Hz
  start_analysis(atoi(argv[1]));
  int i;
  func_b();
  for(i = 0; i < 100*1000000; i++){
    a = b + i;
  }
  func_a();
  func_b();
  func_a();
  func_c();
  func_a();
  func_a();
  end_analysis();
  return 0;
}



