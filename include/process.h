#ifndef PROCESS_H
#define PROCESS_H

#include "util.h"

Img *greyscale(Img *img);

Img *gaussianFilter(Img *originalImg, uchar limit);

Img *sobelFilter(Img *originalImg, uchar limit);

Img *threshold(Img *originalImg, unsigned int intensity);
// TODO

#endif
