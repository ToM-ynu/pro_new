#include<stdio.h>
#include<math.h>
int main(){
  long double ans=0.0;
  long double n=1.0;
  long int memo[50]={};
  for(int i=1;i<50;i++){
    n=n*i;
    memo[i]=n;
  }
  for(int i=30;0<=i;i--){
    //printf("%d  ",memo[i]);
    ans=ans+(1.0/(double)memo[i])*1000000000;
    printf("%.20Lf\n",ans);
  }
  ans=ans+10000000000.0;
  printf("%.20Lf\n",ans);
  ans=ans/1000000000.0;
  printf("%.20Lf\n",ans);
  printf("%.20f\n",exp(1));
  return 0;
}
