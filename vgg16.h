#pragma once

/**
  activation="relu"
 **/
double*** convolution2D(double*** Layers, double**** mask, int* LayDim, int* maskDim, double * bias, int stride, char* ZeroPadding);

/**
 **/
double*** MaxPooling2D(double *** Layers, int* LayDim, int* maskDim, int stride, char* ZeroPadding);

/**
 **/
double * Dense(double* Layer, double** Weight, double * bias, int WeiDimS, int WeiDimE, char * activation);

/**
 **/
double * Flatten(double *** Layer, int* LayDim);

/**
 **/
double * Dropout(double * Image, double *** Weight, int ImageDim, double dropP);

double *** LoadImageAResize(char * filename, int * size);

/*this function for now only works for bmp files.*/
double *** getData(char * path, int ** size);

/*this function resize the original image WITHOUT changing number of layers*/
double *** resize(double *** Layers, int * startSize, int * endSize);
