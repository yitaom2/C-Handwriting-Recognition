#include "vgg16.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BM 19778

#define PATH "testImage-PNG.bmp"

long getWidth(FILE *fp)
{
	long width;
	fseek(fp,18,SEEK_SET);
	fread(&width,1,4,fp);
	return width;
}

//获得图片的高度 ，在22-25字节
long getHeight(FILE *fp)
{
	long height;
	fseek(fp,22,SEEK_SET);
	fread(&height,1,4,fp);
	return height;
}

//获得每个像素的位数,在28-29字节
unsigned short getBit(FILE *fp)
{
	unsigned short bit;
	fseek(fp,28,SEEK_SET);
	fread(&bit,1,2,fp);
	return bit;
}

//获得数据的起始位置
unsigned int getOffSet(FILE *fp)
{
	unsigned int OffSet;
	fseek(fp,10L,SEEK_SET);
	fread(&OffSet,1,4,fp);
	return OffSet;
}

//获得图像的数据
void getData(FILE* fp,unsigned char *r,unsigned char *g,unsigned char *b)
{
    FILE* fpr;
	FILE* fpg;
	FILE* fpb;

	int i, j=0;
	int stride;
	unsigned char* pix=NULL;
	long height,width;
	height=getHeight(fp);
	width=getWidth(fp);

	fseek(fp, getOffSet(fp), SEEK_SET);	//找到位图的数据区

	stride=(24*width+31)/8;	//对齐,计算一个width有多少个8位
	stride=stride/4*4;		//取四的倍数 r,g,b,alph

	//写入数组
	pix=(unsigned char *)malloc(stride);
	for(j=0;j<height;j++)
	{
	   fread(pix, 1, stride, fp);
	   for(i=0;i<width;i++)
		{
			*(r+(height-1-j)+i)=pix[i*3+2];
			*(g+(height-1-j)+i)=pix[i*3+1];
			*(b+(height-1-j)+i)=pix[i*3];
		}
	}

	//写入文件
	fpr=fopen("d:\\bmpr.txt","w+");
	fpg=fopen("d:\\bmpg.txt","w+");
	fpb=fopen("d:\\bmpb.txt","w+");

	for(i =0; i < height; i++)
     {
		for(j = 0; j < width-1; j++)
		{
		fprintf(fpr,"%4d",*(r+i+j));
		fprintf(fpg,"%4d",*(g+i+j));
		fprintf(fpb,"%4d",*(b+i+j));
		}
		fprintf(fpr,"%4d",*(r+i+j));
		fprintf(fpg,"%4d",*(g+i+j));
		fprintf(fpb,"%4d",*(b+i+j));
 	}

	fclose(fpr);
	fclose(fpg);
	fclose(fpb);

}


int main()
{
	long width,height;
	FILE *fp=fopen(PATH,"r");
	unsigned char *r,*g,*b;
	int i,j;
	r=(unsigned char *)malloc(4000);
	b=(unsigned char *)malloc(4000);
	g=(unsigned char *)malloc(4000);

	if(IsBitMap(fp))
		printf("该文件是位图!\n");
	else
		{
			printf("该文件不是位图!\n");
			fclose(fp);
			return 0;
		}

	printf("width=%ld\nheight=%ld\n",getWidth(fp),getHeight(fp));

	printf("该图像是%d位图\n",getBit(fp));

	printf("OffSet=%d\n",getOffSet(fp));

	getData(fp,r,g,b);

	return 1;
}

void test_CONV() {
  int LayDim[3] = {2, 6, 6};
  // int mask[3][3][3] = {{{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}, {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}};
  int maskDim[3] = {3, 3, 3};
  int Image1 = 2;
  int Image2 = 6;
  int Image3 = 6;
  int Mask1 = 3;
  int Mask2 = 3;
  int Mask3 = 3;
  double *** testNImage = calloc(Image1, sizeof(double**));
  for (int i = 0; i < Image1; i++) {
    *(testNImage + i) = calloc(Image2, sizeof(double*));
    for (int j = 0; j < Image2; j++) {
      *(*(testNImage + i) + j) = calloc(Image3, sizeof(double));
    }
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 2; j++) {
      testNImage[j][i][0] = 0;
      testNImage[j][i][1] = 1;
      testNImage[j][i][2] = 2;
      testNImage[j][i][3] = 3;
      testNImage[j][i][4] = 4;
      testNImage[j][i][5] = 5;
    }
  }
  // testNImage[0][0][0] = 0;testNImage[0][0][1] = 1;testNImage[0][0][2] = 2;testNImage[0][0][3] = 3;testNImage[0][0][4] = 4;
  // testNImage[0][1][0] = 10;testNImage[0][1][1] = 11;testNImage[0][1][2] = 12;testNImage[0][1][3] = 13;testNImage[0][1][4] = 14;
  // testNImage[0][2][0] = 20;testNImage[0][2][1] = 21;testNImage[0][2][2] = 22;testNImage[0][2][3] = 23;testNImage[0][2][4] = 24;
  // testNImage[0][3][0] = 30;testNImage[0][3][1] = 31;testNImage[0][3][2] = 32;testNImage[0][3][3] = 33;testNImage[0][3][4] = 34;
  // testNImage[0][4][0] = 40;testNImage[0][4][1] = 41;testNImage[0][4][2] = 42;testNImage[0][4][3] = 43;testNImage[0][4][4] = 44;
  double *** mask = calloc(Mask1, sizeof(double**));
  for (int i = 0; i < Mask1; i++) {
    *(mask + i) = calloc(Mask2, sizeof(double*));
    for (int j = 0; j < Mask2; j++) {
      *(*(mask + i) + j) = calloc(Mask3, sizeof(double));
    }
  }
  mask[0][0][0] = 1;mask[0][0][1] = 0;mask[0][0][2] = 0;mask[0][1][0] = 1;mask[0][1][1] = 0;mask[0][1][2] = 0;mask[0][2][0] = 1;mask[0][2][1] = 0;mask[0][0][2] = 0;
  mask[1][0][0] = 1;mask[1][0][1] = 0;mask[1][0][2] = 0;mask[1][1][0] = 0;mask[1][1][1] = 0;mask[1][1][2] = 0;mask[1][2][0] = 0;mask[1][2][1] = 0;mask[1][0][2] = 0;
  mask[2][0][0] = 0;mask[2][0][1] = 0;mask[2][0][2] = 0;mask[2][1][0] = 0;mask[2][1][1] = 1;mask[2][1][2] = 0;mask[2][2][0] = 0;mask[2][2][1] = 0;mask[2][0][2] = 0;
  printf("IMAGE\n");
  for (int i = 0; i < Image1; i++) {
    printf("Image Layer: %d\n", i);
    for (int j = 0; j < Image2; j++) {
      for (int k = 0; k < Image3; k++) {
        printf("%f ", testNImage[i][j][k]);
      }
      printf("\n");
    }
    printf("-----------------------\n");
  }
  printf("=================================\n");
  printf("MASK\n");
  for (int i = 0; i < Mask1; i++) {
    printf("Mask Layer: %d\n", i);
    for (int j = 0; j < Mask2; j++) {
      for (int k = 0; k < Mask3; k++) {
        printf("%f ", mask[i][j][k]);
      }
      printf("\n");
    }
    printf("-----------------------\n");
  }
  printf("=================================\n");
  double *** result = convolution2D(testNImage, mask, LayDim, maskDim);
  printf("RESULT-COV2D\n");
  for (int i = 0; i < Mask1; i++) {
    printf("Result Layer%d\n", i);
    for (int j = 0; j < Image2 - Mask2 + 1; j++) {
      for (int k = 0; k < Image3 - Mask3 + 1; k++) {
        printf("%f; ", result[i][j][k]);
      }
      printf("\n");
    }
    printf("-----------------------\n");
  }
  printf("=================================\n");
}

void test_POOL() {
  int Image1 = 2;
  int Image2 = 6;
  int Image3 = 6;
  double *** testNImage = calloc(Image1, sizeof(double**));
  for (int i = 0; i < Image1; i++) {
    *(testNImage + i) = calloc(Image2, sizeof(double*));
    for (int j = 0; j < Image2; j++) {
      *(*(testNImage + i) + j) = calloc(Image3, sizeof(double));
    }
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 2; j++) {
      testNImage[j][i][0] = 0;
      testNImage[j][i][1] = 1;
      testNImage[j][i][2] = 2;
      testNImage[j][i][3] = 3;
      testNImage[j][i][4] = 4;
      testNImage[j][i][5] = 5;
    }
  }

  int LayDimPool[3] = {2, 6, 6};
  int maskDimPool[2] = {2, 2};
  int stridesPool[2] = {2, 2};
  double *** resultPool = MaxPooling2D(testNImage, stridesPool, LayDimPool, maskDimPool);
  printf("RESULT-POOL\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        printf("%f; ", resultPool[i][j][k]);
      }
      printf("\n");
    }
    printf("-----------------------\n");
  }
  printf("=================================\n");
}

void test_DENSE() {
  double testNImage[4] = {1.1, 2.4, 3.5, 7.6};
  double ** weight = calloc(4, sizeof(double *));
  for (int i = 0; i < 4; i++) {
    weight[i] = calloc(3, sizeof(double));
  }
  weight[0][0] = 0.1; weight[0][1] = 0.1; weight[0][2] = 0.1;
  weight[1][0] = 0.3; weight[1][1] = 0.5; weight[1][2] = 0.2;
  weight[2][0] = 1.1; weight[2][1] = 2.1; weight[2][2] = 0.1;
  weight[3][0] = 1; weight[3][1] = 1; weight[3][2] = 2;

  double * resultDense = Dense(testNImage, weight, 4, 3);
  printf("RESULT-DENSE\n");
  for (int i = 0; i < 3; i++) {
    printf("%f; ", resultDense[i]);
  }
  printf("\n");
  printf("=================================\n");
}

void test_FLATTEN() {
  int Image1 = 2;
  int Image2 = 3;
  int Image3 = 3;
  double *** testNImage = calloc(Image1, sizeof(double**));
  for (int i = 0; i < Image1; i++) {
    *(testNImage + i) = calloc(Image2, sizeof(double*));
    for (int j = 0; j < Image2; j++) {
      *(*(testNImage + i) + j) = calloc(Image3, sizeof(double));
    }
  }
  testNImage[0][0][0] = 0; testNImage[0][0][1] = 1; testNImage[0][0][2] = 2;
  testNImage[0][1][0] = 3; testNImage[0][1][1] = 4; testNImage[0][1][2] = 5;
  testNImage[0][2][0] = 6; testNImage[0][2][1] = 7; testNImage[0][2][2] = 8;
  testNImage[1][0][0] = 9; testNImage[1][0][1] = 10; testNImage[1][0][2] = 11;
  testNImage[1][1][0] = 12; testNImage[1][1][1] = 13; testNImage[1][1][2] = 14;
  testNImage[1][2][0] = 15; testNImage[1][2][1] = 16; testNImage[1][2][2] = 17;

  int LayDim[3] = {2, 3, 3};
  double * resultFlatten = Flatten(testNImage, LayDim);
  printf("RESULT-FLATTEN\n");
  for (int i = 0; i < 18; i++) {
    printf("%f; ", resultFlatten[i]);
  }
  printf("\n");
  printf("=================================\n");
}

void test_DROPOUT() {
  double testNImage[4] = {1.1, 2.4, 3.5, 7.6};
  double ** weight = calloc(4, sizeof(double *));
  for (int i = 0; i < 4; i++) {
    weight[i] = calloc(3, sizeof(double));
  }
  weight[0][0] = 0.1; weight[0][1] = 0.2; weight[0][2] = 0.3;
  weight[1][0] = 0.4; weight[1][1] = 0.5; weight[1][2] = 0.6;
  weight[2][0] = 1.1; weight[2][1] = 1.2; weight[2][2] = 0.7;
  weight[3][0] = 0.8; weight[3][1] = 0.9; weight[3][2] = 1.0;

  double * resultDropout = Dropout(testNImage, &weight, 4, 0.5);
  printf("RESULT-DROPOUT\n");
  for (int i = 0; i < 2; i++) {
    printf("%f; ", resultDropout[i]);
  }
  printf("%f: ", weight[0][0]);
  printf("\n");
  printf("=================================\n");
}

void test_ZEROPADDING() {
  int Image1 = 2;
  int Image2 = 6;
  int Image3 = 6;
  double *** testNImage = calloc(Image1, sizeof(double**));
  for (int i = 0; i < Image1; i++) {
    *(testNImage + i) = calloc(Image2, sizeof(double*));
    for (int j = 0; j < Image2; j++) {
      *(*(testNImage + i) + j) = calloc(Image3, sizeof(double));
    }
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 2; j++) {
      testNImage[j][i][0] = 6;
      testNImage[j][i][1] = 1;
      testNImage[j][i][2] = 2;
      testNImage[j][i][3] = 3;
      testNImage[j][i][4] = 4;
      testNImage[j][i][5] = 5;
    }
  }

  int LayDim[3] = {2, 6, 6};
  int ZeroNum[2] = {2, 2};
  double *** resultZeroPadding = ZeroPadding2D(testNImage, LayDim, ZeroNum);
  printf("RESULT-ZEROPADDING\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        printf("%f; ", resultZeroPadding[i][j][k]);
      }
      printf("\n");
    }
    printf("-----------------------\n");
  }
  printf("=================================\n");
}
