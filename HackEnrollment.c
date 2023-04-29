#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"

//------------------------------------------------
//mini functions declaration:
/**
checks to see the absolute difference between [ASCII value of Name1] - [ASCII value of Name2]
Parameters :
----------
- name1 : CHAR*
the first name.

- name2 : CHAR*
the second name.

Returns :
--------
- res: INT
absolute value of result.
*/
int Name_distance (char* name1, char* name2);

/**
sums up ASCII value of string

Parameters :
----------
- str : CHAR*
the string.

Returns :
--------
- sum: int
ASCII value of string.
*/
int str_ASCII_value(char* str);

/**
converts id1, and id2 from string to ints and
checks to see the absolute difference.

Parameters :
----------
- id1 : CHAR*

- id2 : CHAR*

Returns :
--------
- res: INT
absolute value of result.
*/
int student_id_difference(char* id1,char* id2);


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


EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues)
{

}


void hackEnrollment(EnrollmentSystem sys, FILE* out)
{

}

//------------------------------------------------
//mini functions:
int Name_distance (char* name1, char* name2)
{
    int res = str_ASCII_value(name1) - str_ASCII_value(name2);
    return (res >= 0) ? res : (res * (-1));
}

int str_ASCII_value(char* str)
{
    int len = strlen(str);
    int sum =0;
    for (int i=0; i< len; i++)
    {
        sum += str[i];
    }
    return sum;
}

int student_id_difference(char* id1,char* id2)
{
    int res = atoi(id1)- atoi(id2);
    return (res >= 0) ? res : (res * (-1));

}

//------------------------------------------------