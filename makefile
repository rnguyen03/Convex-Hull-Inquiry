CC=gcc
CFLAGS=-c -Wall -pedantic -std=c99
LIB=-lm

all: P11 P12 P21 P22

P11: P11.o
	$(CC) P11.o -o P11 $(LIB)

P11.o: P11.c
	$(CC) $(CFLAGS) -c P11.c 

P12: P12.o
	$(CC) P12.o -o P12 $(LIB)

P12.o: P12.c
	$(CC) $(CFLAGS) -c P12.c 

P21: P21.o
	$(CC) P21.o -o P21 $(LIB)

P21.o: P21.c
	$(CC) $(CFLAGS) -c P21.c

P22: P22.o
	$(CC) P22.o -o P22 $(LIB)

P22.o: P22.c
	$(CC) $(CFLAGS) -c P22.c 

clean:
	rm *.o P11 P12 P21 P22