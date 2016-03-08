all: bug

bug: main.c example.h bug.c
	cc -o bug -W -Wall -pedantic -std=c99 bug.c main.c -lglfw -lGL

clean:
	rm -f bug
