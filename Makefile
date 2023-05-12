CC = gcc
OBJS = main.o HackEnrollment.o IsraeliQueue.o
EXEC = HackEnrollment
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

main.o : main.c HackEnrollment.h capslock.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

HackEnrollment.o : HackEnrollment.c HackEnrollment.h IsraeliQueue.h Headers.h capslock.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

IsraeliQueue.o : IsraeliQueue.c IsraeliQueue.h Headers.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)