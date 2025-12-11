TARGET = bin/tp

SRC = $(wildcard src/*.c)

CFLAGS = -Iinc

run: build
	./$(TARGET)

build: $(TARGET)

clean:
	rm -rf bin

$(TARGET): $(SRC)
	@mkdir -p bin
	gcc $(CFLAGS) -o $@ $^


