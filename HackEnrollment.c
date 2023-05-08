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

int read_name(FILE* students_stream, char* name);

void get_to_next_line(FILE* stream);

int get_number_of_lines (FILE* file);

void skip_credits_and_gpa(FILE* stream);

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
    Student* students;
    Hacker* Hackers;
    Courses* ques;
}* EnrollmentSystem;



//------------------------------------------------
//big mini functions declaration:
void read_student_from_file(FILE* students, int num_of_students, EnrollmentSystem system);


//------------------------------------------------

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{
    EnrollmentSystem  system;

    int num_of_students = get_number_of_lines(students);
    Student* students_arr = malloc(num_of_students*sizeof (Student));
    system->students = students_arr;
    read_student_from_file(students, num_of_students, system);

    //TODO hackers and ques


    int num_of_courses = get_number_of_lines(courses);


}


EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues)                                                        //TODO read hackers and ect
{

}//TODO


void hackEnrollment(EnrollmentSystem sys, FILE* out)
{

}//TODO
//------------------------------------------------
//big mini functions:
void read_student_from_file(FILE* students, int num_of_students, EnrollmentSystem system)
{
    if(students = fopen(students,'r') == NULL )
    {
        //HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    for (int i= 0; i < num_of_students; i++)
    {
        char id_temp[ID_SIZE]="";

        fgets(id_temp[0], ID_SIZE, students);
        skip_credits_and_gpa(students);


        char* name_temp = malloc(sizeof (char));
        int name_len_temp = read_name(students, name_temp);


        Student student_temp;
        student_temp->name[name_len_temp]= name_temp;

        free(name_temp);

        student_temp->student_id = atoi(id_temp);
        system->students[i] = student_temp;

        get_to_next_line(students);

    }
    fclose(students);
    return;



}




//------------------------------------------------
//mini functions:

int get_number_of_lines (FILE* file )
{
    if(file = fopen(file,'r') == NULL )
    {
        return HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    int lines_counter = 0;
    char char_temp = '\0';
    fgets(char_temp, 1, file);
    while (char_temp != EOF)
    {
        if (char_temp == '\n')
        {
            lines_counter++;
        }
        fgets(char_temp, 1, file);
    }
    fclose( file);
    return lines_counter;
}


//------------------------------------------------


int read_name(FILE* students_stream, char* name)
{
    char char_temp = "";
    int i = 1;
    int num_of_spaces = 2;
    while (num_of_spaces > 0 )
    {
        i++;
        fgets(char_temp, 1, students_stream);
        name = realloc(name, i * sizeof(char));
        name[i]= char_temp;
        if (char_temp == " ")
        {
            num_of_spaces--;
        }
    }
    return i;
}
//------------------------------------------------

void skip_credits_and_gpa(FILE* stream)
{
    char char_temp = "";
    int num_of_spaces = 3;
    while (num_of_spaces > 0 )
    {
        fgets(char_temp, 1, stream);
        if (char_temp == " ")
        {
            num_of_spaces--;
        }
    }
    return;

}



void get_to_next_line(FILE* stream)
{
    char char_temp = "";
    while (char_temp != '\n')
    {
        fgets(char_temp, 1, stream);

    }
    return;
}
//------------------------------------------------


int Name_distance (char* name1, char* name2, bool caps_lock)
{
    int res = str_ASCII_value(name1, caps_lock) - str_ASCII_value(name2, caps_lock);
    return (res >= 0) ? res : (res * (-1));
}
//------------------------------------------------


int str_ASCII_value(char* str, bool caps_lock) //TODO
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
//------------------------------------------------


int student_id_difference(char* id1,char* id2)
{
    int res = atoi(id1)- atoi(id2);
    return (res >= 0) ? res : (res * (-1));

}

//------------------------------------------------