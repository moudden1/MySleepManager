all: example

gps.o: gps.c gps.h
	gcc -Wall -g -c gps.c -lwiringPi

example: example.c gps.o
	gcc -Wall -g -o $@ $^ -lwiringPi 

clean:
	rm example gps.o
