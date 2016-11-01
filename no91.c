#include<stdio.h>

int main(){
  int x;
  while(1){
    scanf("%d",&x);
    if(x<0){
      break;
    }
    if(x%2==0){
      printf("odd\n");
    }else{
      printf("even\n");
    }
  }
  return 0;
}
/*
4
odd
5
even
-1
*/
