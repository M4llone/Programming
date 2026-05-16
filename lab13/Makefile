CFLAGS = -Wall -Wextra -std=c99

all: sorted

sorted: src/main.o src/smarthome.o
	gcc src/main.o src/smarthome.o -o sorted -lm

main.o: src/main.c
	gcc $(CFLAGS) -c src/main.c -o src/main.o

smarthome.o: smarthome.c
	gcc $(CFLAGS) -c src/smarthome.c -o src/smarthome.o

dinamic: src/main.o src/smarthome.o
	gcc --shared src/main.o src/smarthome.o -o libMY_LOG.so
	gcc src/main.o -o dynamic_exe -L. -lMY_LOG -Wl,-rpath,.
	./dynamic_exe

static: src/main.o src/smarthome.o
	ar rc libMY_LOG.a src/smarthome.o
	gcc src/main.o -o static_exe -L. -lMY_LOG
	./static_exe

clear:
	rm -rf *.o *.a *.so sorted dynamic_exe static_exe