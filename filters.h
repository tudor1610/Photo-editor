#ifndef FILTERS_H
#define FILTERS_H
#include <stdio.h>
#include "photo.h"

//makes the histogram
void histogram(image_t *photo);

//equalizes a black and white image
void equalize(image_t *photo);

//detects the edges of the photo
void edge(image_t *photo);

//sharpens photo
void sharpen(image_t *photo);

//applies blur
void blur(image_t *photo);

//applies gaussian blur
void gaussian_blur(image_t *photo);

//processes the request; applies one of the for filters from above
void apply(image_t *photo);
#endif