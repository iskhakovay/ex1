CC = gcc
OBJS = main.o HackEnrollment.o IsraeliQueues.o
EXEC = my_program
DEBUG_FLAG =
COMP_FLAG = -std=c99 -Wall -Wextra -Werror
INC_FLAG = -I.

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

main.o: main.c HackEnrollment.h Headers.h IsraeliQueue.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(INC_FLAG) main.c -o main.o

HackEnrollment.o: HackEnrollment.c HackEnrollment.h IsraeliQueue.h Headers.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(INC_FLAG) HackEnrollment.c -o HackEnrollment.o

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h Headers.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(INC_FLAG) IsraeliQueues.c -o IsraeliQueues.o

clean:
	rm -f $(OBJS) $(EXEC)