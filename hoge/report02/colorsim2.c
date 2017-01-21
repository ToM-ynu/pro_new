#include<stdio.h>   // ?��W?��?��?��?��?��o?��̓w?��b?��_?��̃C?��?��?��N?��?��?��[?��h
#include"ppmlib.h"  // ppm?��t?��@?��C?��?��?��p?��w?��b?��_?��̃C?��?��?��N?��?��?��[?��h
#include"label.h"   // ?��?��?��x?��?��?��?��?��O?��p?��w?��b?��_?��̃C?��?��?��N?��?��?��[?��h
#include<math.h>

#define RMIN 0.05   // ?��̈�?��ʐς̉�?��?��(=1%)
#define RMAX 0.3   // ?��̈�?��ʐς̏�?��?��(=30%)

void changeRGB(int r,int g,int b,
     double *h ,double *s, double *v){
    double max=fmax(r,fmax(g,b));
    double min=fmin(r,fmin(g,b));
    if(r==g&&r==b)*h=0;
    if(max==r)*h=g-b;
    if(max==g)*h=b-r;
    if(max==b)*h=r-g;
    if(*h!=0)*h=60*(*h)/(max-min);
    while(360<*h){
      *h=*h-360.0;
    }
    while(*h<0.0){
      *h=*h+360.0;
    }
    *v=max/255;
    if(max!=min){
      *s=1-min/max;    
    }else{
      *s=0;
    }
    *v=max;
}
double amari(double val,int num){
    while(num<val){
        val=val-num;
    }
    return val;
}
void changeHSV(double h,double s,double v,
        int *r,int *g,int *b){
  if(h==-1&&s==-1&&v==-1){
    *r=0;
    *g=0;
    *b=0;
    return ;
  }
    double hh=h/60.0;
    double max=v;
    double min=max*(1-s);
    double cr,cg,cb;
    int i=(int)hh;
    if(h==-1){
        cr=0;
        cg=0;
        cb=0;
    }else{
        switch (i){
            case 0:
              cr=max;
              cg=(h/60)*(max-min)+min;
              cb=min;
            break;
            case 1:
              cr=(120-h)/60*(max-min)+min;;
              cg=max;
              cb=min;
            break;
            case 2:
              cr=min;
              cg=max;
              cb=(h-120)/60*(max-min)+min;
            break;
            case 3:
              cr=min;
              cg=(240-h)/60*(max-min)+min;
              cb=max;
            break;
            case 4:
              cr=(h-240)/60*(max-min)+min;
              cg=min;
              cb=max;
            break ;
            case 5:
              cr=max;
              cg=min;
              cb=(360-h)/60*(max-min)+min;
            break;
        }
    *r=(int)255*cr;
    *g=(int)255*cg;
    *b=(int)255*cb;
    }
}
int main(void)
{
    int x,y;     // ?��?��?��W?��p?��̐�?��?��?��ϐ�
    int number;  // ?��Ǘ�?��̈�?��̑�?��?��
    int r,g,b;   // ?��?��?��?��?��?��?��l?��i?��F?��?��?��Ɓj
    int i;       // ?��?��?��x?��?��?��p?��̐�?��?��?��ϐ�
    int area;    // ?��̈�?��̖ʐ�
    int count;   // ?��ŏI?��I?��Ɏc?��?��?��?��?��̈�?��̑�?��?��
    double h,s,v;
	int xmin,ymin,xmax,ymax;  // ?��?��?��x?��?��?��̗̈�
    double ratio;  // ?��ʐϗ�
    int color;     // ?��?��?��ƕϐ�

    printf("read file name\n");
    load_color_image(0,"");   // ?��t?��@?��C?��?�� ?��?�� ?��摜No.0 ?��ւ̓ǂݍ�?��?��
    copy_color_image(0,1);    // ?��摜No.0 ?��?�� ?��摜No.1 ?��փR?��s?��[
    
    printf("write blue\n");
    long hoge=0;
    for(x=0;x<width[1];x++){

        for(y=0;y<height[1];y++){
            r=image[0][x][y][0];
            g=image[0][x][y][1];
            b=image[0][x][y][2];
        changeRGB(r,g,b,&h,&s,&v);
            if (70<h&&h<180){
              if(hoge%100==0){
                          //printf("two:%d:%d:%d\t%.2f:%.2f:%.2f\n"
                          //,r,g,b,h,s,v);
              }
                        image[1][x][y][0]=0;    //r
                        image[1][x][y][1]=0;    //g
                        image[1][x][y][2]=255;  //b
            }else{

                        image[1][x][y][0]=255;
                        image[1][x][y][1]=255;
                        image[1][x][y][2]=255;
            }
        }
    }
    printf("pic choise area and color to blue save at mask1.ppm \n");
    save_color_image( 1, "mask1.ppm" );


    number=labeling(1,255,255,255);
    printf("finish area is=%d\n",number);
    if ( number == 0 ){
		printf("something error 1\n");
		exit(1);
	}


    count = number;
    for(i=1;i<=number;i++){

        xmax=0,ymax=0;
        xmin=width[1],ymin=height[1];
        area=0;
        for(x=0;x<width[1];x++){
            for(y=0;y<height[1];y++){
                if(xmax<x){
                    xmax=x;
                }
                if(ymax<y){
                    ymax=y;
                }
                if(x<xmin){
                    xmin=x;
                }
                if(y<ymin){
                    ymin=y;
                }
                if ( label[x][y] == i ){
                    area++;
                }
            }
        }
        ratio=(double)area/(double)(width[1]*height[1]);
        if(10<area){
            printf("labe; is %d \t%.2f\n",i,ratio*100);
        }
		if ( ratio<=RMIN || RMAX<=ratio ){
            count--;
            if(10<area)
                printf("del %d\n",i);
            for(y=ymin;y<=ymax;y++){
                for(x=xmin;x<=xmax;x++){
                    if ( label[x][y] == i ){
                        image[1][x][y][0] = 255;
                        image[1][x][y][1] = 255;
                        image[1][x][y][2] = 255;
                    }
                }
            }
        }
    }
    printf("finish area2=%d\n",count);
    if ( count > 0 ){
        printf("update blue area\n");
        save_color_image( 1, "mask2.ppm" );
    } else {
		printf("something error\n");
		exit(1);
	}
    printf("change color\n");
    int temph;
    printf("h   ?��̃V?��t?��g?��?�� [-180,+180] = ");  scanf("%d",&temph);
    long debug=0;
    for(x=0;x<width[0];x++){
            for(y=0;y<height[0];y++){
              debug++;
              r=image[0][x][y][0];
              g=image[0][x][y][1];
              b=image[0][x][y][2];
                if(image[1][x][y][2]==255 &&
                   image[1][x][y][0]!=255){
                        changeRGB(r,g,b,&h,&s,&v);
                        if(debug%100==0){
                          //printf("one:%d:%d:%d\t%.2f:%.2f:%.2f\n"
                          //,r,g,b,h,s,v);
                        }
                        if(h+temph>360){
                            h=h+temph-360;
                        }else{
                            h=h+temph;
                        }
                        changeHSV(h,s,v,&r,&g,&b);
                        if(debug%100==0){
                          //printf("two:%d:%d:%d\t%.2f:%.2f:%.2f\n"
                          //,r,g,b,h,s,v);
                        }
                        if(r<0){
                          r=0;
                        }else if(255<r){
                          r=255;
                        }
                        if(g<0){
                          g=0;
                        }else if(255<g){
                          g=255;
                        }
                         if(b<0){
                           b=0;
                         }else if(255<b){
                           b=255;
                         }
                        image[0][x][y][0]=r;
                        image[0][x][y][1]=g;
                        image[0][x][y][2]=b;
                }
            }
    }
    printf("finish\n");
    save_color_image( 0,"");

    return 0;  // ?��?��?��?��?��I?��?��?��?��?��?��?��?��?��l?��?��?��V?��X?��e?��?��?��ɕԂ�?��܂�
}
