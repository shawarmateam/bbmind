all: build

build:
	mkdir -p bin
	gcc src/main.c -o bin/bbmind

run: build
	./bin/bbmind
