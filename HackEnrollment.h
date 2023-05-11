#ifndef EX1_HACKENROLLMENT_H
#define EX1_HACKENROLLMENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Headers.h"






// i guess it should be here


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


/**
Creates an enrollment system by reading student, course, and hacker info from three different files.

Parameters:
-----------
 * @param students : FILE*
a pointer to a file that contains student info.

 * @param courses
a pointer to a file that contains course information

 * @param hackers
a pointer to a file that contains hacker information.


Returns:
--------
 * @return :pointer to the created `EnrollmentSystem`.
 */
EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

/**
Reads queues info from a file and updates the enrollment lists for each course in the enrollment system.

Parameters:
-----------
 * @param sys : EnrollmentSystem
 * @param queues : FILE*

 Returns:
--------
 * @return :The updated enrollment system.
 */
EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);


/**
attempts to enroll hackers into courses according to their preferences, and prints the resulting course queues to
 out file.
the way it works:
1. creates an array of "IsraeliQueue", each representing a course.
2. it turns the enrollment lists for each course into an IsraeliQueue.
3. it enrolls the hackers in the appropriate courses using the IsraeliQueue data structure.
4. iterates over the hackers and attempts to enroll them in their desired courses.
If successful, it prints the new queues and returns. Otherwise, it prints an error message and exits.

 Parameters:
-----------
 * @param sys : EnrollmentSystem
 * @param out : FILE*

 Returns:
--------
 NONE
 */
void hackEnrollment(EnrollmentSystem sys, FILE* out);




#endif //EX1_HACKENROLLMENT_H
