#include<stdio.h>

int add(int x){
  return x+1;
}

int main(){
  int x;
  scanf("%d",&x);
  printf("0+1=%d\n",add(0));
  printf("3*x+1=%d\n",add(3*x));
  printf("x+1+1=%d\n",add(x));
  return 0;
}
