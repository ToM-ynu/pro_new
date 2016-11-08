/*algorithm(header C++) */
#include<stdio.h>
#include<algorithm>
using namespace std;
int main(){
  int a[3];
  scanf("%d,%d,%d",&a[0],&a[1],&a[2]);
  sort(a,a+3);
  printf("%d,%d,%d",a[2],a[1],a[0]);
  return 0;
}


