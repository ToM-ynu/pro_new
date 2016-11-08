#include<stdio.h>
#include<math.h>
int main(){
  double ans=1.0;
  double n=1;
  double memo[1000];
  for(int i=1;i<901;i++){
    n=n*i;
    memo[i]=n;
  }
  for(int i=1;i<900;i++){
    //printf("%d  ",memo[i]);
    ans= ans+(1.0/memo[i]);
    //printf("%.20f\n",ans);
  }
  printf("%.20f\n",ans);
  printf("%.20f\n",exp(1));
}
