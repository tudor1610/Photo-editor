#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "photo.h"
#include "dimensions.h"

//makes the histogram
void histogram(image_t *photo)
{
	int star, bin, freq[256] = {0}, his[256] = {0}, fmax = 0;
	char buf[100], *p;
	fgets(buf, 100, stdin);
	p = strtok(buf, " ");
	if (!photo->is_mat && !photo->is_col) {
		printf("No image loaded\n");
		return;
	}
	if (p[0] != '\n') {
		star = char_to_int(p);
	} else {
		printf("Invalid command\n");
		return;
	}
	p = strtok(NULL, " ");
	if (p) {
		int len = strlen(p);
		p[len - 1] = '\0';
		bin = char_to_int(p);
		p = strtok(NULL, " ");
		if (p) {
			printf("Invalid command\n");
			return;
		}

	} else {
		printf("Invalid command\n");
		return;
	}
	if (photo->is_col) {
		printf("Black and white image needed\n");
		return;
	}
	for (int i = 0; i < photo->n; ++i) {
		for (int j = 0; j < photo->m; ++j)
			freq[photo->mat[i][j]]++;
	}
	if (bin < 256) {
		int k = 0, nr = 256 / bin;
		while (k < bin) {
			for (int i = 0; i < nr; ++i)
				his[k] += freq[k * nr + i];
			if (his[k] > fmax)
				fmax = his[k];
			k++;
		}
	} else if (bin == 256) {
		for (int i = 0; i < bin; ++i) {
			his[i] = freq[i];
			if (his[i] > fmax)
				fmax = his[i];
		}
	}
	for (int i = 0; i < bin; ++i) {
		long long nrs;
		nrs = his[i] * star / fmax;
		printf("%lld	|	", nrs);
		for (int j = 0; j < nrs; ++j)
			printf("*");
		printf("\n");
	}
}

//equalizes a black and white image
void equalize(image_t *photo)
{
	if (photo->is_col) {
		printf("Black and white image needed\n");
		return;
	}
	if (!photo->is_mat && !photo->is_col) {
		printf("No image loaded\n");
		return;
	}
	int freq[256] = {0};
	for (int i = 0; i < photo->n; ++i)
		for (int j = 0; j < photo->m; ++j)
			freq[photo->mat[i][j]]++;
	int area = photo->n * photo->m;
	for (int i = 0; i < photo->n; ++i) {
		for (int j = 0; j < photo->m; ++j) {
			int sum = 0;
			double f;
			for (int k = 0; k <= photo->mat[i][j]; k++)
				sum += freq[k];
			f = 255 * sum / area;
			if (f > 255)
				f = 255;
			photo->mat[i][j] = round(f);
		}
	}
	printf("Equalize done\n");
}

void edge(image_t *photo)
{
	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
	for (int i = 0; i < photo->n; ++i)
		for (int j = 0; j < photo->m; ++j) {
			tmp[i][j].r = photo->color[i][j].r;
			tmp[i][j].g = photo->color[i][j].g;
			tmp[i][j].b = photo->color[i][j].b;
		}
	for (int i = photo->y1; i < photo->y2; ++i)
		for (int j = photo->x1; j < photo->x2; ++j) {
			int r_sum = 0, g_sum = 0, b_sum = 0;
			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
				r_sum = photo->color[i][j].r * 8 - photo->color[i - 1][j - 1].r
				- photo->color[i - 1][j].r - photo->color[i - 1][j + 1].r -
				photo->color[i][j - 1].r - photo->color[i][j + 1].r -
				photo->color[i + 1][j - 1].r - photo->color[i + 1][j].r -
				photo->color[i + 1][j + 1].r;

				g_sum = photo->color[i][j].g * 8 - (photo->color[i - 1][j].g
				+ photo->color[i - 1][j - 1].g + photo->color[i - 1][j + 1].g +
				photo->color[i][j - 1].g + photo->color[i][j + 1].g +
				photo->color[i + 1][j - 1].g + photo->color[i + 1][j].g +
				photo->color[i + 1][j + 1].g);

				b_sum = photo->color[i][j].b * 8 - (photo->color[i - 1][j].b
				+ photo->color[i - 1][j - 1].b + photo->color[i - 1][j + 1].b +
				photo->color[i][j - 1].b + photo->color[i][j + 1].b +
				photo->color[i + 1][j - 1].b + photo->color[i + 1][j].b +
				photo->color[i + 1][j + 1].b);

				if (r_sum < 0)
					r_sum = 0;
				else if (r_sum > 255)
					r_sum = 255;
				if (g_sum < 0)
					g_sum = 0;
				else if (g_sum > 255)
					g_sum = 255;
				if (b_sum < 0)
					b_sum = 0;
				else if (b_sum > 255)
					b_sum = 255;
				tmp[i][j].r = r_sum;
				tmp[i][j].g = g_sum;
				tmp[i][j].b = b_sum;
			}
		}
	matrix_swap_rgb(&photo->color, &tmp);
	destroy_mat_COL(photo->n, tmp);
	printf("APPLY EDGE done\n");
}

void sharpen(image_t *photo)
{
	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
	for (int i = 0; i < photo->n; ++i)
		for (int j = 0; j < photo->m; ++j) {
			tmp[i][j].r = photo->color[i][j].r;
			tmp[i][j].g = photo->color[i][j].g;
			tmp[i][j].b = photo->color[i][j].b;
		}
	for (int i = photo->y1; i < photo->y2; ++i)
		for (int j = photo->x1; j < photo->x2; ++j) {
			int r_sum = 0, g_sum = 0, b_sum = 0;
			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
				r_sum = photo->color[i][j].r * 5 - photo->color[i - 1][j].r -
				photo->color[i][j - 1].r - photo->color[i][j + 1].r -
				photo->color[i + 1][j].r;

				g_sum = photo->color[i][j].g * 5 - photo->color[i - 1][j].g -
				photo->color[i][j - 1].g - photo->color[i][j + 1].g -
				photo->color[i + 1][j].g;

				b_sum = photo->color[i][j].b * 5 - photo->color[i - 1][j].b -
				photo->color[i][j - 1].b - photo->color[i][j + 1].b -
				photo->color[i + 1][j].b;
				if (r_sum < 0)
					r_sum = 0;
				else if (r_sum > 255)
					r_sum = 255;
				if (g_sum < 0)
					g_sum = 0;
				else if (g_sum > 255)
					g_sum = 255;
				if (b_sum < 0)
					b_sum = 0;
				else if (b_sum > 255)
					b_sum = 255;
				tmp[i][j].r = r_sum;
				tmp[i][j].g = g_sum;
				tmp[i][j].b = b_sum;
			}
		}
	matrix_swap_rgb(&photo->color, &tmp);
	destroy_mat_COL(photo->n, tmp);
	printf("APPLY SHARPEN done\n");
}

void blur(image_t *photo)
{
	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
	for (int i = 0; i < photo->n; ++i)
		for (int j = 0; j < photo->m; ++j) {
			tmp[i][j].r = photo->color[i][j].r;
			tmp[i][j].g = photo->color[i][j].g;
			tmp[i][j].b = photo->color[i][j].b;
		}
	for (int i = photo->y1; i < photo->y2; ++i)
		for (int j = photo->x1; j < photo->x2; ++j) {
			double r_sum = 0, g_sum = 0, b_sum = 0;
			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
				r_sum = (double)(photo->color[i][j].r +
				photo->color[i - 1][j - 1].r + photo->color[i - 1][j].r +
				photo->color[i - 1][j + 1].r + photo->color[i][j - 1].r +
				photo->color[i][j + 1].r + photo->color[i + 1][j - 1].r +
				photo->color[i + 1][j].r + photo->color[i + 1][j + 1].r) / 9;

				g_sum = (double)(photo->color[i][j].g +
				photo->color[i - 1][j - 1].g + photo->color[i - 1][j].g +
				photo->color[i - 1][j + 1].g + photo->color[i][j - 1].g +
				photo->color[i][j + 1].g + photo->color[i + 1][j - 1].g +
				photo->color[i + 1][j].g + photo->color[i + 1][j + 1].g) / 9;

				b_sum = (double)(photo->color[i][j].b +
				photo->color[i - 1][j - 1].b + photo->color[i - 1][j].b +
				photo->color[i - 1][j + 1].b + photo->color[i][j - 1].b +
				photo->color[i][j + 1].b + photo->color[i + 1][j - 1].b +
				photo->color[i + 1][j].b + photo->color[i + 1][j + 1].b) / 9;

				r_sum = round(r_sum);
				g_sum = round(g_sum);
				b_sum = round(b_sum);

				if (r_sum < 0)
					r_sum = 0;
				else if (r_sum > 255)
					r_sum = 255;
				if (g_sum < 0)
					g_sum = 0;
				else if (g_sum > 255)
					g_sum = 255;
				if (b_sum < 0)
					b_sum = 0;
				else if (b_sum > 255)
					b_sum = 255;
				tmp[i][j].r = r_sum;
				tmp[i][j].g = g_sum;
				tmp[i][j].b = b_sum;
			}
		}
	matrix_swap_rgb(&photo->color, &tmp);
	destroy_mat_COL(photo->n, tmp);
	printf("APPLY BLUR done\n");
}

void gaussian_blur(image_t *photo)
{
	rgb_t **tmp = alloc_col_mat(photo->n, photo->m);
	for (int i = 0; i < photo->n; ++i)
		for (int j = 0; j < photo->m; ++j) {
			tmp[i][j].r = photo->color[i][j].r;
			tmp[i][j].g = photo->color[i][j].g;
			tmp[i][j].b = photo->color[i][j].b;
		}
	for (int i = photo->y1; i < photo->y2; ++i)
		for (int j = photo->x1; j < photo->x2; ++j) {
			double r_sum = 0, g_sum = 0, b_sum = 0;
			if (i > 0 && i < photo->n - 1 && j > 0 && j < photo->m - 1) {
				r_sum = (double)(4 * photo->color[i][j].r +
				photo->color[i - 1][j - 1].r + 2 * photo->color[i - 1][j].r +
				photo->color[i - 1][j + 1].r + 2 * photo->color[i][j - 1].r +
				2 * photo->color[i][j + 1].r + photo->color[i + 1][j - 1].r +
				2 * photo->color[i + 1][j].r + photo->color[i + 1][j + 1].r) /
				16;

				g_sum = (double)(4 * photo->color[i][j].g +
				photo->color[i - 1][j - 1].g + 2 * photo->color[i - 1][j].g +
				photo->color[i - 1][j + 1].g + 2 * photo->color[i][j - 1].g +
				2 * photo->color[i][j + 1].g + photo->color[i + 1][j - 1].g +
				2 * photo->color[i + 1][j].g + photo->color[i + 1][j + 1].g) /
				16;

				b_sum = (double)(4 * photo->color[i][j].b +
				photo->color[i - 1][j - 1].b + 2 * photo->color[i - 1][j].b +
				photo->color[i - 1][j + 1].b + 2 * photo->color[i][j - 1].b +
				2 * photo->color[i][j + 1].b + photo->color[i + 1][j - 1].b +
				2 * photo->color[i + 1][j].b + photo->color[i + 1][j + 1].b) /
				16;

				r_sum = round(r_sum);
				g_sum = round(g_sum);
				b_sum = round(b_sum);

				if (r_sum < 0)
					r_sum = 0;
				else if (r_sum > 255)
					r_sum = 255;
				if (g_sum < 0)
					g_sum = 0;
				else if (g_sum > 255)
					g_sum = 255;
				if (b_sum < 0)
					b_sum = 0;
				else if (b_sum > 255)
					b_sum = 255;
				tmp[i][j].r = r_sum;
				tmp[i][j].g = g_sum;
				tmp[i][j].b = b_sum;
			}
		}
	matrix_swap_rgb(&photo->color, &tmp);
	destroy_mat_COL(photo->n, tmp);
	printf("APPLY GAUSSIAN_BLUR done\n");
}

//applies one of the for filters from above
void apply(image_t *photo)
{
	char buff[100], format[30], *p;
	fgets(buff, 100, stdin);
	p = strtok(buff, " ");
	strcpy(format, p);
	if (!photo->is_mat && !photo->is_col) {
		printf("No image loaded\n");
		return;
	}
	if (p[0] != '\n') {
		int len = strlen(format);
		format[len - 1] = '\0';
		if (photo->is_mat) {
			printf("Easy, Charlie Chaplin\n");
			return;
		} else if (!strcmp(format, "EDGE")) {
			edge(photo);
			return;
		} else if (!strcmp(format, "SHARPEN")) {
			sharpen(photo);
			return;
		} else if (!strcmp(format, "BLUR")) {
			blur(photo);
			return;
		} else if (!strcmp(format, "GAUSSIAN_BLUR")) {
			gaussian_blur(photo);
			return;
		} else if (!strcmp(format, "\n")) {
			printf("Invalid command\n");
			return;
		}
		printf("APPLY parameter invalid\n");
	} else {
		printf("Invalid command\n");
	}
}