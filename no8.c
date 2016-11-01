#include<stdio.h>

int max1(int x, int y){
   if(x<y){
     return y;
   }else{
     return x;
   }
}
int max2(int x, int y){
  if(x<y){
    return y;
  }
  if(y<x){
    return x;
  }
}

int max3(int x, int y){
  return (x<y? y: x);
}

int main(){
  int x=3,y=5;
  printf("max is %d\n",max1(x,y));
  printf("max is %d\n",max2(x,y));
  printf("max is %d\n",max2(x,y));
  return 0;
}
/*
max is 5
max is 5
max is 5
*/
