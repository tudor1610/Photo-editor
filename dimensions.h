#ifndef DIMENSIONS_H
#define DIMENSIONS_H
#include "photo.h"

//transforms a string into a number
int char_to_int(char s[10]);

//makes a selection from the photo (given coordonates)
void case_select(image_t *photo, char buff[100]);

//selects the whole photo
void case_select_all(image_t *photo);

//swaps to given matrices
void matrix_swap(int ***a, int ***b);

//swaps to rgb_t matrices
void matrix_swap_rgb(rgb_t ***a, rgb_t ***b);

//rotates the photo 90 degrees to the left
void turn_left(image_t *photo);

//rotates the photo (given an angle)
void rotate(image_t *photo);

//crops the image
void crop(image_t *photo);

#endif