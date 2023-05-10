#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"
#include "HackEnrollment.c"
#include "getopt.h"
#include "unistd.h"
#include <sys/stat.h>

#define CAPSLOCK_ON  true
#define CAPSLOCK_OFF false
#define CHUNK_SIZE 256


int main(int argc, char** argv)//maybe char* argv
{
    bool capslock;
    FILE* students;
    FILE *courses;
    FILE *hackers;
    FILE *target;
    FILE *queues;
    int option;
    if( argc > 6 ) {
        printf("Too many arguments supplied.\n");
    }
    // put ':' at the starting of the string so compiler can distinguish between '?' and ':'
    int i =0;
    while ((option = getopt(argc, argv, ":if:i")) != -1) { //get option from the getopt() method
        switch (option) {
            //For option i, r, l, print that these are options
            case 'i':
                capslock = CAPSLOCK_OFF;
                break;
            case ':':
                break;
            case '?': //used for some unknown options
                printf("unknown option: %c\n", optopt);
                break;
        }


    }
    while(i<6){
        if(i == 1){
            students = fopen(argv[1],"r");
            fclose(students);
        }
        if(i == 2){
            courses = fopen(argv[2],"r");
            fclose(courses);
        }
        if(i == 3){
            hackers = fopen(argv[3],"r");
            fclose(hackers);
        }
        if(i == 4){
            queues = fopen(argv[4],"r");
            fclose(queues);
        }
        if(i == 5){
            target = fopen(argv[5],"r");
            fclose(target);
        }
        i++;
    }
    EnrollmentSystem sys =createEnrollment(students, courses, hackers);
    sys =readEnrollment(sys, queues);
    hackEnrollment(sys, target);



}
