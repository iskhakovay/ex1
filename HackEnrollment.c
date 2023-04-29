#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"

//------------------------------------------------
//mini functions declaration:
/**
cheks to see [ASCII value of Name1] - [ASCII value of Name2]

Parameters :
----------
- name1 : CHAR*
the first name.

- name2 : CHAR*
the secont name.

Returns :
--------
- res: int
absolte value of reulte.
*/
int Name_distence (char* name1, char* name2);

//------------------------------------------------

typedef struct enrollment_system{
    char* Student_ID;
    int Total_Credits;
    int GPA;
    char* Name;
    char* Surname;
    char* City;
    char* Department;
    int Course_Number;
}*EnrollmentSystem;

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{
    if((FILE* students_file = fopen(students, r)) == NULL)
    {
        return NULL;
    }



}