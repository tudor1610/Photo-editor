//Copyright Tudor Brandibur 313CAa 2023-2024
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "photo.h"
#include "filters.h"
#include "dimensions.h"

#define NMAX 1000

// typedef struct {
// 	int r, g, b;
// } rgb_t;

// typedef struct {
// 	char type[3];
// 	int n, m;
// 	int maxval;
// 	int **mat;
// 	int is_mat;
// 	int x1, x2, y1, y2;
// 	rgb_t **color;
// 	int is_col;
// } image_t;

// //allocates memory for an int type matrix
// int **alloc_mat(int n, int m)
// {
// 	int **a = (int **)malloc(n * sizeof(int *));
// 	if (!a) {
// 		printf("malloc() failed 1\n");
// 		return NULL;
// 	}
// 	for (int i = 0; i < n; ++i) {
// 		a[i] = (int *)malloc(m * sizeof(int));
// 		if (!a[i]) {
// 			printf("malloc() failed 2\n");
// 			for (int j = i - 1; j >= 0; --j)
// 				free(a[j]);
// 			free(a);
// 			return NULL;
// 		}
// 	}
// 	return a;
// }

// //allocates memory for a rgb_t matrix
// rgb_t **alloc_col_mat(int n, int m)
// {
// 	rgb_t **a = (rgb_t **)malloc(n * sizeof(rgb_t *));
// 	if (!a) {
// 		printf("calloc() failed 1\n");
// 		return NULL;
// 	}
// 	for (int i = 0; i < n; ++i) {
// 		a[i] = (rgb_t *)malloc(m * sizeof(rgb_t));
// 		if (!a[i]) {
// 			printf("calloc() failed 2\n");
// 			for (int j = i - 1; j >= 0; --j)
// 				free(a[j]);
// 			free(a);
// 			return NULL;
// 		}
// 	}
// 	return a;
// }

// //reads a matrix form an ascii file
// void read_matrix_ASCII(int m, int n, int **a, FILE *in)
// {
// 	int cnt = 0;
// 	for (int i = 0; i < m; i++) {
// 		for (int j = 0; j < n; j++) {
// 			if (fscanf(in, "%d", &a[i][j]) != EOF)
// 				cnt++;
// 		}
// 	}
// 	if (cnt != n * m) {
// 		for (int i = 0; i < m; ++i)
// 			free(a[i]);
// 		free(a);
// 		a = NULL;
// 	}
// }

// //reads an rgb_t matrix from an ascii file
// void read_color_ASCII(int n, int m, rgb_t **a, FILE *in)
// {
// 	int cnt = 0;
// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < m; j++) {
// 			if (fscanf(in, "%d%d%d", &a[i][j].r, &a[i][j].g, &a[i][j].b) != EOF)
// 				cnt++;
// 		}
// 	}
// 	if (cnt != n * m) {
// 		printf("Filed to load matrix 111\n");
// 		for (int i = 0; i < n; ++i)
// 			free(a[i]);
// 		free(a);
// 		a = NULL;
// 	}
// }

// //reads an rgb_t matrix from a binary file
// void read_color_BIN(int n, int m, rgb_t **a, FILE *in)
// {
// 	int cnt = 0;
// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < m; j++) {
// 			unsigned char r, g, b;
// 			if (fread(&r, sizeof(unsigned char), 1, in) &&
// 				fread(&g, sizeof(unsigned char), 1, in) &&
// 				fread(&b, sizeof(unsigned char), 1, in)) {
// 				a[i][j].r = (int)r;
// 				a[i][j].g = (int)g;
// 				a[i][j].b = (int)b;
// 				cnt++;
// 			}
// 		}
// 	}
// 	if (cnt != n * m) {
// 		printf("Filed to load matrix 111\n");
// 		for (int i = 0; i < n; ++i)
// 			free(a[i]);
// 		free(a);
// 		a = NULL;
// 	}
// }

// //reads an int matrix from a binary file
// void read_matrix_BIN(int m, int n, int **a, FILE *in)
// {
// 	int cnt = 0;
// 	unsigned char c;
// 	for (int i = 0; i < m; i++) {
// 		for (int j = 0; j < n; j++)
// 			if (fread(&c, sizeof(unsigned char), 1, in) == 1) {
// 				cnt++;
// 				a[i][j] = (int)c;
// 			}
// 	}
// 	if (cnt != n * m) {
// 		printf("Filed to load matrix\n");
// 		for (int i = 0; i < m; ++i)
// 			free(a[i]);
// 		free(a);
// 		a = NULL;
// 	}
// }

// //skips the empty lines and the ones that start with '#'
// void skip_comm(FILE *in)
// {
// 	char buf[NMAX], c;
// 	fscanf(in, "%c", &c);
// 	while (c == '#' || c == ' ' || c == '\n' || c == '\t') {
// 		if (c == '#') {
// 			fgets(buf, NMAX, in);
// 		} else {
// 			if (c == EOF)
// 				return;
// 		}
// 		fscanf(in, "%c", &c);
// 	}
// 	fseek(in, -1, SEEK_CUR);
// }

// //deallocates a given matrix
// void destroy_mat_GREY(int n, int **mat)
// {
// 	for (int i = 0; i < n; ++i)
// 		free(mat[i]);
// 	free(mat);
// }

// //deallocates a given rgb_t matrix
// void destroy_mat_COL(int n, rgb_t **mat)
// {
// 	for (int i = 0; i < n; ++i)
// 		free(mat[i]);
// 	free(mat);
// }

// //allocates memory and reads a matrix from a file depending on its type
// void load_file(FILE *in, image_t *photo, char *file)
// {
// 	int **ok;
// 	rgb_t **v;
// 	if (photo->is_mat) {
// 		destroy_mat_GREY(photo->n, photo->mat);
// 		photo->mat = NULL;
// 		photo->is_mat = 0;
// 	} else if (photo->is_col) {
// 		destroy_mat_COL(photo->n, photo->color);
// 		photo->color = NULL;
// 		photo->is_col = 0;
// 	}
// 	skip_comm(in);
// 	if (!fscanf(in, "%s", photo->type)) {
// 		fprintf(stderr, "Couldn't load type\n");
// 		return;
// 	}
// 	skip_comm(in);
// 	fscanf(in, "%d%d", &photo->m, &photo->n);
// 	photo->x1 = 0;
// 	photo->y1 = 0;
// 	photo->x2 = photo->m;
// 	photo->y2 = photo->n;
// 	skip_comm(in);
// 	if (!strcmp(photo->type, "P3") || !strcmp(photo->type, "P6")) {
// 		photo->color = alloc_col_mat(photo->n, photo->m);
// 		fscanf(in, "%d", &photo->maxval);
// 		skip_comm(in);
// 		if (!strcmp(photo->type, "P3")) {
// 			read_color_ASCII(photo->n, photo->m, photo->color, in);
// 			v = photo->color;
// 		} else {
// 			read_color_BIN(photo->n, photo->m, photo->color, in);
// 			v = photo->color;
// 		}
// 		photo->is_col = 1;
// 		if (v) {
// 			printf("Loaded %s\n", file);
// 		} else {
// 			printf("Failed to load %s\n", file);
// 			photo->is_col = 0;
// 		}
// 	} else {
// 		photo->mat = alloc_mat(photo->n, photo->m);
// 		if (!strcmp(photo->type, "P1") || !strcmp(photo->type, "P4")) {
// 			if (!strcmp(photo->type, "P1")) {
// 				read_matrix_ASCII(photo->n, photo->m, photo->mat, in);
// 				ok = photo->mat;
// 			} else {
// 				read_matrix_BIN(photo->n, photo->m, photo->mat, in);
// 				ok = photo->mat;
// 			}
// 		}
// 		if (!strcmp(photo->type, "P2") || !strcmp(photo->type, "P5")) {
// 			fscanf(in, "%d", &photo->maxval);
// 			skip_comm(in);
// 			if (!strcmp(photo->type, "P2")) {
// 				read_matrix_ASCII(photo->n, photo->m, photo->mat, in);
// 				ok = photo->mat;
// 			} else {
// 				read_matrix_BIN(photo->n, photo->m, photo->mat, in);
// 				ok = photo->mat;
// 			}
// 		}
// 		photo->is_mat = 1;
// 		if (ok) {
// 			printf("Loaded %s\n", file);
// 		} else {
// 			printf("Failed to load %s\n", file);
// 			photo->is_mat = 0;
// 		}
// 		//print_matrix(photo->n, photo->m, photo->mat);
// 	}
// }

//transforms a string into a number
// int char_to_int(char s[10])
// {
// 	int p = 1, len = strlen(s);
// 	while (len > 1) {
// 		p *= 10;
// 		len--;
// 	}
// 	len = strlen(s);
// 	int x = 0;
// 	for (int i = 0; i < len; ++i) {
// 		int n = s[i] - '0';
// 		x += n * p;
// 		p /= 10;
// 	}
// 	return x;
// }

// //makes a selection from the photo (given coordonates)
// void case_select(image_t *photo, char buff[100])
// {
// 	int x11, y11, x22, y22, ok = 1, k = 0, sp = 0, n, m, x1, x2, y1, y2;
// 	x11 = photo->x1; y11 = photo->y1; x22 = photo->x2; y22 = photo->y2;
// 	if (photo->is_col == 0 && photo->is_mat == 0) {
// 		printf("No image loaded\n"); return;
// 	}
// 	char car[] = "0123456789 -\n";
// 	for (int i = 0; buff[i]; ++i) {
// 		if (!strchr(car, buff[i]))
// 			k = 1;
// 		if (buff[i] == ' ') {
// 			while (buff[i] == ' ')
// 				i++;
// 			sp++; i--;
// 		}
// 	}
// 	if (k || sp < 4) {
// 		printf("Invalid command\n");
// 		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
// 		return;
// 	}
// 	char *p;
// 	p = strtok(buff, " ");
// 	if (p[0] == '-') {
// 		int len = strlen(p);
// 		for (int i = 0; i < len - 1; ++i)
// 			p[i] = p[i + 1];
// 		photo->x1 = -1 * char_to_int(p);
// 	} else {
// 		photo->x1 = char_to_int(p);
// 	}
// 	p = strtok(NULL, " ");
// 	if (p[0] == '-') {
// 		int len = strlen(p);
// 		for (int i = 0; i < len - 1; ++i)
// 			p[i] = p[i + 1];
// 		photo->y1 = -1 * char_to_int(p);
// 	} else {
// 		photo->y1 = char_to_int(p);
// 	}
// 	p = strtok(NULL, " ");
// 	if (p[0] == '-') {
// 		int len = strlen(p);
// 		for (int i = 0; i < len - 1; ++i)
// 			p[i] = p[i + 1];
// 		photo->x2 = -1 * char_to_int(p);
// 	} else {
// 		photo->x2 = char_to_int(p);
// 	}
// 	p = strtok(NULL, " ");
// 	int len = strlen(p);
// 	p[len - 1] = '\0';
// 	if (p[0] == '-') {
// 		int len = strlen(p);
// 		for (int i = 0; i < len - 1; ++i)
// 			p[i] = p[i + 1];
// 		photo->y2 = -1 * char_to_int(p);
// 	} else {
// 		photo->y2 = char_to_int(p);
// 	}
// 	n = photo->n; m = photo->m;
// 	if (photo->x1 > photo->x2) {
// 		int tmp = photo->x1; photo->x1 = photo->x2; photo->x2 = tmp;
// 	}
// 	if (photo->y1 > photo->y2) {
// 		int tmp = photo->y1; photo->y1 = photo->y2; photo->y2 = tmp;
// 	}
// 	x1 = photo->x1; y1 = photo->y1; x2 = photo->x2; y2 = photo->y2;
// 	if (x1 < 0 || y1 < 0 || x2 > m || y2 > n) {
// 		printf("Invalid set of coordinates\n"); ok = 0;
// 		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
// 	} else if (x1 == y1 && x2 == y2 && y1 == x2) {
// 		printf("Invalid set of coordinates\n"); ok = 0;
// 		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
// 	} else if (x1 == x2 || y1 == y2) {
// 		printf("Invalid set of coordinates\n"); ok = 0;
// 		photo->x1 = x11; photo->y1 = y11; photo->x2 = x22; photo->y2 = y22;
// 	}
// 	if (ok)
// 		printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
// }

// //selects the whole photo
// void case_select_all(image_t *photo)
// {
// 	if (photo->is_col == 0 && photo->is_mat == 0) {
// 		printf("No image loaded\n");
// 		return;
// 	}
// 	photo->x1 = 0;
// 	photo->y1 = 0;
// 	photo->x2 = photo->m;
// 	photo->y2 = photo->n;
// 	printf("Selected ALL\n");
// }

// //saves the image into a given file
// void save_image(image_t *photo)
// {
// 	char buf[100], file[50], format[10] = "", *p;
// 	fgets(buf, 100, stdin);
// 	int len = strlen(buf);
// 	buf[len - 1] = '\0';
// 	p = strtok(buf, " ");
// 	strcpy(file, p);
// 	p = strtok(NULL, " ");
// 	if (p) {
// 		strcpy(format, p);
// 		int len = strlen(format);
// 		format[len - 1] = '\0';
// 	}
// 	FILE  *out;
// 	if (photo->is_mat) {
// 		if (!strcmp(format, "ascii")) {
// 			out = fopen(file, "wt");
// 			fprintf(out, "P2\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
// 			for (int i = 0; i < photo->n; ++i) {
// 				for (int j = 0; j < photo->m; ++j)
// 					fprintf(out, "%d ", photo->mat[i][j]);
// 				fprintf(out, "\n");
// 			}
// 		} else {
// 			out = fopen(file, "wb");
// 			fprintf(out, "P5\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
// 			for (int i = 0; i < photo->n; ++i) {
// 				for (int j = 0; j < photo->m; ++j) {
// 					unsigned char c = (unsigned char)photo->mat[i][j];
// 					fwrite(&c, sizeof(unsigned char), 1, out);
// 				}
// 			}
// 		}
// 		fclose(out);
// 		printf("Saved %s\n", file);
// 	} else if (photo->is_col) {
// 		if (!strcmp(format, "ascii")) {
// 			out = fopen(file, "wt");
// 			fprintf(out, "P3\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
// 			for (int i = 0; i < photo->n; ++i) {
// 				for (int j = 0; j < photo->m; ++j) {
// 					fprintf(out, "%d ", photo->color[i][j].r);
// 					fprintf(out, "%d ", photo->color[i][j].g);
// 					fprintf(out, "%d ", photo->color[i][j].b);
// 				}
// 				fprintf(out, "\n");
// 			}
// 		} else {
// 			out = fopen(file, "wb");
// 			fprintf(out, "P6\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
// 			for (int i = 0; i < photo->n; ++i) {
// 				for (int j = 0; j < photo->m; ++j) {
// 					unsigned char r, g, b;
// 					r = (unsigned char)photo->color[i][j].r;
// 					g = (unsigned char)photo->color[i][j].g;
// 					b = (unsigned char)photo->color[i][j].b;
// 					fwrite(&r, sizeof(unsigned char), 1, out);
// 					fwrite(&g, sizeof(unsigned char), 1, out);
// 					fwrite(&b, sizeof(unsigned char), 1, out);
// 				}
// 			}
// 		}
// 		fclose(out);
// 		printf("Saved %s\n", file);
// 	} else {
// 		printf("No image loaded\n");
// 	}
// }

// //makes the histogram
// void histogram(image_t *photo)
// {
// 	int star, bin, freq[256] = {0}, his[256] = {0}, fmax = 0;
// 	char buf[100], *p;
// 	fgets(buf, 100, stdin);
// 	p = strtok(buf, " ");
// 	if (!photo->is_mat && !photo->is_col) {
// 		printf("No image loaded\n");
// 		return;
// 	}
// 	if (p[0] != '\n') {
// 		star = char_to_int(p);
// 	} else {
// 		printf("Invalid command\n");
// 		return;
// 	}
// 	p = strtok(NULL, " ");
// 	if (p) {
// 		int len = strlen(p);
// 		p[len - 1] = '\0';
// 		bin = char_to_int(p);
// 		p = strtok(NULL, " ");gcc -Wall -Wextra -Werror -g -c image_editor.c
// 		if (p) {
// 			printf("Invalid command\n");
// 			return;
// 		}

// 	} else {
// 		printf("Invalid command\n");
// 		return;
// 	}
// 	if (photo->is_col) {
// 		printf("Black and white image needed\n");
// 		return;
// 	}
// 	for (int i = 0; i < photo->n; ++i) {
// 		for (int j = 0; j < photo->m; ++j)
// 			freq[photo->mat[i][j]]++;
// 	}
// 	if (bin < 256) {
// 		int k = 0, nr = 256 / bin;
// 		while (k < bin) {
// 			for (int i = 0; i < nr; ++i)
// 				his[k] += freq[k * nr + i];
// 			if (his[k] > fmax)
// 				fmax = his[k];
// 			k++;
// 		}
// 	} else if (bin == 256) {
// 		for (int i = 0; i < bin; ++i) {
// 			his[i] = freq[i];
// 			if (his[i] > fmax)
// 				fmax = his[i];
// 		}
// 	}
// 	for (int i = 0; i < bin; ++i) {
// 		long long nrs;
// 		nrs = his[i] * star / fmax;
// 		printf("%lld	|	", nrs);
// 		for (int j = 0; j < nrs; ++j)
// 			printf("*");
// 		printf("\n");
// 	}
// }

// //equalizes a black and white image
// void equalize(image_t *photo)
// {
// 	if (photo->is_col) {
// 		printf("Black and white image needed\n");
// 		return;
// 	}
// 	if (!photo->is_mat && !photo->is_col) {
// 		printf("No image loaded\n");
// 		return;
// 	}
// 	int freq[256] = {0};
// 	for (int i = 0; i < photo->n; ++i)
// 		for (int j = 0; j < photo->m; ++j)
// 			freq[photo->mat[i][j]]++;
// 	int area = photo->n * photo->m;
// 	for (int i = 0; i < photo->n; ++i) {
// 		for (int j = 0; j < photo->m; ++j) {
// 			int sum = 0;
// 			double f;
// 			for (int k = 0; k <= photo->mat[i][j]; k++)
// 				sum += freq[k];
// 			f = 255 * sum / area;
// 			if (f > 255)
// 				f = 255;
// 			photo->mat[i][j] = round(f);
// 		}
// 	}
// 	printf("Equalize done\n");
// }

// //swaps to given matrices
// void matrix_swap(int ***a, int ***b)
// {
// 	int **aux = *a;
// 	*a = *b;
// 	*b = aux;
// }

// //swaps to rgb_t matrices
// void matrix_swap_rgb(rgb_t ***a, rgb_t ***b)
// {
// 	rgb_t **aux = *a;
// 	*a = *b;
// 	*b = aux;
// }

// //rotates the photo 90 degrees to the left
// void turn_left(image_t *photo)
// {
// 	int x1, y1, x2, y2;
// 	x1 = photo->x1;
// 	y1 = photo->y1;
// 	x2 = photo->x2;
// 	y2 = photo->y2;
// 	int height = photo->y2 - photo->y1;
// 	int width = photo->x2 - photo->x1;
// 	if (photo->is_mat) {
// 		if (x1 == 0 && y1 == 0 && x2 == photo->m && y2 == photo->n) {
// 			//rotate whole photo
// 			int **tmp = alloc_mat(photo->m, photo->n);
// 			for (int i = 0; i < photo->m; ++i)
// 				for (int j = 0; j < photo->n; ++j)
// 					tmp[i][j] = photo->mat[j][photo->m - i - 1];
// 			matrix_swap(&tmp, &photo->mat);
// 			destroy_mat_GREY(photo->n, tmp);
// 			int aux = photo->m;
// 			photo->m = photo->n;
// 			photo->n = aux;
// 			photo->x1 = 0;
// 			photo->y1 = 0;
// 			photo->x2 = photo->m;
// 			photo->y2 = photo->n;
// 		} else if (height == width) {
// 			//rotate a square selection
// 			int **tmp = alloc_mat(width, height);
// 			for (int i = 0; i < height; ++i)
// 				for (int j = 0; j < width; ++j)
// 					tmp[i][j] = photo->mat[y1 + j][x1 + height - 1 - i];
// 			for (int i = y1; i < y2; ++i)
// 				for (int j = x1; j < x2; ++j)
// 					photo->mat[i][j] = tmp[i - y1][j - x1];
// 			destroy_mat_GREY(width, tmp);
// 		} else {
// 			printf("The selection must be square\n");
// 		}
// 	} else if (photo->is_col) {
// 		if (x1 == 0 && y1 == 0 && x2 == photo->m && y2 == photo->n) {
// 			//rotate whole photo rgb_t
// 			rgb_t **tmp = alloc_col_mat(photo->m, photo->n);
// 			for (int i = 0; i < photo->m; ++i)
// 				for (int j = 0; j < photo->n; ++j) {
// 					tmp[i][j].r = photo->color[j][photo->m - i - 1].r;
// 					tmp[i][j].g = photo->color[j][photo->m - i - 1].g;
// 					tmp[i][j].b = photo->color[j][photo->m - i - 1].b;
// 				}
// 			matrix_swap_rgb(&tmp, &photo->color);
// 			destroy_mat_COL(photo->n, tmp);
// 			int aux = photo->m;
// 			photo->m = photo->n;
// 			photo->n = aux;
// 			photo->x1 = 0;
// 			photo->y1 = 0;
// 			photo->x2 = photo->m;
// 			photo->y2 = photo->n;
// 		} else if (height == width) {
// 			//rotates square selection rgb_t
// 			rgb_t **tmp = alloc_col_mat(width, height);
// 			for (int i = 0; i < height; ++i)
// 				for (int j = 0; j < width; ++j) {
// 					tmp[i][j].r = photo->color[y1 + j][x1 + height - 1 - i].r;
// 					tmp[i][j].g = photo->color[y1 + j][x1 + height - 1 - i].g;
// 					tmp[i][j].b = photo->color[y1 + j][x1 + height - 1 - i].b;
// 			}
// 			for (int i = y1; i < y2; ++i)
// 				for (int j = x1; j < x2; ++j) {
// 					photo->color[i][j].r = tmp[i - y1][j - x1].r;
// 					photo->color[i][j].g = tmp[i - y1][j - x1].g;
// 					photo->color[i][j].b = tmp[i - y1][j - x1].b;
// 				}
// 			destroy_mat_COL(width, tmp);
// 		} else {
// 			printf("The selection must be square\n");
// 		}
// 	}
// }

// //rotates the photo (given an angle)
// void rotate(image_t *photo)
// {
// 	int angle;
// 	scanf("%d", &angle);
// 	if (!photo->is_mat && !photo->is_col) {
// 		printf("No image loaded\n");
// 		return;
// 	}
// 	if (angle == 90) {
// 		turn_left(photo);
// 		turn_left(photo);
// 		turn_left(photo);
// 	} else if (angle == -90) {
// 		turn_left(photo);
// 	} else if (angle == 180 || angle == -180) {
// 		turn_left(photo);
// 		turn_left(photo);
// 	} else if (angle == 270) {
// 		turn_left(photo);
// 	} else if (angle == -270) {
// 		turn_left(photo);
// 		turn_left(photo);
// 		turn_left(photo);
// 	} else if (angle == 360 || angle == -360 || angle == 0) {
// 		turn_left(photo);
// 		turn_left(photo);
// 		turn_left(photo);
// 		turn_left(photo);
// 	} else {
// 		printf("Unsupported rotation angle\n");
// 		return;
// 	}
// 	printf("Rotated %d\n", angle);
// }

// //crops the image
// void crop(image_t *photo)
// {
// 	if (photo->is_mat) {
// 		int height, width;
// 		width = photo->x2 - photo->x1;
// 		height = photo->y2 - photo->y1;
// 		int **tmp = alloc_mat(height, width);
// 		for (int i = 0; i < height; ++i)
// 			for (int j = 0; j < width; ++j)
// 				tmp[i][j] = photo->mat[photo->y1 + i][photo->x1 + j];
// 		matrix_swap(&tmp, &photo->mat);
// 		destroy_mat_GREY(photo->n, tmp);
// 		photo->n = height;
// 		photo->m = width;
// 		photo->x1 = 0;
// 		photo->y1 = 0;
// 		photo->x2 = photo->m;
// 		photo->y2 = photo->n;
// 		printf("Image cropped\n");
// 	} else if (photo->is_col) {
// 		int height, width;
// 		width = photo->x2 - photo->x1;
// 		height = photo->y2 - photo->y1;
// 		rgb_t **tmp = alloc_col_mat(height, width);
// 		for (int i = 0; i < height; ++i) {
// 			for (int j = 0; j < width; ++j) {
// 				tmp[i][j].r = photo->color[photo->y1 + i][photo->x1 + j].r;
// 				tmp[i][j].g = photo->color[photo->y1 + i][photo->x1 + j].g;
// 				tmp[i][j].b = photo->color[photo->y1 + i][photo->x1 + j].b;
// 			}
// 		}
// 		matrix_swap_rgb(&tmp, &photo->color);
// 		destroy_mat_COL(photo->n, tmp);
// 		photo->n = height;
// 		photo->m = width;
// 		photo->x1 = 0;
// 		photo->y1 = 0;
// 		photo->x2 = photo->m;
// 		photo->y2 = photo->n;
// 		printf("Image cropped\n");
// 	} else {
// 		printf("No image loaded\n");
// 	}
// }

// void edge(image_t *photo)
// {
// 	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
// 	for (int i = 0; i < photo->n; ++i)
// 		for (int j = 0; j < photo->m; ++j) {
// 			tmp[i][j].r = photo->color[i][j].r;
// 			tmp[i][j].g = photo->color[i][j].g;
// 			tmp[i][j].b = photo->color[i][j].b;
// 		}
// 	for (int i = photo->y1; i < photo->y2; ++i)
// 		for (int j = photo->x1; j < photo->x2; ++j) {
// 			int r_sum = 0, g_sum = 0, b_sum = 0;
// 			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
// 				r_sum = photo->color[i][j].r * 8 - photo->color[i - 1][j - 1].r
// 				- photo->color[i - 1][j].r - photo->color[i - 1][j + 1].r -
// 				photo->color[i][j - 1].r - photo->color[i][j + 1].r -
// 				photo->color[i + 1][j - 1].r - photo->color[i + 1][j].r -
// 				photo->color[i + 1][j + 1].r;

// 				g_sum = photo->color[i][j].g * 8 - (photo->color[i - 1][j].g
// 				+ photo->color[i - 1][j - 1].g + photo->color[i - 1][j + 1].g +
// 				photo->color[i][j - 1].g + photo->color[i][j + 1].g +
// 				photo->color[i + 1][j - 1].g + photo->color[i + 1][j].g +
// 				photo->color[i + 1][j + 1].g);

// 				b_sum = photo->color[i][j].b * 8 - (photo->color[i - 1][j].b
// 				+ photo->color[i - 1][j - 1].b + photo->color[i - 1][j + 1].b +
// 				photo->color[i][j - 1].b + photo->color[i][j + 1].b +
// 				photo->color[i + 1][j - 1].b + photo->color[i + 1][j].b +
// 				photo->color[i + 1][j + 1].b);

// 				if (r_sum < 0)
// 					r_sum = 0;
// 				else if (r_sum > 255)
// 					r_sum = 255;
// 				if (g_sum < 0)
// 					g_sum = 0;
// 				else if (g_sum > 255)
// 					g_sum = 255;
// 				if (b_sum < 0)
// 					b_sum = 0;
// 				else if (b_sum > 255)
// 					b_sum = 255;
// 				tmp[i][j].r = r_sum;
// 				tmp[i][j].g = g_sum;
// 				tmp[i][j].b = b_sum;
// 			}
// 		}
// 	matrix_swap_rgb(&photo->color, &tmp);
// 	destroy_mat_COL(photo->n, tmp);
// 	printf("APPLY EDGE done\n");
// }

// void sharpen(image_t *photo)
// {
// 	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
// 	for (int i = 0; i < photo->n; ++i)
// 		for (int j = 0; j < photo->m; ++j) {
// 			tmp[i][j].r = photo->color[i][j].r;
// 			tmp[i][j].g = photo->color[i][j].g;
// 			tmp[i][j].b = photo->color[i][j].b;
// 		}
// 	for (int i = photo->y1; i < photo->y2; ++i)
// 		for (int j = photo->x1; j < photo->x2; ++j) {
// 			int r_sum = 0, g_sum = 0, b_sum = 0;
// 			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
// 				r_sum = photo->color[i][j].r * 5 - photo->color[i - 1][j].r -
// 				photo->color[i][j - 1].r - photo->color[i][j + 1].r -
// 				photo->color[i + 1][j].r;

// 				g_sum = photo->color[i][j].g * 5 - photo->color[i - 1][j].g -
// 				photo->color[i][j - 1].g - photo->color[i][j + 1].g -
// 				photo->color[i + 1][j].g;

// 				b_sum = photo->color[i][j].b * 5 - photo->color[i - 1][j].b -
// 				photo->color[i][j - 1].b - photo->color[i][j + 1].b -
// 				photo->color[i + 1][j].b;
// 				if (r_sum < 0)
// 					r_sum = 0;
// 				else if (r_sum > 255)
// 					r_sum = 255;
// 				if (g_sum < 0)
// 					g_sum = 0;
// 				else if (g_sum > 255)
// 					g_sum = 255;
// 				if (b_sum < 0)
// 					b_sum = 0;
// 				else if (b_sum > 255)
// 					b_sum = 255;
// 				tmp[i][j].r = r_sum;
// 				tmp[i][j].g = g_sum;
// 				tmp[i][j].b = b_sum;
// 			}
// 		}
// 	matrix_swap_rgb(&photo->color, &tmp);
// 	destroy_mat_COL(photo->n, tmp);
// 	printf("APPLY SHARPEN done\n");
// }

// void blur(image_t *photo)
// {
// 	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
// 	for (int i = 0; i < photo->n; ++i)
// 		for (int j = 0; j < photo->m; ++j) {
// 			tmp[i][j].r = photo->color[i][j].r;
// 			tmp[i][j].g = photo->color[i][j].g;
// 			tmp[i][j].b = photo->color[i][j].b;
// 		}
// 	for (int i = photo->y1; i < photo->y2; ++i)
// 		for (int j = photo->x1; j < photo->x2; ++j) {
// 			double r_sum = 0, g_sum = 0, b_sum = 0;
// 			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
// 				r_sum = (double)(photo->color[i][j].r +
// 				photo->color[i - 1][j - 1].r + photo->color[i - 1][j].r +
// 				photo->color[i - 1][j + 1].r + photo->color[i][j - 1].r +
// 				photo->color[i][j + 1].r + photo->color[i + 1][j - 1].r +
// 				photo->color[i + 1][j].r + photo->color[i + 1][j + 1].r) / 9;

// 				g_sum = (double)(photo->color[i][j].g +
// 				photo->color[i - 1][j - 1].g + photo->color[i - 1][j].g +
// 				photo->color[i - 1][j + 1].g + photo->color[i][j - 1].g +
// 				photo->color[i][j + 1].g + photo->color[i + 1][j - 1].g +
// 				photo->color[i + 1][j].g + photo->color[i + 1][j + 1].g) / 9;

// 				b_sum = (double)(photo->color[i][j].b +
// 				photo->color[i - 1][j - 1].b + photo->color[i - 1][j].b +
// 				photo->color[i - 1][j + 1].b + photo->color[i][j - 1].b +
// 				photo->color[i][j + 1].b + photo->color[i + 1][j - 1].b +
// 				photo->color[i + 1][j].b + photo->color[i + 1][j + 1].b) / 9;

// 				r_sum = round(r_sum);
// 				g_sum = round(g_sum);
// 				b_sum = round(b_sum);

// 				if (r_sum < 0)
// 					r_sum = 0;
// 				else if (r_sum > 255)
// 					r_sum = 255;
// 				if (g_sum < 0)
// 					g_sum = 0;
// 				else if (g_sum > 255)
// 					g_sum = 255;
// 				if (b_sum < 0)
// 					b_sum = 0;
// 				else if (b_sum > 255)
// 					b_sum = 255;
// 				tmp[i][j].r = r_sum;
// 				tmp[i][j].g = g_sum;
// 				tmp[i][j].b = b_sum;
// 			}
// 		}
// 	matrix_swap_rgb(&photo->color, &tmp);
// 	destroy_mat_COL(photo->n, tmp);
// 	printf("APPLY BLUR done\n");
// }

// void gaussian_blur(image_t *photo)
// {
// 	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
// 	for (int i = 0; i < photo->n; ++i)
// 		for (int j = 0; j < photo->m; ++j) {
// 			tmp[i][j].r = photo->color[i][j].r;
// 			tmp[i][j].g = photo->color[i][j].g;
// 			tmp[i][j].b = photo->color[i][j].b;
// 		}
// 	for (int i = photo->y1; i < photo->y2; ++i)
// 		for (int j = photo->x1; j < photo->x2; ++j) {
// 			double r_sum = 0, g_sum = 0, b_sum = 0;
// 			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
// 				r_sum = (double)(4 * photo->color[i][j].r +
// 				photo->color[i - 1][j - 1].r + 2 * photo->color[i - 1][j].r +
// 				photo->color[i - 1][j + 1].r + 2 * photo->color[i][j - 1].r +
// 				2 * photo->color[i][j + 1].r + photo->color[i + 1][j - 1].r +
// 				2 * photo->color[i + 1][j].r + photo->color[i + 1][j + 1].r) /
// 				16;

// 				g_sum = (double)(4 * photo->color[i][j].g +
// 				photo->color[i - 1][j - 1].g + 2 * photo->color[i - 1][j].g +
// 				photo->color[i - 1][j + 1].g + 2 * photo->color[i][j - 1].g +
// 				2 * photo->color[i][j + 1].g + photo->color[i + 1][j - 1].g +
// 				2 * photo->color[i + 1][j].g + photo->color[i + 1][j + 1].g) /
// 				16;

// 				b_sum = (double)(4 * photo->color[i][j].b +
// 				photo->color[i - 1][j - 1].b + 2 * photo->color[i - 1][j].b +
// 				photo->color[i - 1][j + 1].b + 2 * photo->color[i][j - 1].b +
// 				2 * photo->color[i][j + 1].b + photo->color[i + 1][j - 1].b +
// 				2 * photo->color[i + 1][j].b + photo->color[i + 1][j + 1].b) /
// 				16;

// 				r_sum = round(r_sum);
// 				g_sum = round(g_sum);
// 				b_sum = round(b_sum);

// 				if (r_sum < 0)
// 					r_sum = 0;
// 				else if (r_sum > 255)
// 					r_sum = 255;
// 				if (g_sum < 0)
// 					g_sum = 0;
// 				else if (g_sum > 255)
// 					g_sum = 255;
// 				if (b_sum < 0)
// 					b_sum = 0;
// 				else if (b_sum > 255)
// 					b_sum = 255;
// 				tmp[i][j].r = r_sum;
// 				tmp[i][j].g = g_sum;
// 				tmp[i][j].b = b_sum;
// 			}
// 		}
// 	matrix_swap_rgb(&photo->color, &tmp);
// 	destroy_mat_COL(photo->n, tmp);
// 	printf("APPLY GAUSSIAN_BLUR done\n");
// }

// //applies one of the for filters from above
// void apply(image_t *photo)
// {
// 	char buff[100], format[30], *p;
// 	fgets(buff, 100, stdin);
// 	p = strtok(buff, " ");
// 	strcpy(format, p);
// 	if (!photo->is_mat && !photo->is_col) {
// 		printf("No image loaded\n");
// 		return;
// 	}
// 	if (p[0] != '\n') {
// 		int len = strlen(format);
// 		format[len - 1] = '\0';
// 		if (photo->is_mat) {
// 			printf("Easy, Charlie Chaplin\n");
// 			return;
// 		} else if (!strcmp(format, "EDGE")) {
// 			edge(photo);
// 			return;
// 		} else if (!strcmp(format, "SHARPEN")) {
// 			sharpen(photo);
// 			return;
// 		} else if (!strcmp(format, "BLUR")) {
// 			blur(photo);
// 			return;
// 		} else if (!strcmp(format, "GAUSSIAN_BLUR")) {
// 			gaussian_blur(photo);
// 			return;
// 		} else if (!strcmp(format, "\n")) {
// 			printf("Invalid command\n");
// 			return;
// 		}
// 		printf("APPLY parameter invalid\n");
// 	} else {
// 		printf("Invalid command\n");
// 	}
// }

int main(void)
{
	char imp[20] = "";
	image_t photo;
	photo.is_col = 0;
	photo.is_mat = 0;
	FILE *in;
	int ok = 1;
	while (ok) {
		scanf("%s", imp);
		if (!strcmp(imp, "LOAD")) {
			char file[30];
			scanf("%s", file);
			in = fopen(file, "rb");
			if (!in) {
				printf("Failed to load %s\n", file);
				if (photo.is_col) {
					destroy_mat_COL(photo.n, photo.color);
					photo.is_col = 0;
				}
				if (photo.is_mat) {
					destroy_mat_GREY(photo.n, photo.mat);
					photo.is_mat = 0;
				}
			} else {
				load_file(in, &photo, file);
				fclose(in);
			}
		} else if (!strcmp(imp, "SELECT")) {
			char buff[100] = "", *p, s[100];
			fgets(buff, 100, stdin);
			strcpy(s, buff);
			p = strtok(buff, " ");
			if (p[0] == 'A')
				p[3] = '\0';
			if (!strcmp(p, "ALL"))
				case_select_all(&photo);
			else if (isdigit(p[0]) || p[0] == '-')
				case_select(&photo, s);
			else
				printf("Invalid command\n");
		} else if (!strcmp(imp, "HISTOGRAM")) {
			histogram(&photo);
		} else if (!strcmp(imp, "EQUALIZE")) {
			equalize(&photo);
		} else if (!strcmp(imp, "ROTATE")) {
			rotate(&photo);
		} else if (!strcmp(imp, "CROP")) {
			crop(&photo);
		} else if (!strcmp(imp, "APPLY")) {
			apply(&photo);
		} else if (!strcmp(imp, "SAVE")) {
			save_image(&photo);
		} else if (!strcmp(imp, "EXIT")) {
			if (photo.is_mat) {
				destroy_mat_GREY(photo.n, photo.mat);
				photo.mat = NULL;
				ok = 0;
			} else if (photo.is_col) {
				destroy_mat_COL(photo.n, photo.color);
				photo.color = NULL;
				ok = 0;
			} else {
				printf("No image loaded\n");
				ok = 0;
			}
		} else {
			char buff[100];
			fgets(buff, 100, stdin);
			printf("Invalid command\n");
		}
	}
	return 0;
}
