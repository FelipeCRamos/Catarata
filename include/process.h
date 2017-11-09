#ifndef PROCESS_H
#define PROCESS_H

#include "util.h"

Img *greyscale(Img *img);

Img *gaussianFilter(Img *originalImg);

Img *sobelFilter(Img *originalImg);
// TODO

#endif
