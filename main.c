#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"
#include "HackEnrollment.c"
#include "getopt.h"
#include "unistd.h"

#define CAPSLOCK_ON  true
#define CAPSLOCK_OFF false

bool checkInputFiles(char** argv, int argc);
int main(int argc, char** argv)//maybe char* argv
{
    bool capslock = checkInputFiles(argv,argc);
    FILE* students, courses, hackers, target,queues;
    students = argv[0];
    int option;
    // put ':' at the starting of the string so compiler can distinguish between '?' and ':'
    for(int i = 0; i<argc; i++) {
        while ((option = getopt(argc, &argv[i], ":if:i")) != -1) { //get option from the getopt() method
            switch (option) {
                //For option i, r, l, print that these are options
                case 'i':
                    capslock = CAPSLOCK_OFF;
                    break;
                case 'f':
                    if(i == 0){

                    }
                    printf("Given File: %s\n", optarg);
                    break;
                case ':':
                    printf("option needs a value\n");
                    break;
                case '?': //used for some unknown options
                    printf("unknown option: %c\n", optopt);
                    break;
            }
        }
    }
    //EnrollmentSystem sys =createEnrollment(argv[1], courses, hackers);
    //sys =readEnrollment(sys, queues);
    //hackEnrollment(sys, FILE* out);



}
bool checkInputFiles(char** argv, int argc){ //checks files and returns if capslock true
    FILE* file_handler;
    if(argc>6){
        printf("Too many arguments");
    }
    for(int i = 0; i < argc; i++) {
        if ((((file_handler) = fopen(argv[i], "r")) == NULL)){
            printf("No file supplied");
        }
        fclose(file_handler);
    }
    if(argc>5){
        if(strcmp(argv[0],"-i")==0){
            return CAPSLOCK_OFF;
        }
    }
    return CAPSLOCK_ON;

}

