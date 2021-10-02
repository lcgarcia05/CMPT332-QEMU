CC = gcc
CFLAGS = -g
CPPFLAGS = -Wall -pedantic

target: wrdsh

wrdsh:	wrdsh.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o wrdsh wrdsh.o

wrdsh.o:	wrdsh.c
	$(CC) $(CFLAGS) -o wrdsh.o -c $(CPPFLAGS) wrdsh.c


.PHONY: clean

clean:
	rm -f wrdsh.o
	rm -f wrdsh
