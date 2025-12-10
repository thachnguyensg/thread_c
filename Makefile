TARGET = bin/tp

SRC = $(wildcard src/*.c)

CFLAGS = -Iinc

build: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	gcc $(CFLAGS) -o $@ $^


