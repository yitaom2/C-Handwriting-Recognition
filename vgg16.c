#include "vgg16.h"
#include <stdlib.h>
#include <stdio.h>

double*** convolution2D(double*** Layers, double*** mask, int* LayDim, int* maskDim) {
  //numbers of masks, horizontal lines in a mask, vertical lines in a mask
  int maskDimNum = *maskDim;
  int maskDimH = *(maskDim + 1);
  int maskDimV= *(maskDim + 2);
  //dimension of layers, horizontal lines in a layer, vertical lines in a layer
  int LayDimNum = *LayDim;
  int LayDimH = *(LayDim + 1);
  int LayDimV = *(LayDim + 2);
  double *** ret = calloc(maskDimNum, sizeof(double**));
  for (int masknum = 0; masknum < maskDimNum; masknum++) {
    //for each mask a different operation
    *(ret + masknum) = calloc(LayDimH - maskDimH + 1, sizeof(double*));
    for (int createintarray = 0; createintarray < LayDimH - maskDimH + 1; createintarray++) {
      *(*(ret + masknum) + createintarray) = calloc(LayDimV - maskDimV + 1, sizeof(double));
    }
    for (int layernum = 0; layernum < LayDimNum; layernum++) {
      //use layernum in the outer layer to avoid jumping arround memories
      double ** temporiLayer = *(Layers + layernum);
      for (int layerh = 0; layerh < LayDimH - maskDimH + 1; layerh++) {
        for (int layerv = 0; layerv < LayDimV- maskDimV + 1; layerv++) {
          double ** masktemp = *(mask + masknum);
          for (int maskh = 0; maskh < maskDimH; maskh++) {
            for (int maskv = 0; maskv < maskDimV; maskv++) {
              // printf("%f\n", *(*(*(ret + masknum) + layerh) + layerv));
              // printf("ret: L%d (H%d, V%d): + %f * %f; mask: (%d, %d), layer: (%d, %d, %d)\n", masknum, layerh, layerv, (*(*(masktemp + maskh) + maskv)), *(*(temporiLayer + layerh + maskh) + layerv + maskv), maskh, maskv, layernum, layerh + maskh, layerv + maskv);
              *(*(*(ret + masknum) + layerh) + layerv) += (*(*(masktemp + maskh) + maskv)) * (*(*(temporiLayer + layerh + maskh) + layerv + maskv));
            }
          }

        }
      }
    }
  }
  return ret;
}

double *** MaxPooling2D(double *** Layers, int* strides, int* LayDim, int* maskDim) {
  int maskDimH = *maskDim;
  int maskDimV= *(maskDim + 1);
  //dimension of layers, horizontal lines in a layer, vertical lines in a layer
  int LayDimNum = *LayDim;
  int LayDimH = *(LayDim + 1);
  int LayDimV = *(LayDim + 2);
  int strideH = *strides;
  int strideV = *(strides + 1);

  double *** ret = calloc(LayDimNum, sizeof(double**));
  for (int laynum = 0; laynum < LayDimNum; laynum++) {
    //for each mask a different operation
    *(ret + laynum) = calloc(LayDimH / strideH, sizeof(double*));
    for (int createintarray = 0; createintarray < LayDimH / maskDimH; createintarray++) {
      *(*(ret + laynum) + createintarray) = calloc(LayDimV / maskDimV, sizeof(double));
    }
    double ** retToFillLayer = *(ret + laynum);
    for (int layerh = 0; layerh < LayDimH / strideH; layerh++) {
      for (int layerv = 0; layerv < LayDimV / maskDimV; layerv++) {
        double max = -1000;
        for (int maskh = 0; maskh < maskDimH; maskh++) {
          for (int maskv = 0; maskv < maskDimV; maskv++) {
            double temp = Layers[laynum][layerh * strideH + maskh][layerv * strideV + maskv];
            if (temp > max) {
              max = temp;
            }
          }
        }
        retToFillLayer[layerh][layerv] = max;
      }
    }
  }
  return ret;
}

double * Dense(double* Layer, double** Weight, int WeiDimS, int WeiDimE) {
  double * ret = calloc(WeiDimE, sizeof(double));
  for (int count = 0; count < WeiDimS; count++) {
    for (int neur = 0; neur < WeiDimE; neur++) {
      printf("%d: + %f * %f\n", neur, Weight[count][neur], Layer[count]);
      ret[neur] += Weight[count][neur] * Layer[count];
    }
  }
  return ret;
}

double * Flatten(double*** Layers, int* LayDim) {
  int LayDimNum = *LayDim;
  int LayDimH = *(LayDim + 1);
  int LayDimV = *(LayDim + 2);
  double * ret = calloc(1, LayDimNum * LayDimH * LayDimV * sizeof(double));
  for (int i = 0; i < LayDimNum; i++) {
    for (int j = 0; j < LayDimH; j++) {
      for (int k = 0; k < LayDimV; k++) {
        ret[i * LayDimH * LayDimV + j * LayDimV + k] = Layers[i][j][k];
      }
    }
  }
  return ret;
}

double * Dropout(double * Image, double *** Weight, int ImageDim, double dropP) {
  int numToKeep = (1 - dropP) * ImageDim;
  int * filter = calloc(ImageDim, sizeof(int));
  int count = 0;
  while (count < numToKeep) {
    int temp = random() % ImageDim;
    printf("%d\n", temp);
    if (filter[temp] != 1) {
      filter[temp] = 1;
      count++;
    }
  }
  double * ret = calloc(numToKeep, sizeof(double));
  double ** weightR = calloc(numToKeep, sizeof(double *));
  count = 0;
  for (int i = 0; i < ImageDim; i++) {
    if (filter[i] == 1) {
      ret[count] = Image[i];
      *(weightR + count) = (*Weight)[i];
      count++;
    } else {
      free((*Weight)[i]);
    }
  }
  free((*Weight));
  (*Weight) = weightR;
  return ret;
}

double *** ZeroPadding2D(double *** Layers, int* LayDim, int * ZeroNum) {
  //dimension of layers, horizontal lines in a layer, vertical lines in a layer
  int LayDimNum = *LayDim;
  int LayDimH = *(LayDim + 1);
  int LayDimV = *(LayDim + 2);
  int ZeroNumH = *ZeroNum;
  int ZeroNumV= *(ZeroNum + 1);

  double *** ret = calloc(LayDimNum, sizeof(double**));
  for (int laynum = 0; laynum < LayDimNum; laynum++) {
    //for each mask a different operation
    *(ret + laynum) = calloc(LayDimH + 2 * ZeroNumH, sizeof(double*));
    for (int i = 0; i < LayDimH + 2 * ZeroNumH; i++) {
      *(*(ret + laynum) + i) = calloc(LayDimV + 2 * ZeroNumV, sizeof(double));
      if (i >= ZeroNumH && i < LayDimH + ZeroNumH) {
        for (int j = ZeroNumH; j < LayDimH + ZeroNumH; j++) {
          *(*(*(ret + laynum) + i) + j) = Layers[laynum][i - ZeroNumH][j - ZeroNumH];
        }
      }
    }
  }
  return ret;
}

double *** LoadImageAResize(char * filename, int * size) {
  FILE *fp =fopen("testImage-PNG.bmp","r");
  int test = 1;
  while(test == 1) {
    char store;
    test = fread(&store, 1, 1, fp);
    printf("%c", store);
  }
  fclose(fp);
}
