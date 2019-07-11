#include "vgg16.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

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
  double *** result = convolution2D(testNImage, mask, LayDim, maskDim, 2, "SAME");
  printf("RESULT-COV2D\n");
  for (int i = 0; i < Mask1; i++) {
    printf("Result Layer%d\n", i);
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
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
  double *** resultPool = MaxPooling2D(testNImage, LayDimPool, maskDimPool, 3, "SAME");
  printf("RESULT-POOL\n");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
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

  double * resultDense = Dense(testNImage, weight, 4, 3, "relu");
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

double *** ConvWeight(char * layerName, int * layerDim) {
  double *** weight = calloc(layerDim[0], sizeof(double**));
  for (int i = 0; i < layerDim[0]; i++) {
    *(weight + i) = calloc(layerDim[1], sizeof(double*));

    char filepath[55];
    sprintf(filepath, "handWritRec/layerData/%s/%d", layerName, i);
    FILE * weightfile = fopen(filepath, "r");

    for (int j = 0; j < layerDim[1]; j++) {
      *(*(weight + i) + j) = calloc(layerDim[2], sizeof(double));

      char * buffer = calloc(1000, 1);buffer[999] = '\0';
      size_t linelength = 0;
      ssize_t read = getline(&buffer, &linelength, weightfile);

      char * moving = buffer;
      for (int k = 0; k < layerDim[2]; k++) {
        sscanf(moving, "%lf", &weight[i][j][k]);
        moving = strstr(moving, " ") + 1;
      }
      free(buffer);
    }
    fclose(weightfile);
  }
  return weight;
}

double ** DenseWeight(char * layerName, int * layerDim) {
  char filepath[55];
  sprintf(filepath, "handWritRec/layerData/%s/weight", layerName);
  FILE * weightfile = fopen(filepath, "r");

  double ** weight = calloc(layerDim[0], sizeof(double*));
  for (int i = 0; i < layerDim[0]; i++) {
    *(weight + i) = calloc(layerDim[1], sizeof(double*));
    char * buffer = calloc(1000, 1);buffer[999] = '\0';
    size_t linelength = 0;
    ssize_t read = getline(&buffer, &linelength, weightfile);

    char * moving = buffer;
    for (int j = 0; j < layerDim[1]; j++) {
      sscanf(moving, "%lf", &weight[i][j]);
      moving = strstr(moving, " ") + 1;
    }
    free(buffer);
  }
  fclose(weightfile);
  return weight;
}

double *** createImage(int imagenum) {
  char filepath[50];
  sprintf(filepath, "handWritRec/image/x_test/%d", imagenum);

  FILE * imagefile = fopen(filepath, "r");
  char buffer[26]; buffer[25] = '\0';

  double *** image = calloc(1, sizeof(double**));
  *image = calloc(28, sizeof(double*));
  for (int i = 0; i < 28; i++) {
    *(*image + i) = calloc(28, sizeof(double));
    for (int j = 0; j < 28; j++) {
      int num = fread(buffer, 25, 1, imagefile);
      double data = atof(buffer);
      image[0][i][j] = data;
    }
  }

  fclose(imagefile);
  return image;
}

void image_recognition(int imagenum) {
  double *** image = createImage(imagenum);

  int weightDim1[3] = {16, 3, 3}; int layerDim1[3] = {1, 28, 28};
  int weightDim2[2] = {12544, 20}; int layerDim2[3] = {16, 28, 28};
  int weightDim3[2] = {20, 10}; int layerDim3[3] = {1, 28, 28};
  double *** weight1 = ConvWeight("Conv1", weightDim1);
  double ** weight2 = DenseWeight("Dense1", weightDim2);
  double ** weight3 = DenseWeight("Dense2", weightDim3);

  double *** layerConv1 = convolution2D(image, weight1, layerDim1, weightDim1, 1, "SAME");
  double * layerFlatten = Flatten(layerConv1, layerDim2);
  double * layerDense1 = Dense(layerFlatten, weight2, 12544, 20, "relu");
  double * layerDense2 = Dense(layerDense1, weight3, 20, 10, "softmax");

  printf("HERE ARE THE RESULT:\n");
  for (int i = 0; i < 10; i++) {
    printf("%f ", layerDense2[i]);
  }
  printf("\n");
}

int main(int argc, char * argv[]) {
  if (argc <= 1) {
    printf("enter in the format: ./combine.o [number in range[0, 10000)]\n");
    exit(0);
  }
  int imagenum = atoi(argv[1]);
  if (imagenum == 0) {
    printf("currently showing the result of image 0\n");
    printf("you either entered 0 as the image number or entered a none number variable\n");
    printf("enter in the format: ./combine.o [number in range[0, 10000)]\n");
    printf("----------------------------------------------------------\n");
  }
  image_recognition(imagenum);
  return 0;
}
