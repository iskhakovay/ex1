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


typedef struct hacker_t{
    int hacker_id;
    int* desired_courses;
    int register_course_succsesful;
    int num_of_desired_courses;
}* Hacker;

typedef struct courses_t{
    int course_id;
    int size;
    int* enrollment_list; /** IMPORTANT*/
    int size_of_enrolment_list;
}* Courses;

typedef struct EnrollmentSystem_t{
    Student* students;
    int num_of_students;
    Hacker* Hackers;
    int num_of_hackers;
    Courses* ques;
    int num_of_ques;
}* EnrollmentSystem;




typedef  enum {HACK_ENROLLMENT_SUCCESS, HACK_ENROLLMENT_FAILED_READ_FILE,HACK_ENROLLMENT_MEMORY_FAIL} HackEnrollmentError;
//typedef struct EnrollmentSystem_t *EnrollmentSystem;

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);

void hackEnrollment(EnrollmentSystem sys, FILE* out);




#endif //EX1_HACKENROLLMENT_H
