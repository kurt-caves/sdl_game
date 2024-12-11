# 12/6/24
# source https://github.com/tlively/sdl_seminar/blob/master/Makefile


# compiler were using
CC = clang
# compiler flags
CFLAGS = -I/opt/homebrew/include/SDL2 -lSDL2_image -lm
# linker flags
LDFLAGS = -L/opt/homebrew/lib -lSDL2

# header files
HDRS :=

# source files
SRCS := hello3_sdl.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := game

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean