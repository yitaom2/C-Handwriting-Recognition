#include "vgg16.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BM 19778

#define PATH "testImage-PNG.bmp"

// int getWidth(FILE *fp)
// {
// 	int width;
// 	fseek(fp,18,SEEK_SET);
// 	fread(&width,1,4,fp);
// 	fseek(fp, 0, SEEK_SET);
// 	return width;
// }
//
// //获得图片的高度 ，在22-25字节
// int getHeight(FILE *fp)
// {
// 	int height;
// 	fseek(fp,22,SEEK_SET);
// 	fread(&height,1,4,fp);
// 	fseek(fp, 0, SEEK_SET);
// 	return height;
// }
//
// //获得每个像素的位数,在28-29字节
// unsigned short getBit(FILE *fp)
// {
// 	unsigned short bit;
// 	fseek(fp,28,SEEK_SET);
// 	fread(&bit,1,2,fp);
// 	return bit;
// }
//
// //获得数据的起始位置
// unsigned int getOffSet(FILE *fp)
// {
// 	unsigned int OffSet;
// 	fseek(fp,10L,SEEK_SET);
// 	fread(&OffSet,1,4,fp);
// 	fseek(fp, 0, SEEK_SET);
// 	return OffSet;
// }
//
// //获得图像的数据
// double *** getData(FILE* fp)
// {
//   //   FILE* fpr;
// 	// FILE* fpg;
// 	// FILE* fpb;
//
// 	int i, j=0;
// 	unsigned char* pix=NULL;
// 	int height = getHeight(fp);
// 	int width = getWidth(fp);
// 	printf("%d, %d\n", height, width);
//
// 	fseek(fp, getOffSet(fp), SEEK_SET);	//找到位图的数据区
//
// 	// stride=(24*width+31)/8;
// 	// stride=stride/4*4;
//
// 	// 写入数组
// 	int stride = width * 4;
//
// 	pix=(unsigned char *)malloc(stride);
// 	double *** ret = calloc(3, sizeof(double **));
// 	*(ret) = calloc(height, sizeof(double*));
// 	*(ret + 1) = calloc(height, sizeof(double*));
// 	*(ret + 2) = calloc(height, sizeof(double*));
// 	// double ** red = calloc(height, sizeof(double*));
// 	// double ** blue = calloc(height, sizeof(double*));
// 	// double ** green = calloc(height, sizeof(double*));
// 	for (int i = 0; i < height; i++) {
// 		*(*ret + (height - 1 - i)) = calloc(width, sizeof(double));
// 		*(*(ret + 1) + (height - 1 - i)) = calloc(width, sizeof(double));
// 		*(*(ret + 2) + (height - 1 - i)) = calloc(width, sizeof(double));
//
// 		fread(pix, 1, stride, fp);
// 		for (int j = 0; j < width; j++) {
// 			ret[0][height - 1 - i][width - 1 - j] = pix[j * 3 + 2];
// 			ret[1][height - 1 - i][width - 1 - j] = pix[j * 3 + 1];
// 			ret[2][height - 1 - i][width - 1 - j] = pix[j * 3];
// 		}
// 	}
//
// 	for (int i = 0; i < height; i++) {
// 		for (int j = 0; j < width; j++) {
// 			printf("(%f, %f, %f) ", ret[0][i][j], ret[1][i][j], ret[2][i][j]);
// 		}
// 	}
//
// 	return ret;
//
// 	//写入文件
// 	// fpr=fopen("d:\\bmpr.txt","w+");
// 	// fpg=fopen("d:\\bmpg.txt","w+");
// 	// fpb=fopen("d:\\bmpb.txt","w+");
// 	//
// 	// for(i =0; i < height; i++)
//   //    {
// 	// 	for(j = 0; j < width-1; j++)
// 	// 	{
// 	// 	fprintf(fpr,"%4d",*(r+i * width +j));
// 	// 	fprintf(fpr,"(%d, %d)", i, j);
// 	// 	fprintf(fpg,"%4d",*(g+i * width+j));
// 	// 	fprintf(fpb,"%4d",*(b+i * width+j));
// 	// 	}
// 	// 	fprintf(fpr,"%4d",*(r+i * width+j));
// 	// 	fprintf(fpg,"%4d",*(g+i * width+j));
// 	// 	fprintf(fpb,"%4d",*(b+i+j));
//  	// }
//
// 	// fclose(fpr);
// 	// fclose(fpg);
// 	// fclose(fpb);
//
// }
//
//
// int main()
// {
// 	long width,height;
// 	FILE *fp=fopen(PATH,"r");
// 	unsigned char *r,*g,*b;
// 	int i,j;
// 	r=(unsigned char *)malloc(4000);
// 	b=(unsigned char *)malloc(4000);
// 	g=(unsigned char *)malloc(4000);
//
// 	getData(fp);
//
// 	return 0;
// }

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

int main() {
	double *** inuse = getData("testImage-PNG.bmp");
	int startSize[2] = {422, 750};
	int endSize[2] = {200, 200};
	inuse = resize(inuse, startSize, endSize);
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			printf("%f ", inuse[0][i][j]);
		}
		printf("\n");
	}
	return 0;
}
