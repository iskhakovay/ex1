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

int read_string(FILE* stream, char* str,char stop_char ,int num_of_stops);

void read_arr_of_strings(FILE* stream, int* arr);


void get_to_next_line(FILE* stream);

int get_number_of_lines (FILE* file);

void skip_credits_and_gpa(FILE* stream);

/*
typedef struct node{
    int data;
    struct  node* next;
    int friendship;
    int rival;
}*Node;

typedef struct Queue{
    Node front;
    Node rear;
    int count;
} * Queue;
*/
typedef struct student_t{
    char* name;
    int student_id;
}* Student;

typedef struct hacker_t{
    int hacker_id;
    int* desired_courses;
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

void read_courses_from_file(FILE* courses, int num_of_courses, EnrollmentSystem system);

void read_hackers_from_file(FILE* hackers, int num_of_hackers, EnrollmentSystem system);


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
    Courses * courses_arr = malloc(num_of_courses*sizeof (Courses));
    system->ques = courses_arr;
    read_courses_from_file(courses,num_of_courses,system);


    int num_of_hackers = get_number_of_lines(hackers)/4;
    Hacker * hacker_arr = malloc(num_of_hackers * sizeof (Hacker));
    system->Hackers = hacker_arr;
    read_hackers_from_file(hackers,num_of_hackers, system);
}


EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues)                                                        //TODO read hackers and ect
{
    int num_of_queues = get_number_of_lines(queues);
    for (int i = 0; i < num_of_queues; ++i)
    {
        //get course number id
        char* course_id_temp = malloc(sizeof (char));
        read_string(queues, course_id_temp, ' ',1);
        int current_course_id=  = atoi(course_id_temp);
        free(course_id_temp);

        // find course id in courses arr in system
        while (current_course_id != sys ->ques)
        {



        }




    }


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
        int name_len_temp = read_string(students, name_temp, ' ',2);


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

void read_courses_from_file(FILE* courses, int num_of_courses, EnrollmentSystem system)
{
    if(courses = fopen(courses,'r') == NULL )
    {
        //HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    for (int i= 0; i < num_of_courses; i++)
    {

        char* course_id_temp = malloc(sizeof (char));
        read_string(courses, course_id_temp, ' ',1);
        Courses course_temp;
        course_temp ->course_id = atoi(course_id_temp);
        free(course_id_temp);

        char* course_size_temp = malloc(sizeof (char));
        read_string(courses, course_id_temp, '\n',1);
        course_temp ->size =  atoi(course_size_temp);
        free(course_size_temp);

        system ->ques[i]= course_temp;

        get_to_next_line(courses);

    }
    fclose(courses);
    return;



}

//------------------------------------------------

void read_hackers_from_file(FILE* hackers, int num_of_hackers, EnrollmentSystem system)
{
    if(hackers = fopen(hackers,'r') == NULL )
    {
        //HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    for (int i= 0; i < num_of_hackers; i++)
    {
        Hacker hacker_temp;

        //read hacker id
        char id_temp[ID_SIZE]="";
        fgets(id_temp[0], ID_SIZE, hackers);
        hacker_temp->hacker_id = atoi(id_temp);

        char trash ="";
        fgets(trash, 1, hackers);

        //read desired courses
        int* desired_courses_temp= malloc(sizeof (int));
        read_arr_of_strings(hackers,desired_courses_temp);
        hacker_temp->desired_courses = desired_courses_temp;

        //read friends courses
        int* friends_temp= malloc(sizeof (int));
        read_arr_of_strings(hackers,friends_temp);
        hacker_temp->friends = friends_temp;

        //read rivals courses
        int* rivals_temp= malloc(sizeof (int));
        read_arr_of_strings(hackers,rivals_temp);
        hacker_temp->rivals = rivals_temp;

    }
    fclose(hackers);
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


int read_string(FILE* stream, char* str,char stop_char ,int num_of_stops)
{
    char char_temp = "";
    int i = 1;
    while (num_of_stops > 0 )
    {
        i++;
        fgets(char_temp, 1, stream);
        str = realloc(str, i * sizeof(char));
        str[i]= char_temp;
        if (char_temp == stop_char)
        {
            num_of_stops--;
        }
    }
    return i;
}
//------------------------------------------------
void read_arr_of_strings(FILE* stream, int* arr)
{

    char char_temp = "";
    int j = 0;

    while (char_temp != '/n')
    {
        char* str_temp = malloc(sizeof (char));
        int i = 1;
        fgets(char_temp, 1, stream);
        str_temp[0]= char_temp;
        while (char_temp != ' ')
        {
            i++;
            fgets(char_temp, 1, stream);
            str_temp = realloc(str_temp, i * sizeof(char));
            str_temp[i]= char_temp;
        }
        arr = realloc(arr, (j+1)*sizeof (int));
        arr[j]= atoi(str_temp);
        free( str_temp);
    }

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