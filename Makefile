# Make File
# Varience

CC = gcc

CFLAGS = -Iinclude -g -D_REENTRANT
LIBS = -lSDL2 -lSDL2_ttf

FONT_SOURCE = src/font.c
FONT_SCRIPT = files/font/build_font.sh
FONT_FILES = $(wildcard files/font/*.ttf)

SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

TARGET = Varience

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

$(FONT_SOURCE): $(FONT_SCRIPT) $(FONT_FILES)
	./$(FONT_SCRIPT)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
