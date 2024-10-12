<small>Copyright Tudor Brandibur 2023-2024 </small>

# Photo Editor

## Description
The program is a basic photo editor that is able to perform core
operations on a photo (select an area, crop, rotate, apply filters, equalize,
generate histogram);(.pgm, .ppm formats are supported).

## Functionality
The structure "image_t" stores the image as a matrix, its dimensions
(m, n), the coordonates of the selected area(x1, y1, x2, y2), the highest
pixle value in the matrix (maxval) and two pivotal flags, "is_col" and 
"is_mat," indicating whether a color or grayscale matrix is loaded. These 
flags never coexist, providing a binary distinction for matrix type.
	When running the program, it will read a command from stdin and apply
it.

## Functions

### LOAD \<file> (.ppm/.pgm)
Given a certain file name, the program will try to open it and, if it
succeeds, will allocate memory, load the photo using one of the four reading
functions(read_matrix_ASCII, read_matrix_BIN, read_color_ASCII, read_color_BIN)
depending on its type(P1, P2, P3 etc.) and close the file.

### SELECT \<x1> \<y1> \<x2> \<y2> /SELECT ALL
The SELECT function will select a certain area of the photo, depending
on the values given, which are stored in the variables x1, y1, x2, y2; SELLECT
ALL will select the whole photo.

### HISTOGRAM \<X> \<Y>
After reading the number of stars (X) and bins (Y) which can be used, this 
function will calculate a grayscale photo's histogram, using a frequency 
array. The number of stars is calculated using the given formula and then
the histogram is outputted to stdin.

### EQUALIZE
The function checks if the image is grayscale and then performs 
histogram equalization on the image. For each pixel, it calculates the
cumulative sum of frequencies up to the current pixel value, normalizes
the pixel value based on the cumulative sum and total area, and updates
the pixel value in the image.

### ROTATE \<angle>
Given a certain angle(only multiples of 90 < 360 supported), the
function will rotate the image or the square selection, using the function
"turn_left", which rotates an image by 90 degrees to the left.

### CROP
Using a temporary matrix(tmp), this function will copy the current 
selection and store it in tmp. Then it will swap the current matrix with
tmp, calling the function "matrix_swap"("matrix_swap_rgb" for color matrices),
and free the temporary matrix.

### APPLY \<filter>
This function applies a specific filter to the selected area(sharpen,
edge detection, blur or gaussian blur). It works only on color photos. A copy 
of the photo is made and then, the filter is applied only to the pixles in 
the selected area. The copy and the original photo are then swapped and the 
copy is freed.

### SAVE
This function takes user input for the file name and format, then saves
the image data to the specified file in either ASCII or binary mode depending
on the format. It supports both grayscale and color images. The function also 
prints a message indicating that the image has been saved.

### EXIT
All the memory is freed and the program closes.
