#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
  srand((unsigned int)time(NULL));
  int randam= rand()%100;
  int x;
  while(1){
    printf("%d\n",randam);//for debug
    scanf("%d",&x);
    if(x==randam){
      printf("Bingo!!\n");
      break;
    }
  }
  return 0;
}
