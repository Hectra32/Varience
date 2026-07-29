CC = gcc

CFLAGS = -Iinclude -g -I/usr/include/SDL2 -D_REENTRANT
LIBS = -lSDL2 -lSDL2_ttf

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = out


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)
