#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"
#include "IsraeliQueue.h"

#define ID_SIZE 9

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

- caps_lock : BOOL
true- 'A' != 'a'
false- 'A' == 'a'

Returns :
--------
- res: INT
absolute value of result.
*/
int Name_distance (char* name1, char* name2, bool caps_lock);

/**
sums up ASCII value of string

Parameters :
----------
- str : CHAR*
the string.

- caps_lock : BOOL
true- 'A' != 'a'
false- 'A' == 'a'

Returns :
--------
- sum: int
ASCII value of string.
*/
int str_ASCII_value(char* str, bool caps_lock);

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

int read_name(FILE* students, char* name);

void get_to_next_line(FILE* stream);

int get_number_of_lines (FILE* file);


//------------------------------------------------
//big mini functions declaration:
Student read_student_from_file(FILE* students);


//------------------------------------------------
typedef struct student_t{
    char* name;
    int student_id;
}* Student;

typedef struct hacker_t{
    int student_id;
    int* friends;
    int* rivals;
}* Hacker;

typedef struct courses_t{
    int course_id;
    int size;
    struct Student* enrollment_list;
}* Courses;

typedef struct EnrollmentSystem_t{
    struct Student* students;
    struct Courses* ques;
}* EnrollmentSystem;

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{
    EnrollmentSystem  system;
    int num_of_students = get_number_of_lines(students);
    system->students = malloc(num_of_students * sizeof (Student));

    for (int i= o; i < num_of_students; i++)
    {
        system->students[i] =  read_student_from_file(students);
    }


    int num_of_courses = get_number_of_lines(courses);















 /*   if(students = fopen(students,'r') == NULL ||
            )
    {
        return HACK_ENROLLMENT_FAILED_READ_FILE;
    }*/



}


EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues)
{

}


void hackEnrollment(EnrollmentSystem sys, FILE* out)
{

}
------------------------------------------------
//big mini functions:
Student read_student_from_file(FILE* students)
{
    char[ID_SIZE] id_temp = "";
    char[TOTAL_CRADIT_GPA_SIZE] total_cradit_gpa_temp = "";

    fgets(id_temp, ID_SIZE, students);
    fgets(total_cradit_gpa_temp, TOTAL_CRADIT_GPA_SIZE, students);

    char * name_temp = malloc(sizeof (char));
    int name_len_temp = read_name(students, name_temp);

    Student student_temp;
    student_temp.name[name_len_temp]= name_temp;
    student_temp.student_id = atoi(id_temp);

    get_to_next_line(students);
    return student_temp;
}




//------------------------------------------------
//mini functions:

int get_number_of_lines (FILE* file)
{
    int lines_counter = 0;
    char char_temp = "";
    fgets(char_temp, 1, file);
    while (chr != EOF)
    {
        if (chr == '\n')
        {
            lines_counter++;
        }
        fgets(char_temp, 1, file);
    }
    return lines_counter;
}


}

int read_name(FILE* students, char* name)
{
    char char_temp = "";
    int i = 1;
    while (char_temp != " ")
    {
        i++;
        fgets(char_temp, 1, students);
        realloc(name, i * sizeof(char));
        name[i]= char_temp;
    }
    return i;
}

void get_to_next_line(FILE* stream)
{
    char char_temp = "";
    while (char_temp != "\n")
    {
        fgets(char_temp, 1, stream);

    }
    return;
}

int Name_distance (char* name1, char* name2, bool caps_lock)
{
    int res = str_ASCII_value(name1, caps_lock) - str_ASCII_value(name2, caps_lock);
    return (res >= 0) ? res : (res * (-1));
}

int str_ASCII_value(char* str, bool caps_lock)
{
    if (caps_lock)
    {
        int len = strlen(str);
        int sum =0;
        for (int i=0; i< len; i++)
        {
            if (!caps_lock)
            {
                if (str[i] >= 'A' && str[i]<= 'a')
                {
                    sum += str[i] -'A';
                }
                else
                {
                    sum += str[i] -'a';
                }
            }
            sum += str[i];
        }
        return sum;
    }
    else
    {
        int len = strlen(str);
        int sum =0;
        for (int i=0; i< len; i++)
        {

            sum += str[i];
        }
        return sum;
    }

}

int student_id_difference(char* id1,char* id2)
{
    int res = atoi(id1)- atoi(id2);
    return (res >= 0) ? res : (res * (-1));

}

//------------------------------------------------