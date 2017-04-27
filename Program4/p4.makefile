CC = gcc
CFLAGS = -std=c99 -g -Wall
LIB = /home/ff/cs9c/lib
animal1 : animal1.o $(LIB)/p4.o
	$(CC) $(CFLAGS) -o animal1 animal1.o $(LIB)/p4.o
animal2  : animal2.o $(LIB)/p4.o
	$(CC) $(CFLAGS) -o animal2  animal2.o $(LIB)/p4.o
animal1.o : animal1.c animal.h
animal2.o : animal2.c animal.h
c.animal1 : animal1.c $(LIB)/p4.c
	#load $(CFLAGS) animal1.c $(LIB)/p4.c
c.listtest : animal2.c $(LIB)/p4.c
	#load $(CFLAGS) animal2.c $(LIB)/p4.c