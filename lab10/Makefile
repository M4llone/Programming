CFLAGS = -Wall -Wextra -std=c99

all: conus

conus: main.o def.o
	gcc main.o def.o -o conus -lm

main.o: main.c
	gcc -c main.c

def.o: def.c
	gcc -c def.c

clean:
	rm -rf *.o conus

