
all: HackEnrollment

HackEnrollment: main.o HackEnrollment.o IsraeliQueue.o
	gcc main.o HackEnrollment.o IsraeliQueue.o -o HackEnrollment

main.o: main.c HackEnrollment.h IsraeliQueue.h
	gcc -c main.c

HackEnrollment.o: HackEnrollment.c HackEnrollment.h IsraeliQueue.h
	gcc -c HackEnrollment.c

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h
	gcc -c IsraeliQueue.c

clean:
	rm -f *.o HackEnrollment