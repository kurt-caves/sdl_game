CC = gcc
CFLAGS = -Wall -std=c99 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2_image -lSDL2_ttf -lm

SRCS = src/main.c \

OBJS = $(SRCS:.c=.o)
TARGET = game

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)