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
