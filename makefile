# Makefile for APC project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRC = main.c multiplication.c subtraction.c division.c addition.c

# Object files
OBJ = $(SRC:.c=.o)

# Header file
DEPS = apc.h

# Output executable name
TARGET = apc_program

# Default target to build everything
all: $(TARGET)

# Rule to link object files into the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c to .o
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and executable
clean:
	rm -f *.o $(TARGET)

# Optional: Add a run target
run: $(TARGET)
	./$(TARGET)

# Phony targets to avoid conflict with file names
.PHONY: all clean run