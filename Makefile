CC = gcc
OBJS = main.o HackEnrollment.o IsraeliQueues.o
EXEC = HackEnrollment
DEBUG_FLAG =
COMP_FLAG = -std=c99 -Wall -Wextra -Werror

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

main.o: main.c HackEnrollment.h headers.h IsraeliQueues.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) main.c -o main.o

HackEnrollment.o: HackEnrollment.c HackEnrollment.h IsraeliQueues.h headers.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) HackEnrollment.c -o HackEnrollment.o

IsraeliQueues.o: IsraeliQueues.c IsraeliQueues.h headers.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) IsraeliQueues.c -o IsraeliQueues.o

clean:
	rm -f $(OBJS) $(EXEC)