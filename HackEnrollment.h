#ifndef EX1_HACKENROLLMENT_H
#define EX1_HACKENROLLMENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool capslock;

// i guess it should be here
typedef struct student_t{
    char* name;
    int student_id;
    int* friends;
    int num_of_friends;
    int* rivals;
    int num_of_rivals;

}* Student;

typedef  enum {HACK_ENROLLMENT_SUCCESS, HACK_ENROLLMENT_FAILED_READ_FILE,HACK_ENROLLMENT_MEMORY_FAIL} HackEnrollmentError;
typedef struct EnrollmentSystem_t *EnrollmentSystem;

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);

void hackEnrollment(EnrollmentSystem sys, FILE* out);




#endif //EX1_HACKENROLLMENT_H
