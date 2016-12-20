#include<stdio.h>
#include<math.h>
double dist(double, double);
int main(){
  double x,y;
  printf("x=");
  scanf("%lf",&x);

  printf("y=");
  scanf("%lf\n",&y);

  printf("dis= %lf",dist(x,y));

  return 0;
}

double dist(double x,double y){
  return (x*x+y*y);
}

