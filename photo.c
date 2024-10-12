#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "photo.h"
#define NMAX 1000

//allocates memory for an int type matrix
int **alloc_mat(int n, int m)
{
	int **a = (int **)malloc(n * sizeof(int *));
	if (!a) {
		printf("malloc() failed 1\n");
		return NULL;
	}
	for (int i = 0; i < n; ++i) {
		a[i] = (int *)malloc(m * sizeof(int));
		if (!a[i]) {
			printf("malloc() failed 2\n");
			for (int j = i - 1; j >= 0; --j)
				free(a[j]);
			free(a);
			return NULL;
		}
	}
	return a;
}

//allocates memory for a rgb_t matrix
rgb_t **alloc_col_mat(int n, int m)
{
	rgb_t **a = (rgb_t **)malloc(n * sizeof(rgb_t *));
	if (!a) {
		printf("calloc() failed 1\n");
		return NULL;
	}
	for (int i = 0; i < n; ++i) {
		a[i] = (rgb_t *)malloc(m * sizeof(rgb_t));
		if (!a[i]) {
			printf("calloc() failed 2\n");
			for (int j = i - 1; j >= 0; --j)
				free(a[j]);
			free(a);
			return NULL;
		}
	}
	return a;
}

//reads a matrix form an ascii file
void read_matrix_ASCII(int m, int n, int **a, FILE *in)
{
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (fscanf(in, "%d", &a[i][j]) != EOF)
				cnt++;
		}
	}
	if (cnt != n * m) {
		for (int i = 0; i < m; ++i)
			free(a[i]);
		free(a);
		a = NULL;
	}
}

//reads an rgb_t matrix from an ascii file
void read_color_ASCII(int n, int m, rgb_t **a, FILE *in)
{
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (fscanf(in, "%d%d%d", &a[i][j].r, &a[i][j].g, &a[i][j].b) != EOF)
				cnt++;
		}
	}
	if (cnt != n * m) {
		printf("Filed to load matrix 111\n");
		for (int i = 0; i < n; ++i)
			free(a[i]);
		free(a);
		a = NULL;
	}
}

//reads an rgb_t matrix from a binary file
void read_color_BIN(int n, int m, rgb_t **a, FILE *in)
{
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			unsigned char r, g, b;
			if (fread(&r, sizeof(unsigned char), 1, in) &&
				fread(&g, sizeof(unsigned char), 1, in) &&
				fread(&b, sizeof(unsigned char), 1, in)) {
				a[i][j].r = (int)r;
				a[i][j].g = (int)g;
				a[i][j].b = (int)b;
				cnt++;
			}
		}
	}
	if (cnt != n * m) {
		printf("Filed to load matrix 111\n");
		for (int i = 0; i < n; ++i)
			free(a[i]);
		free(a);
		a = NULL;
	}
}

//reads an int matrix from a binary file
void read_matrix_BIN(int m, int n, int **a, FILE *in)
{
	int cnt = 0;
	unsigned char c;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			if (fread(&c, sizeof(unsigned char), 1, in) == 1) {
				cnt++;
				a[i][j] = (int)c;
			}
	}
	if (cnt != n * m) {
		printf("Filed to load matrix\n");
		for (int i = 0; i < m; ++i)
			free(a[i]);
		free(a);
		a = NULL;
	}
}

//skips the empty lines and the ones that start with '#'
void skip_comm(FILE *in)
{
	char buf[NMAX], c;
	fscanf(in, "%c", &c);
	while (c == '#' || c == ' ' || c == '\n' || c == '\t') {
		if (c == '#') {
			fgets(buf, NMAX, in);
		} else {
			if (c == EOF)
				return;
		}
		fscanf(in, "%c", &c);
	}
	fseek(in, -1, SEEK_CUR);
}

//deallocates a given matrix
void destroy_mat_GREY(int n, int **mat)
{
	for (int i = 0; i < n; ++i)
		free(mat[i]);
	free(mat);
}

//deallocates a given rgb_t matrix
void destroy_mat_COL(int n, rgb_t **mat)
{
	for (int i = 0; i < n; ++i)
		free(mat[i]);
	free(mat);
}

//allocates memory and reads a matrix from a file depending on its type
void load_file(FILE *in, image_t *photo, char *file)
{
	int **ok;
	rgb_t **v;
	if (photo->is_mat) {
		destroy_mat_GREY(photo->n, photo->mat);
		photo->mat = NULL;
		photo->is_mat = 0;
	} else if (photo->is_col) {
		destroy_mat_COL(photo->n, photo->color);
		photo->color = NULL;
		photo->is_col = 0;
	}
	skip_comm(in);
	if (!fscanf(in, "%s", photo->type)) {
		fprintf(stderr, "Couldn't load type\n");
		return;
	}
	skip_comm(in);
	fscanf(in, "%d%d", &photo->m, &photo->n);
	photo->x1 = 0;
	photo->y1 = 0;
	photo->x2 = photo->m;
	photo->y2 = photo->n;
	skip_comm(in);
	if (!strcmp(photo->type, "P3") || !strcmp(photo->type, "P6")) {
		photo->color = alloc_col_mat(photo->n, photo->m);
		fscanf(in, "%d", &photo->maxval);
		skip_comm(in);
		if (!strcmp(photo->type, "P3")) {
			read_color_ASCII(photo->n, photo->m, photo->color, in);
			v = photo->color;
		} else {
			read_color_BIN(photo->n, photo->m, photo->color, in);
			v = photo->color;
		}
		photo->is_col = 1;
		if (v) {
			printf("Loaded %s\n", file);
		} else {
			printf("Failed to load %s\n", file);
			photo->is_col = 0;
		}
	} else {
		photo->mat = alloc_mat(photo->n, photo->m);
		if (!strcmp(photo->type, "P1") || !strcmp(photo->type, "P4")) {
			if (!strcmp(photo->type, "P1")) {
				read_matrix_ASCII(photo->n, photo->m, photo->mat, in);
				ok = photo->mat;
			} else {
				read_matrix_BIN(photo->n, photo->m, photo->mat, in);
				ok = photo->mat;
			}
		}
		if (!strcmp(photo->type, "P2") || !strcmp(photo->type, "P5")) {
			fscanf(in, "%d", &photo->maxval);
			skip_comm(in);
			if (!strcmp(photo->type, "P2")) {
				read_matrix_ASCII(photo->n, photo->m, photo->mat, in);
				ok = photo->mat;
			} else {
				read_matrix_BIN(photo->n, photo->m, photo->mat, in);
				ok = photo->mat;
			}
		}
		photo->is_mat = 1;
		if (ok) {
			printf("Loaded %s\n", file);
		} else {
			printf("Failed to load %s\n", file);
			photo->is_mat = 0;
		}
	}
}

//saves the image into a given file
void save_image(image_t *photo)
{
	char buf[100], file[50], format[10] = "", *p;
	fgets(buf, 100, stdin);
	int len = strlen(buf);
	buf[len - 1] = '\0';
	p = strtok(buf, " ");
	strcpy(file, p);
	p = strtok(NULL, " ");
	if (p) {
		strcpy(format, p);
		int len = strlen(format);
		format[len - 1] = '\0';
	}
	FILE  *out;
	if (photo->is_mat) {
		if (!strcmp(format, "ascii")) {
			out = fopen(file, "wt");
			fprintf(out, "P2\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
			for (int i = 0; i < photo->n; ++i) {
				for (int j = 0; j < photo->m; ++j)
					fprintf(out, "%d ", photo->mat[i][j]);
				fprintf(out, "\n");
			}
		} else {
			out = fopen(file, "wb");
			fprintf(out, "P5\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
			for (int i = 0; i < photo->n; ++i) {
				for (int j = 0; j < photo->m; ++j) {
					unsigned char c = (unsigned char)photo->mat[i][j];
					fwrite(&c, sizeof(unsigned char), 1, out);
				}
			}
		}
		fclose(out);
		printf("Saved %s\n", file);
	} else if (photo->is_col) {
		if (!strcmp(format, "ascii")) {
			out = fopen(file, "wt");
			fprintf(out, "P3\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
			for (int i = 0; i < photo->n; ++i) {
				for (int j = 0; j < photo->m; ++j) {
					fprintf(out, "%d ", photo->color[i][j].r);
					fprintf(out, "%d ", photo->color[i][j].g);
					fprintf(out, "%d ", photo->color[i][j].b);
				}
				fprintf(out, "\n");
			}
		} else {
			out = fopen(file, "wb");
			fprintf(out, "P6\n%d %d\n%d\n", photo->m, photo->n, photo->maxval);
			for (int i = 0; i < photo->n; ++i) {
				for (int j = 0; j < photo->m; ++j) {
					unsigned char r, g, b;
					r = (unsigned char)photo->color[i][j].r;
					g = (unsigned char)photo->color[i][j].g;
					b = (unsigned char)photo->color[i][j].b;
					fwrite(&r, sizeof(unsigned char), 1, out);
					fwrite(&g, sizeof(unsigned char), 1, out);
					fwrite(&b, sizeof(unsigned char), 1, out);
				}
			}
		}
		fclose(out);
		printf("Saved %s\n", file);
	} else {
		printf("No image loaded\n");
	}
}