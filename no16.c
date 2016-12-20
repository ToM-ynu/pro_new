#include<stdio.h>

int main(){
  int n=0;
  scanf("%d",&n);
  printf("%d\n",n);
  int i=0;
  int ans=0;
  while(0<n){
    ans=ans*10;
    ans=ans+n%10;
    //printf("%d\n",ans);
    n=n/10;
  }
  printf("%d\n",ans);
  return 0;
}

