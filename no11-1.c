#include<stdio.h>
int loop(int x);
int main(){
int i=0;
scanf("%d",&i);
printf("%d\n",loop(i));
return 0;
}

int loop(int x){
  if(x==1){
    return 1;
  }else{
    return x*loop(x-1);
}
}
