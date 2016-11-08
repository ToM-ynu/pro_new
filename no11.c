#include<stdio.h>

int main(){
  int n,ans;
  scanf("%d",&n);
  ans=1;
  for(int i=1;i<=n;i++){
    ans= ans*i;
  }
  printf("%d",ans);
  return 0;
}
