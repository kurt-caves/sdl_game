# Compiler
CC = gcc

# Compiler flags
CFLAGS = -I/opt/homebrew/include

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image

# Source files
SRC = src/main.c

# Object files
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = game

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean rule to remove generated files
clean:
	rm -f $(OBJ) $(TARGET)