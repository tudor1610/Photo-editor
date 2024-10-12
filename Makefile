# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Target executable name
TARGET = image_editor

# List of object files (note the lowercase 'o' in dimensions.o)
OBJS = image_editor.o photo.o filters.o dimensions.o

# Default target, which builds the program
all: $(TARGET)

# Rule to compile photo.c into photo.o
photo.o: photo.c photo.h
	$(CC) $(CFLAGS) -c photo.c

# Rule to compile filters.c into filters.o
filters.o: filters.c filters.h
	$(CC) $(CFLAGS) -c filters.c

# Rule to compile dimensions.c into dimensions.o
dimensions.o: dimensions.c dimensions.h
	$(CC) $(CFLAGS) -c dimensions.c

# Rule to compile image_editor.c into image_editor.o
image_editor.o: image_editor.c photo.h filters.h dimensions.h
	$(CC) $(CFLAGS) -c image_editor.c

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
