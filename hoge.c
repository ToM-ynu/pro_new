#include<stdio.h>

int a=111;
int c=123;
int main(){
  int *b=&a;
  printf("a=%d:\t%p\n",a,&a);
  printf("b==%d:\t%p\n",*b,&b);
  printf("c==%d:\t%p\n",c,&c);
  b=(int *)0x601038;
  *b=3;
  printf("a=%d:\t%p\n",a,&a);
  return 0;
}
