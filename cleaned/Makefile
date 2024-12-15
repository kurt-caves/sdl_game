CC = gcc
CFLAGS = -Wall -std=c99 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2_image -lm

SRCS = src/main.c \
       src/game_state.c \
       src/graphics.c \
       src/input.c \
	   src/game.c \
       src/main_character.c

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