#ifndef PROCESS_H
#define PROCESS_H

#include "util.h"

Img *greyscale(Img *img);

Img *gaussianFilter(Img *originalImg, unsigned short limit);

Img *sobelFilter(Img *originalImg, unsigned short limit);
// TODO

#endif
