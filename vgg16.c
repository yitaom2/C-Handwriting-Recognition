#include "vgg16.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double*** convolution2D(double*** Layers, double*** mask, int* LayDim, int* maskDim, int stride, char* ZeroPadding) {
  //numbers of masks, horizontal lines in a mask, vertical lines in a mask
  int maskDimNum = *maskDim;
  int maskDimH = *(maskDim + 1);
  int maskDimV= *(maskDim + 2);
  //dimension of layers, horizontal lines in a layer, vertical lines in a layer
  int inputNum = *LayDim;
  int inputH = *(LayDim + 1);
  int inputV = *(LayDim + 2);

  int outputH;
  int outputV;
  int zeroH;
  int zeroV;
  if (strncmp(ZeroPadding, "SAME", 4) == 0) {
    outputH = floor((inputH - 1) / stride + 1); if (outputH < 0) {outputH = 0;}
    outputV = floor((inputV - 1) / stride + 1); if (outputV < 0) {outputV = 0;}
    zeroH = stride * (outputH - 1) + maskDimH - inputH; if (zeroH < 0) {zeroH = 0;}
    zeroV = stride * (outputV - 1) + maskDimV - inputV; if (zeroV < 0) {zeroV = 0;}
  } else {
    outputH = floor((inputH - maskDimH) / stride + 1); if (outputH < 0) {outputH = 0;}
    outputV = floor((inputV - maskDimV) / stride + 1); if (outputV < 0) {outputV = 0;}
    zeroH = stride * (outputH - 1) + maskDimH - inputH; if (zeroH > 0) {zeroH = 0;}
    zeroV = stride * (outputV - 1) + maskDimV - inputV; if (zeroV > 0) {zeroV = 0;}
  }
  printf("%d %d %d %d\n", outputH, outputV, zeroH, zeroV);
  double *** ret = calloc(maskDimNum, sizeof(double**));
  for (int masknum = 0; masknum < maskDimNum; masknum++) {
    //for each mask a different operation
    *(ret + masknum) = calloc(outputH, sizeof(double*));
    for (int createintarray = 0; createintarray < outputH; createintarray++) {
      *(*(ret + masknum) + createintarray) = calloc(outputV, sizeof(double));
    }
    for (int layernum = 0; layernum < inputNum; layernum++) {
      for (int outputh = 0; outputh < outputH; outputh++) {
        for (int outputv = 0; outputv < outputV; outputv++) {
          int starth = outputh * stride;
          int startv = outputv * stride;
          if (zeroH > 0) starth -= floor(zeroH / 2);
          if (zeroV > 0) startv -= floor(zeroV / 2);
          // printf("(%d, %d)\n", starth, startv);
          for (int i = 0; i < maskDimH; i++) {
            for (int j = 0; j < maskDimV; j++) {
              if (starth + i < 0 || startv + j < 0 || starth + i >= inputH || startv + j >= inputV) {
                continue;
              }
              // printf("(%d, %d) += mask(%d, %d) * origin(%d , %d)\n", outputh, outputv, i, j, starth + i, startv + j);
              ret[masknum][outputh][outputv] += mask[masknum][i][j] * Layers[layernum][starth + i][startv + j];
            }
          }
        }
      }
    }
  }
  return ret;
}

double *** MaxPooling2D(double *** Layers, int* LayDim, int* maskDim, int stride, char* ZeroPadding) {
  int maskDimH = *maskDim;
  int maskDimV= *(maskDim + 1);
  //dimension of layers, horizontal lines in a layer, vertical lines in a layer
  int inputNum = *LayDim;
  int inputH = *(LayDim + 1);
  int inputV = *(LayDim + 2);

  int outputH;
  int outputV;
  int zeroH;
  int zeroV;
  if (strncmp(ZeroPadding, "SAME", 4) == 0) {
    outputH = floor((inputH - 1) / stride + 1); if (outputH < 0) {outputH = 0;}
    outputV = floor((inputV - 1) / stride + 1); if (outputV < 0) {outputV = 0;}
    zeroH = stride * (outputH - 1) + maskDimH - inputH; if (zeroH < 0) {zeroH = 0;}
    zeroV = stride * (outputV - 1) + maskDimV - inputV; if (zeroV < 0) {zeroV = 0;}
  } else {
    outputH = floor((inputH - maskDimH) / stride + 1); if (outputH < 0) {outputH = 0;}
    outputV = floor((inputV - maskDimV) / stride + 1); if (outputV < 0) {outputV = 0;}
    zeroH = stride * (outputH - 1) + maskDimH - inputH; if (zeroH > 0) {zeroH = 0;}
    zeroV = stride * (outputV - 1) + maskDimV - inputV; if (zeroV > 0) {zeroV = 0;}
  }
  printf("%d %d %d %d\n", outputH, outputV, zeroH, zeroV);

  double *** ret = calloc(inputNum, sizeof(double**));
  for (int laynum = 0; laynum < inputNum; laynum++) {
    //for each mask a different operation
    *(ret + laynum) = calloc(outputH, sizeof(double*));
    for (int createintarray = 0; createintarray < outputH; createintarray++) {
      *(*(ret + laynum) + createintarray) = calloc(outputV, sizeof(double));
    }
    double ** retToFillLayer = *(ret + laynum);
    for (int outputh = 0; outputh < outputH; outputh++) {
      for (int outputv = 0; outputv < outputV; outputv++) {
        int starth = outputh * stride;
        int startv = outputv * stride;
        if (zeroH > 0) starth -= floor(zeroH / 2);
        if (zeroV > 0) startv -= floor(zeroV / 2);
        double max = -1000;
        for (int i = 0; i < maskDimH; i++) {
          for (int j = 0; j < maskDimV; j++) {
            if (starth + i < 0 || startv + j < 0 || starth + i >= inputH || startv + j >= inputV) {
              continue;
            }
            double temp = Layers[laynum][starth + i][startv + j];
            if (temp > max) {
              max = temp;
            }
          }
        }
        retToFillLayer[outputh][outputv] = max;
      }
    }
    // for (int layerh = 0; layerh < inputH / stride; layerh++) {
    //   for (int layerv = 0; layerv < inputV / maskDimV; layerv++) {
    //     double max = -1000;
    //     for (int maskh = 0; maskh < maskDimH; maskh++) {
    //       for (int maskv = 0; maskv < maskDimV; maskv++) {
    //         double temp = Layers[laynum][layerh * stride + maskh][layerv * stride + maskv];
    //         if (temp > max) {
    //           max = temp;
    //         }
    //       }
    //     }
    //     retToFillLayer[layerh][layerv] = max;
    //   }
    // }
  }
  return ret;
}

double * Dense(double* Layer, double** Weight, int WeiDimS, int WeiDimE) {
  double * ret = calloc(WeiDimE, sizeof(double));
  for (int count = 0; count < WeiDimS; count++) {
    for (int neur = 0; neur < WeiDimE; neur++) {
      ret[neur] += Weight[count][neur] * Layer[count];
    }
  }
  return ret;
}

double * Flatten(double*** Layers, int* LayDim) {
  int LayDimNum = *LayDim;
  int LayDimH = *(LayDim + 1);
  int LayDimV = *(LayDim + 2);
  double * ret = calloc(LayDimNum * LayDimH * LayDimV, sizeof(double));
  printf("%d %d %d", LayDimNum, LayDimH, LayDimV);
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

double *** getData(char * path, int ** size) {
  FILE *fp=fopen(path,"r");

  int width, height, offset;
	fseek(fp,18,SEEK_SET);
	fread(&width,1,4,fp);
  fread(&height,1,4,fp);
  fseek(fp,10L,SEEK_SET);
	fread(&offset,1,4,fp);
	fseek(fp, 0, SEEK_SET);

	unsigned char* pix=NULL;
	fseek(fp,offset, SEEK_SET);
	int stride = width * 4;

	pix=(unsigned char *)malloc(stride);
	double *** ret = calloc(3, sizeof(double **));
	*(ret) = calloc(height, sizeof(double*));
	*(ret + 1) = calloc(height, sizeof(double*));
	*(ret + 2) = calloc(height, sizeof(double*));
	for (int i = 0; i < height; i++) {
		*(*ret + (height - 1 - i)) = calloc(width, sizeof(double));
		*(*(ret + 1) + (height - 1 - i)) = calloc(width, sizeof(double));
		*(*(ret + 2) + (height - 1 - i)) = calloc(width, sizeof(double));
		fread(pix, 1, stride, fp);
		for (int j = 0; j < width; j++) {
			ret[0][height - 1 - i][width - 1 - j] = pix[j * 3 + 2];
			ret[1][height - 1 - i][width - 1 - j] = pix[j * 3 + 1];
			ret[2][height - 1 - i][width - 1 - j] = pix[j * 3];
		}
	}
  // for (int i = 0; i < height; i++) {
  //   printf("%d\n", i);
	// 	for (int j = 0; j < width; j++) {
  //     printf("%f", ret[0][i][j]);
	// 	}
	// }

  *(*(size)) = height;
  *(*(size) + 1) = width;
	return ret;
}

double *** resize(double *** Layers, int * startSize, int * endSize) {
  int sH = *startSize;
  int sV = *(startSize + 1);
  int eH = *endSize;
  int eV = *(endSize + 1);

  double *** ret = calloc(3, sizeof(double **));
  for (int layer = 0; layer < 3; layer++) {
    *(ret + layer) = calloc(eH, sizeof(double *));
    for (int i = 0; i < eH; i++) {
      *(*(ret + layer) + i) = calloc(eV, sizeof(double));
      for (int j = 0; j < eV; j++) {
        double reScaleH = (double)i * ((double)sH / (double)eH);
        double reScaleV = (double)j * ((double)sV / (double)eV);

        int lowerH = reScaleH;
        int higherH = (reScaleH + 1);
        int lowerV = reScaleV;
        int higherV = (reScaleV + 1);
        // if (i == 1 && j == 1) {printf("(%f, %f) -> %d, %d, %d, %d\n", reScaleH, reScaleV, lowerH, higherH, lowerV, higherV);}
        /* following the function as follows:
        f(x,y)=f(0,0)(1-x)(1-y)+f(1,0)x(1-y)+f(0,1)(1-x)y+f(1,1)xy
        */
        /*1 - x*/
        double _x = (double)higherH - reScaleH;
        double x = reScaleH - (double)lowerH;
        double _y = (double)higherV - reScaleV;
        double y = reScaleV - (double)lowerV;
        ret[layer][i][j] = Layers[layer][lowerH][lowerV] * _x * _y + Layers[layer][higherH][lowerV] * x * _y
         + Layers[layer][lowerH][higherV] * _x * y + Layers[layer][higherH][higherV] * x * y;
      }
    }
  }
  return ret;
}
