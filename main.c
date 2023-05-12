#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "HackEnrollment.h"
//#include "capslock.h"
#include "Headers.h"


//#include "HackEnrollment.c"
//#include "getopt.h"
//#include "unistd.h"
//#include <sys/stat.h>

#define CAPSLOCK_ON  true
#define CAPSLOCK_OFF false
#define CHUNK_SIZE 256




int main(int argc, char** argv)//maybe char* argv
{
    printf("%d argc\n", argc);

    FILE* students;
    FILE *courses;
    FILE *hackers;
    FILE *out;
    FILE *queues;


    //int option;

    if( argc > 7 ) {
        printf("Too many arguments supplied.\n");
        return 0;
    }

    if (argc == 7)
    {
        printf("yhayy");
        if(strcmp(argv[1], "-i")== 0)
        {
            defineCapsLock(CAPSLOCK_OFF);
           //capslock = CAPSLOCK_OFF;
        } else
        {
            printf("unknown option: %s\n", argv[1]);
        }


            students = fopen(argv[2],"r");
            courses = fopen(argv[3],"r");
            hackers = fopen(argv[4],"r");
            queues = fopen(argv[5],"r");
            out = fopen(argv[6],"w");
    }
    //printf("yhayy");

    if (argc == 6)
    {
        printf("yhayy\n");
        fflush(stdout);
        students = fopen(argv[1],"r");
        courses = fopen(argv[2],"r");
        hackers = fopen(argv[3],"r");
        queues = fopen(argv[4],"r");
        out = fopen(argv[5],"w");

        printf("nhayy\n");
        //fflush(stdout);
    }

    if( argc < 6 ) {
        printf("not enough arguments supplied.\n");
        return 0;
    }
    if(students==NULL || courses == NULL || hackers == NULL){
        printf("input files problem");
    }
    printf("before hack");
    char srr[10];
    fscanf(students,srr);
    printf("%s",srr);
    fflush(stdout);
    EnrollmentSystem sys = createEnrollment(students, courses, hackers);
    sys = readEnrollment(sys, queues);
    hackEnrollment(sys, out);


    fclose(out);
    fclose(students);
    fclose(courses);
    fclose(hackers);
    fclose(queues);



/*

    // put ':' at the starting of the string so compiler can distinguish between '?' and ':'
    int i = 1;
    capslock = CAPSLOCK_ON;
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

    for(int j = optind; j<argc;j++){
        if(i == 1){
            students = fopen(argv[j],"r");
            //fclose(students);
        }
        if(i == 2){
            courses = fopen(argv[j],"r");
            //fclose(courses);
        }
        if(i == 3){
            hackers = fopen(argv[j],"r");
            //fclose(hackers);
        }
        if(i == 4){
            queues = fopen(argv[j],"r");
            //fclose(queues);
        }
        if(i == 5){
            target = fopen(argv[j],"r");
            // fclose(target);
        }
        i++;
    }*/
}
