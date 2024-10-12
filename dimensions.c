#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "photo.h"
//transforms a string into a number
int char_to_int(char s[10])
{
	int p = 1, len = strlen(s);
	while (len > 1) {
		p *= 10;
		len--;
	}
	len = strlen(s);
	int x = 0;
	for (int i = 0; i < len; ++i) {
		int n = s[i] - '0';
		x += n * p;
		p /= 10;
	}
	return x;
}

//makes a selection from the photo (given coordonates)
void case_select(image_t *photo, char buff[100])
{
	int x11, y11, x22, y22, ok = 1, k = 0, sp = 0, n, m, x1, x2, y1, y2;
	x11 = photo->x1; y11 = photo->y1; x22 = photo->x2; y22 = photo->y2;
	if (photo->is_col == 0 && photo->is_mat == 0) {
		printf("No image loaded\n"); return;
	}
	char car[] = "0123456789 -\n";
	for (int i = 0; buff[i]; ++i) {
		if (!strchr(car, buff[i]))
			k = 1;
		if (buff[i] == ' ') {
			while (buff[i] == ' ')
				i++;
			sp++; i--;
		}
	}
	if (k || sp < 4) {
		printf("Invalid command\n");
		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
		return;
	}
	char *p;
	p = strtok(buff, " ");
	if (p[0] == '-') {
		int len = strlen(p);
		for (int i = 0; i < len - 1; ++i)
			p[i] = p[i + 1];
		photo->x1 = -1 * char_to_int(p);
	} else {
		photo->x1 = char_to_int(p);
	}
	p = strtok(NULL, " ");
	if (p[0] == '-') {
		int len = strlen(p);
		for (int i = 0; i < len - 1; ++i)
			p[i] = p[i + 1];
		photo->y1 = -1 * char_to_int(p);
	} else {
		photo->y1 = char_to_int(p);
	}
	p = strtok(NULL, " ");
	if (p[0] == '-') {
		int len = strlen(p);
		for (int i = 0; i < len - 1; ++i)
			p[i] = p[i + 1];
		photo->x2 = -1 * char_to_int(p);
	} else {
		photo->x2 = char_to_int(p);
	}
	p = strtok(NULL, " ");
	int len = strlen(p);
	p[len - 1] = '\0';
	if (p[0] == '-') {
		int len = strlen(p);
		for (int i = 0; i < len - 1; ++i)
			p[i] = p[i + 1];
		photo->y2 = -1 * char_to_int(p);
	} else {
		photo->y2 = char_to_int(p);
	}
	n = photo->n; m = photo->m;
	if (photo->x1 > photo->x2) {
		int tmp = photo->x1; photo->x1 = photo->x2; photo->x2 = tmp;
	}
	if (photo->y1 > photo->y2) {
		int tmp = photo->y1; photo->y1 = photo->y2; photo->y2 = tmp;
	}
	x1 = photo->x1; y1 = photo->y1; x2 = photo->x2; y2 = photo->y2;
	if (x1 < 0 || y1 < 0 || x2 > m || y2 > n) {
		printf("Invalid set of coordinates\n"); ok = 0;
		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
	} else if (x1 == y1 && x2 == y2 && y1 == x2) {
		printf("Invalid set of coordinates\n"); ok = 0;
		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
	} else if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n"); ok = 0;
		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
	}
	if (ok)
		printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

//selects the whole photo
void case_select_all(image_t *photo)
{
	if (photo->is_col == 0 && photo->is_mat == 0) {
		printf("No image loaded\n");
		return;
	}
	photo->x1 = 0;
	photo->y1 = 0;
	photo->x2 = photo->m;
	photo->y2 = photo->n;
	printf("Selected ALL\n");
}

//swaps to given matrices
void matrix_swap(int ***a, int ***b)
{
	int **aux = *a;
	*a = *b;
	*b = aux;
}

//swaps to rgb_t matrices
void matrix_swap_rgb(rgb_t ***a, rgb_t ***b)
{
	rgb_t **aux = *a;
	*a = *b;
	*b = aux;
}

//rotates the photo 90 degrees to the left
void turn_left(image_t *photo)
{
	int x1, y1, x2, y2;
	x1 = photo->x1;
	y1 = photo->y1;
	x2 = photo->x2;
	y2 = photo->y2;
	int height = photo->y2 - photo->y1;
	int width = photo->x2 - photo->x1;
	if (photo->is_mat) {
		if (x1 == 0 && y1 == 0 && x2 == photo->m && y2 == photo->n) {
			//rotate whole photo
			int **tmp = alloc_mat(photo->m, photo->n);
			for (int i = 0; i < photo->m; ++i)
				for (int j = 0; j < photo->n; ++j)
					tmp[i][j] = photo->mat[j][photo->m - i - 1];
			matrix_swap(&tmp, &photo->mat);
			destroy_mat_GREY(photo->n, tmp);
			int aux = photo->m;
			photo->m = photo->n;
			photo->n = aux;
			photo->x1 = 0;
			photo->y1 = 0;
			photo->x2 = photo->m;
			photo->y2 = photo->n;
		} else if (height == width) {
			//rotate a square selection
			int **tmp = alloc_mat(width, height);
			for (int i = 0; i < height; ++i)
				for (int j = 0; j < width; ++j)
					tmp[i][j] = photo->mat[y1 + j][x1 + height - 1 - i];
			for (int i = y1; i < y2; ++i)
				for (int j = x1; j < x2; ++j)
					photo->mat[i][j] = tmp[i - y1][j - x1];
			destroy_mat_GREY(width, tmp);
		} else {
			printf("The selection must be square\n");
		}
	} else if (photo->is_col) {
		if (x1 == 0 && y1 == 0 && x2 == photo->m && y2 == photo->n) {
			//rotate whole photo rgb_t
			rgb_t **tmp = alloc_col_mat(photo->m, photo->n);
			for (int i = 0; i < photo->m; ++i)
				for (int j = 0; j < photo->n; ++j) {
					tmp[i][j].r = photo->color[j][photo->m - i - 1].r;
					tmp[i][j].g = photo->color[j][photo->m - i - 1].g;
					tmp[i][j].b = photo->color[j][photo->m - i - 1].b;
				}
			matrix_swap_rgb(&tmp, &photo->color);
			destroy_mat_COL(photo->n, tmp);
			int aux = photo->m;
			photo->m = photo->n;
			photo->n = aux;
			photo->x1 = 0;
			photo->y1 = 0;
			photo->x2 = photo->m;
			photo->y2 = photo->n;
		} else if (height == width) {
			//rotates square selection rgb_t
			rgb_t **tmp = alloc_col_mat(width, height);
			for (int i = 0; i < height; ++i)
				for (int j = 0; j < width; ++j) {
					tmp[i][j].r = photo->color[y1 + j][x1 + height - 1 - i].r;
					tmp[i][j].g = photo->color[y1 + j][x1 + height - 1 - i].g;
					tmp[i][j].b = photo->color[y1 + j][x1 + height - 1 - i].b;
			}
			for (int i = y1; i < y2; ++i)
				for (int j = x1; j < x2; ++j) {
					photo->color[i][j].r = tmp[i - y1][j - x1].r;
					photo->color[i][j].g = tmp[i - y1][j - x1].g;
					photo->color[i][j].b = tmp[i - y1][j - x1].b;
				}
			destroy_mat_COL(width, tmp);
		} else {
			printf("The selection must be square\n");
		}
	}
}

//rotates the photo (given an angle)
void rotate(image_t *photo)
{
	int angle;
	scanf("%d", &angle);
	if (!photo->is_mat && !photo->is_col) {
		printf("No image loaded\n");
		return;
	}
	if (angle == 90) {
		turn_left(photo);
		turn_left(photo);
		turn_left(photo);
	} else if (angle == -90) {
		turn_left(photo);
	} else if (angle == 180 || angle == -180) {
		turn_left(photo);
		turn_left(photo);
	} else if (angle == 270) {
		turn_left(photo);
	} else if (angle == -270) {
		turn_left(photo);
		turn_left(photo);
		turn_left(photo);
	} else if (angle == 360 || angle == -360 || angle == 0) {
        //image does't need t turn
	} else {
		printf("Unsupported rotation angle\n");
		return;
	}
	printf("Rotated %d\n", angle);
}

//crops the image
void crop(image_t *photo)
{
	if (photo->is_mat) {
		int height, width;
		width = photo->x2 - photo->x1;
		height = photo->y2 - photo->y1;
		int **tmp = alloc_mat(height, width);
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				tmp[i][j] = photo->mat[photo->y1 + i][photo->x1 + j];
		matrix_swap(&tmp, &photo->mat);
		destroy_mat_GREY(photo->n, tmp);
		photo->n = height;
		photo->m = width;
		photo->x1 = 0;
		photo->y1 = 0;
		photo->x2 = photo->m;
		photo->y2 = photo->n;
		printf("Image cropped\n");
	} else if (photo->is_col) {
		int height, width;
		width = photo->x2 - photo->x1;
		height = photo->y2 - photo->y1;
		rgb_t **tmp = alloc_col_mat(height, width);
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				tmp[i][j].r = photo->color[photo->y1 + i][photo->x1 + j].r;
				tmp[i][j].g = photo->color[photo->y1 + i][photo->x1 + j].g;
				tmp[i][j].b = photo->color[photo->y1 + i][photo->x1 + j].b;
			}
		}
		matrix_swap_rgb(&tmp, &photo->color);
		destroy_mat_COL(photo->n, tmp);
		photo->n = height;
		photo->m = width;
		photo->x1 = 0;
		photo->y1 = 0;
		photo->x2 = photo->m;
		photo->y2 = photo->n;
		printf("Image cropped\n");
	} else {
		printf("No image loaded\n");
	}
}