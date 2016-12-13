// colorsim.c�i���̃v���O�����̖��O)
#include<stdio.h>   // �W�����o�̓w�b�_�̃C���N���[�h
#include"ppmlib.h"  // ppm�t�@�C���p�w�b�_�̃C���N���[�h
#include"label.h"   // ���x�����O�p�w�b�_�̃C���N���[�h

#define RMIN 0.05   // �̈��ʐς̉���(=1%)
#define RMAX 0.3   // �̈��ʐς̏���(=30%)

int main(void)
{
    int x,y;     // ���W�p�̐����ϐ�
    int number;  // �Ǘ��̈��̑���
    int r,g,b;   // �������l�i�F���Ɓj
    int i;       // ���x���p�̐����ϐ�
    int area;    // �̈��̖ʐ�
    int count;   // �ŏI�I�Ɏc�����̈��̑���
	int xmin,ymin,xmax,ymax;  // ���x���̗̈�
    double ratio;  // �ʐϗ�
    int color;     // ���ƕϐ�

    //printf("==== �J���[�V�~�����[�^�[ =====\n");
    //printf("���摜(ppm(�o�C�i��)�`��)���ǂݍ��݂܂�\n");
    load_color_image(0,"");   // �t�@�C�� �� �摜No.0 �ւ̓ǂݍ���
    copy_color_image(0,1);    // �摜No.0 �� �摜No.1 �փR�s�[
    
    // �����P�F�摜No.1 �̖ڕW�̐F�̉��f���F�Œ��o���܂�
    //printf("\n�����P�F�ڕW�̐F�̉��f���F�Œ��o���܂��D\n");
    // ********************************************************************
    // �����ɁC�摜No.1�̉��f�̐F���C���摜(No.0)�̐F�ύX�Ώۗ̈��Ȃ��iR=
    // G=0,B=255�j�C�����łȂ��Ȃ甒�iR=G=B=255�j�ɂ��鏈���������ĉ������D
    // �������͑ΏۂƂ��錴�摜�Ɉˑ����܂��D�܂��C�����ł̑I�ʂ́C������
    // �I�񂾌��摜�����ɗL���ŁC���̉摜�ɂ͎g���Ȃ����̂ŗǂ��ł��D
    // ********************************************************************
    // Red> 1.1*Green Blue>1.1*Green Red>180
    for(x=0;x<width[1];x++){

        for(y=0;y<height[1];y++){
            r=image[0][x][y][0];
            g=image[0][x][y][1];
            b=image[0][x][y][2];
            if( r<g&&b<g){
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
    printf("save mask1\n");
    save_color_image( 1, "mask1.ppm" );
    // �����Q�F���x�����O
    printf("labeling\n");
    // ********************************************************************
    // �֐� labeling( ) ���g���āC�摜No.1 ���w�i���f�̐F�𔒁iR=G=B=255)��
    // ���ă��׃����O���s�Ȃ��C�Ǘ��̈��̑������ϐ� number �ɑ��������L�q��
    // �����ĉ������D�������P�s�����ł��D
    // ********************************************************************
    number=labeling(1,255,255,255);
    printf("finish area is=%d��\n",number);
    if ( number == 0 ){
		printf("no area \n");
		exit(1);
	}

    /// �����R�F�ʐςőI�ʂ���
    //printf("\n�����R�F�ڕW�F�̗̈��̖ʐςőI�ʂ��܂��D\n");
   // printf("�ʐς��͈͊O�̂��͔̂����f�ɂ��܂�.\n");
    count = number;
    // ���x��=1 ���� number �܂ł𒲂ׂ�
    for(i=1;i<=number;i++){
        // ****************************************************************
        // �܂��C���x�� i �̗̈��̖ʐ� area �����߂܂��傤�D
        // ���̍ہC�����ɂ��̗̈��� x, y �͈̔́ixmin,ymin)<--->(xmax,ymax)
        // �����߂Ă����܂��傤�i���̑��������������邽�߂ł��j�D�����ŁC
        // (xmin,ymin)�F���x�� i �̗̈��̍����̍��W
        // (xmax,ymax)�F���x�� i �̗̈��̉E���̍��W
        // ���ɖʐϗ� ratio �����߂܂��傤�D�����ł̖ʐϗ��Ƃ́Carea ���摜
        // �S�̖̂ʐςŊ��������̂ł��D���Ȃ킿�C0.0�`1.0�̎����l�ɂȂ��܂��D
        // ���ɂ��� ratio �̒l�͈̔́i�v���O�����̖`���� define���Œ��`����
        // �Ă��܂��D���̗��ł� 1%�ȏ�30%�ȉ��ł��j�ł͂Ȃ����f�𔒂ɂ��܂��D
        // ���̏����͊��Ɏ��ɏ������Ă��܂��̂ō����Ȃ��Č��\�ł��D
        // ****************************************************************
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
        printf("save mask2.ppm\n");
        save_color_image( 1, "mask2.ppm" );
    } else {
		printf("something error\n");
		exit(1);
	}
    
    // �����S�F�F�̕ύX
    printf("\nchange color\n");
    printf("Red   [-100,100] = ");  scanf("%d",&r);
    printf("Green [-100,100] = ");  scanf("%d",&g);
    printf("Blue  [-100,100] = ");  scanf("%d",&b);
    // ********************************************************************
    // ���摜�iNo.0�j�����X�^�������C�Ή�����No.1�̉��f���̂Ƃ������CNo.0
    // �̉��f�̐F�ɏ��L�̃V�t�g�ʂ������܂��D0���菬�����Ȃ��Ă��܂����� 0,
    // 255 �����傫���Ȃ����� 255 �ɂ��邱�Ƃ����Y���Ȃ��D
    // �����ɂ����āC�ŏI�I�ȏo�͉摜�� No.0 �ɍ������܂��D
    // ********************************************************************
    for(x=0;x<width[0];x++){
            for(y=0;y<height[0];y++){
                if(image[1][x][y][2]==255 && image[1][x][y][1]!=255){
                        image[0][x][y][0]=image[0][x][y][0]+r;
                        image[0][x][y][1]=image[0][x][y][1]+g;
                        image[0][x][y][2]=image[0][x][y][2]+b;
                        for(int aa=0;i<2;i++){
                            if(image[0][x][y][0]<0){
                                image[0][x][y][aa]=0;
                            }else if(255<image[0][x][y][0]){
                                image[0][x][y][aa]=255;
                            }
                        }
                }
            }
    }
    printf("finish\n");
    save_color_image( 0,"");

    return 0;  // �����I���������l���V�X�e���ɕԂ��܂�
}
