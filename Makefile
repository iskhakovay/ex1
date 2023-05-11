
CC = gcc
CFLAGS = -Wall -g

all: HackEnrollment

HackEnrollment: main.o IsraeliQueue.o HackEnrollment.o
	$(CC) $(CFLAGS) main.o IsraeliQueue.o HackEnrollment.o -o HackEnrollment

main.o: main.c capslock.h HackEnrollment.h
	$(CC) $(CFLAGS) -c main.c

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h Headers.h
	$(CC) $(CFLAGS) -c IsraeliQueue.c

HackEnrollment.o: HackEnrollment.c HackEnrollment.h IsraeliQueue.h capslock.h
	$(CC) $(CFLAGS) -c HackEnrollment.c

clean:
	rm -f *.o HackEnrollment


