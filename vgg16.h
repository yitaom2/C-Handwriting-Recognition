#pragma once

/**
  activation="relu"
 **/
double*** convolution2D(double*** Layers, double*** mask, int* LayDim, int* maskDim);

/**
 **/
double*** MaxPooling2D(double *** Layers, int* strides, int* LayDim, int* maskDim);

/**
 **/
double * Dense(double* Layer, double** Weight, int WeiDimS, int WeiDimE);

/**
 **/
double * Flatten(double *** Layer, int* LayDim);

/**
 **/
double * Dropout(double * Image, double *** Weight, int ImageDim, double dropP);

double *** ZeroPadding2D(double *** Layers, int* LayDim, int * ZeroNum);

double *** LoadImageAResize(char * filename, int * size);
