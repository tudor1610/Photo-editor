#ifndef PHOTO_H
#define PHOTO_H
#include <stdio.h>

typedef struct {
	int r, g, b;
} rgb_t;

typedef struct {
	char type[3];
	int n, m;
	int maxval;
	int **mat;
	int is_mat;
	int x1, x2, y1, y2;
	rgb_t **color;
	int is_col;
} image_t;

//allocates memory for an int type matrix
int **alloc_mat(int n, int m);

//allocates memory for a rgb_t matrix
rgb_t **alloc_col_mat(int n, int m);

//reads a matrix form an ascii file
void read_matrix_ASCII(int m, int n, int **a, FILE *in);

//reads an rgb_t matrix from an ascii file
void read_color_ASCII(int n, int m, rgb_t **a, FILE *in);

//reads an rgb_t matrix from a binary file
void read_color_BIN(int n, int m, rgb_t **a, FILE *in);

//reads an int matrix from a binary file
void read_matrix_BIN(int m, int n, int **a, FILE *in);

//skips the empty lines and the ones that start with '#'
void skip_comm(FILE *in);

//deallocates a given matrix
void destroy_mat_GREY(int n, int **mat);

//deallocates a given rgb_t matrix
void destroy_mat_COL(int n, rgb_t **mat);

//allocates memory and reads a matrix from a file depending on its type
void load_file(FILE *in, image_t *photo, char *file);

//saves the image into a given file
void save_image(image_t *photo);

#endif