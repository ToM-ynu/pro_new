// heikatsu.c  ���̃v���O�����̖��O
// ****************************************************
// �����́u�s���S�ȁv�v���O�����ł��D���̃v���O������
// �@�C�A�C�B�̕����ɓK�؂ȋL�q�������āC���������삷
// ���v���O�����ɕς��Ă������o���ĉ������D
// ****************************************************
#include<stdio.h>
#include"pgmlib.h"
#include<time.h>

int main(void)
{
	int h;                     // �ϊ����̃q�X�g�O�����̍���
	int fmin = 255, fmax = 0;  // �摜�̍Œ��K���l�E�ő��K���l
	int x, y;                   // �����ϐ�
	int g = 0;                   // �ϊ����̏����K���l
	int count;                 // �e�K�� g �̉��f�̐�
	int f;                     // �B�ŊK���ɂ��Ă�for���[�v��
							   // �����Ƃ��̐����ϐ�
 clock_t start,end;
	printf("===== �q�X�g�O�����������̃v���O���� ===\n");
	printf("���摜���ǂݍ��݂܂�\n");
	load_image(0, "");       // �t�@�C�� �� �摜No.0 �֓ǂݍ���
	copy_image(0, 1);        // �摜No.0 �� �摜No.1 �փR�s�[


start=clock();
	//decide h
	printf("%d,%d\n", width[0], height[0]);
	h = width[0] * height[0] / 256;

	// h (�����������̃q�X�g�O�����̍����j�����߂�
	// *********************************************
	//
	//    �@���̕����ɓK�؂ȋL�q�������܂��傤
	//
	// *********************************************

	printf("h=%d\n", h);

	//find fim fmax
	for (int i = 0; i < width[0]; i++) {
		for (int j = 0; j < height[0]; j++) {
			if (fmin > image[0][i][j]) {
				fmin = image[0][i][j];
			}
			if (fmax < image[0][i][j]) {
				fmax = image[0][i][j];
			}
		}
	}

	// image[0] �̍ŏ��K���l fmin, �ő��K���l fmax �����߂�
	// *********************************************
	//
	//    �A���̕����ɓK�؂ȋL�q�������܂��傤
	//
	// *********************************************
	printf("fmin=%d, fmax=%d\n", fmin, fmax);

	g = 0;
	int k = 255;
	int h_num[256] = {};
	for (int i = fmin; i <= fmax; i++) {
		for (int m = 0; m < width[0]; m++) {
			for (int n = 0; n < height[0]; n++) {
				if (image[0][m][n] == i) {
					if (h_num[g] <= h) {
						image[1][m][n] = g;
						h_num[g]++;
					}
					else if(g<256){
						g++;
					}
				}
				if (image[0][m][n] == fmax + fmin-i) {
					if (h_num[k] <= h) {
						image[1][m][n] = k;
						h_num[k]++;
					}
					else if(0<k){
						k--;
					}
				}
        if(k<g){
          goto LABEL1;
        }
			}
		}
	}
LABEL1:

		// �ϊ�����
		// ���摜�̍ŏ��K���l�����ő��K���l�܂ł𑖍����Ȃ����C
		// �ϊ����̉摜�̊K���l�� g=0 ���珇�� g=255 �܂Ŗ��߂Ă���
		// count �́C�eg�ł̉��f���̃J�E���^�ŁCcount=h �ɂȂ������C
		// g �̒l�ɂP���������D
		// *********************************************
		//
		//    �B���̕����ɓK�؂ȋL�q�������܂��傤
		//
		// *********************************************
		printf("fiinsh\n");


    end=clock();
		printf("�������̉摜���ۑ����܂�\n");
		save_image(1, "");  // �摜No.1 �� �t�@�C��
    printf("%.5f\n",(double)(end-start)/CLOCKS_PER_SEC);
		return 0;
	}

