#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"
#include "IsraeliQueue.h"
#include "IsraeliQueue.c"

#define ID_SIZE 9
#define FRIEND 20
#define RIVAL -20
#define NEUTRAL 0
#define FRIENDSHIP_TH 20
#define RIVALRY_TH 0

const bool capslock = true;







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
    int num_of_desired_courses;
    int* friends;
    int* rivals;
}* Hacker;

typedef struct courses_t{
    int course_id;
    int size;
    int* enrollment_list; /** IMPORTANT*/
}* Courses;

typedef struct EnrollmentSystem_t{
    Student* students;
    int num_of_students;
    Hacker* Hackers;
    int num_of_hackers;
    Courses* ques;
    int num_of_ques;
}* EnrollmentSystem;

//------------------------------------------------
//mini functions declaration:



int read_string(FILE* stream, char* str,char stop_char ,int num_of_stops);

int read_arr_of_strings(FILE* stream, int* arr);//return len


void get_to_next_line(FILE* stream);

int get_number_of_lines (FILE* file, char* file_name);

void skip_credits_and_gpa(FILE* stream);

int find_course_index_in_system ( int current_course_id, EnrollmentSystem sys);

//------------------------------------------------
//big mini functions declaration:
void read_student_from_file(FILE* students, int num_of_students, EnrollmentSystem system);

void read_courses_from_file(FILE* courses, int num_of_courses, EnrollmentSystem system);

void read_hackers_from_file(FILE* hackers, int num_of_hackers, EnrollmentSystem system);


//------------------------------------------------
//the power of friendship (functions) !!!!

/**

checks to see the absolute difference.

Parameters :
----------
- id1 : int*

- id2 : int*

Returns :
--------
- res: INT
absolute value of result.
*/
int student_id_difference(int* id1,int* id2);

/**
checks to see the absolute difference between [ASCII value of Name1] - [ASCII value of Name2]
Parameters :
----------
- name1 : CHAR*
the first name.

- name2 : CHAR*
the second name.

- caps_lock : const BOOL
defult- true- 'A' != 'a'
false- 'A' == 'a'
 gets changed as flag in begining.

Returns :
--------
- res: INT
absolute value of result.
*/
int Name_distance (char* name1, char* name2);

int check_hacker_file_friend_status(EnrollmentSystem sys, int hacker_id, int student_id );



// help for friends
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





//------------------------------------------------

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{

    EnrollmentSystem  system;
    system = malloc(sizeof (EnrollmentSystem)); /** IMPORTANT*/

    int num_of_students = get_number_of_lines(students, "students.txt");
    Student* students_arr = malloc(num_of_students*sizeof (Student));
    system->students = students_arr;
    read_student_from_file(students, num_of_students, system);
    system->num_of_students = num_of_students;


    int num_of_courses = get_number_of_lines(courses,"courses.txt");
    Courses * courses_arr = malloc(num_of_courses*sizeof (Courses));
    system->ques = courses_arr;
    system->num_of_ques = num_of_courses;
    read_courses_from_file(courses,num_of_courses,system);



    int num_of_hackers = get_number_of_lines(hackers,"hackers.txt")/4;
    Hacker * hacker_arr = malloc(num_of_hackers * sizeof (Hacker));
    system->Hackers = hacker_arr;
    read_hackers_from_file(hackers,num_of_hackers, system);
    system ->num_of_hackers = num_of_hackers;

    return system; /** IMPORTANT*/
}


EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues)
{
    int num_of_queues = get_number_of_lines(queues,"queues.txt");
    for (int i = 0; i < num_of_queues; ++i)
    {
        //get course number id
        char* course_id_temp = malloc(sizeof (char));
        read_string(queues, course_id_temp, ' ',1);
        int current_course_id = atoi(course_id_temp);
        free(course_id_temp);


        // find course id in courses arr in system
        int course_index = find_course_index_in_system (current_course_id, sys);
        /*
        while (current_course_id != (sys ->ques[course_index]->course_id))
        {
            course_index++;
            if(course_index >= sys->num_of_ques)//not supposed to happen
            {
                printf("Error no course like that\n");
                break;
            }
        }*/

        //enter the students ids
        int size_of_current_course = sys->ques[course_index]->size;
        int* students_of_current_course_arr = malloc( sizeof (int));
        read_arr_of_strings(queues, students_of_current_course_arr);
        students_of_current_course_arr = realloc(students_of_current_course_arr,size_of_current_course*sizeof (int));
        sys->ques[course_index]->enrollment_list = students_of_current_course_arr;

    }
    return sys;

}

//------------------------------------------------


//------------------------------------------------
int* (*pt)(void*, void*);
void hackEnrollment(EnrollmentSystem sys, FILE* out)
{
    IsraeliQueue q;
    q = malloc(sizeof (IsraeliQueue));
    (q->FriendshipFunction) = (pt);
    (&pt)[0] = (&student_id_difference); //TODO check pointers
    (&pt)[1] = (&Name_distance);
    (&pt)[2] = (&check_hacker_file_friend_status);
    for (int hacker_index = 0; hacker_index < sys->num_of_hackers; ++hacker_index)
    {
        for (int i = 0; i < sys->Hackers[hacker_index]->num_of_desired_courses; ++i)
        {
            int current_course_id = sys->Hackers[hacker_index]->desired_courses[i];
            int course_sys_index = find_course_index_in_system (current_course_id, sys);

            //IsraeliQueue new_que = IsraeliQueueCreate(FriendshipFunction *friendshipFunction, ComparisonFunction comparisonFunction, FRIENDSHIP_TH, RIVALRY_TH)


        }

    }




}//TODO
//------------------------------------------------

//------------------------------------------------
//big mini functions:
void read_student_from_file(FILE* students, int num_of_students, EnrollmentSystem system)
{
    if((students = fopen("students.txt","r")) == NULL )/** IMPORTANT*/ /** a lot of warnings of incompatible pointer types in every fopen. must check it*/
    {
        //HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    for (int i= 0; i < num_of_students; i++)
    {
        char id_temp[ID_SIZE]="";

        fgets(id_temp, ID_SIZE, students); /** IMPORTANT*/
        skip_credits_and_gpa(students);


        char* name_temp = malloc(sizeof (char));
        int name_len_temp = read_string(students, name_temp, ' ',2);


        Student student_temp = malloc(sizeof(Student)); /** IMPORTANT*/
        student_temp->name[name_len_temp]= *name_temp;

        free(name_temp);

        student_temp->student_id = atoi(id_temp);
        system->students[i] = student_temp;

        get_to_next_line(students);
        free(student_temp);     /** IMPORTANT*/

    }
    fclose(students);
    return;



}

//------------------------------------------------

void read_courses_from_file(FILE* courses, int num_of_courses, EnrollmentSystem system)
{
    if((courses = fopen("courses.txt","r")) == NULL ) /** IMPORTANT*/ /** a lot of warnings of incompatible pointer types in every fopen. must check it*/
    {
        //HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    for (int i= 0; i < num_of_courses; i++)
    {

        char* course_id_temp = malloc(sizeof (char));
        read_string(courses, course_id_temp, ' ',1);
        Courses course_temp = malloc(sizeof (Courses)); /** IMPORTANT*/
        course_temp ->course_id = atoi(course_id_temp);


        char* course_size_temp = malloc(sizeof (char));
        read_string(courses, course_id_temp, '\n',1);
        course_temp ->size =  atoi(course_size_temp);
        free(course_size_temp);
        free(course_id_temp);/** IMPORTANT*/

        system ->ques[i]= course_temp;

        get_to_next_line(courses);
        free( course_temp);/** IMPORTANT*/

    }
    fclose(courses);
    return;



}

//------------------------------------------------

void read_hackers_from_file(FILE* hackers, int num_of_hackers, EnrollmentSystem system)
{
    if((hackers = fopen("hackers.txt","r")) == NULL )/** IMPORTANT*/ /** a lot of warnings of incompatible pointer types in every fopen. must check it*/
    {
        //HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    for (int i= 0; i < num_of_hackers; i++)
    {
        Hacker hacker_temp = malloc(sizeof (Hacker)); /** IMPORTANT*/

        //read hacker id
        char id_temp[ID_SIZE]="";
        fgets(id_temp, ID_SIZE, hackers); /** IMPORTANT*/
        hacker_temp->hacker_id = atoi(id_temp);

        char* trash =""; /** IMPORTANT*/
        fgets(trash, 1, hackers);


        //read desired courses
        int* desired_courses_temp= malloc(sizeof (int));
        int num_of_courses_temp= read_arr_of_strings(hackers,desired_courses_temp);
        hacker_temp->desired_courses = desired_courses_temp;
        hacker_temp->num_of_desired_courses = num_of_courses_temp;

        //read friends courses
        int* friends_temp= malloc(sizeof (int));
        read_arr_of_strings(hackers,friends_temp);
        hacker_temp->friends = friends_temp;

        //read rivals courses
        int* rivals_temp= malloc(sizeof (int));
        read_arr_of_strings(hackers,rivals_temp);
        hacker_temp->rivals = rivals_temp;

        free(hacker_temp);/** IMPORTANT*/

    }
    fclose(hackers);
    return;



}

int* (*pt)(void*, void*);

//------------------------------------------------
//mini functions:

int get_number_of_lines (FILE* file, char* file_name )
{
    if((file = fopen(file_name,"r")) == NULL )/** IMPORTANT*/ /** a lot of warnings of incompatible pointer types in every fopen. must check it*/
    {
        return HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    int lines_counter = 0;
    char* char_temp = malloc(sizeof (char ));/** IMPORTANT*/
    fgets(char_temp, 1, file);
    while (*char_temp != EOF) /** IMPORTANT*/ /** warning says endless loop + changed to *char temp and says it is no longer endless*/
    {
        if (*char_temp == '\n') /** IMPORTANT*/
        {
            lines_counter++;
        }
        fgets(char_temp, 1, file); /** IMPORTANT*/ /** UNREACHABLE CODE DOWN - somehow already reachable lol*/
    }
    free(char_temp);
    fclose( file);
    return lines_counter;
}


//------------------------------------------------


int read_string(FILE* stream, char* str,char stop_char ,int num_of_stops)
{
    char* char_temp = malloc(sizeof (char ));/** IMPORTANT*/
    int i = 1;
    while (num_of_stops > 0 )
    {
        i++;
        fgets(char_temp, 1, stream);
        str = realloc(str, i * sizeof(char));
        str[i]= *char_temp; /** IMPORTANT*/
        if (*char_temp == stop_char)/** IMPORTANT*/
        {
            num_of_stops--;
        }
    }
    free(char_temp);
    return i;
}
//------------------------------------------------
int read_arr_of_strings(FILE* stream, int* arr)
{
    IsraeliQueue q;
    q = malloc(sizeof (IsraeliQueue));
    (q->FriendshipFunction) = (pt);
    (&pt)[0] = (&student_id_difference); //TODO check pointers
    (&pt)[1] = (&Name_distance);
    (&pt)[2] = (&check_hacker_file_friend_status);

    char* char_temp = malloc(sizeof (char )); /** IMPORTANT*/
    int j = 0;

    while (*char_temp != '\n') /** IMPORTANT*/
    {
        char* str_temp = malloc(sizeof (char));
        int i = 1;
        fgets(char_temp, 1, stream);
        str_temp[0]= *char_temp;/** IMPORTANT*/
        while (*char_temp != ' ')
        {
            i++;
            fgets(char_temp, 1, stream);
            str_temp = realloc(str_temp, i * sizeof(char));
            str_temp[i]= *char_temp;
        }
        arr = realloc(arr, (j+1)*sizeof (int));
        arr[j]= atoi(str_temp);
        free( str_temp);
    }
    free(char_temp);
    return j;

}


//------------------------------------------------

void skip_credits_and_gpa(FILE* stream)
{
    char* char_temp = malloc(sizeof (char )); /** IMPORTANT*/
    int num_of_spaces = 3;
    while (num_of_spaces > 0 )
    {
        fgets(char_temp, 1, stream);
        if (*char_temp == ' ')/** IMPORTANT*/
        {
            num_of_spaces--;
        }
    }
    free(char_temp);
    return;

}



void get_to_next_line(FILE* stream)
{
    char* char_temp = malloc(sizeof (char ));/** IMPORTANT*/
    while (*char_temp != '\n')/** IMPORTANT*/
    {
        fgets(char_temp, 1, stream);

    }
    free(char_temp);/** IMPORTANT*/
    return;
}
//------------------------------------------------


int Name_distance (char* name1, char* name2)
{
    int res = str_ASCII_value(name1, capslock) - str_ASCII_value(name2, capslock);
    return (res >= 0) ? res : (res * (-1));
}
//------------------------------------------------


int str_ASCII_value(char* str, bool caps_lock)
{


    int len = strlen(str);
    int sum =0;
    if (!caps_lock) // a == A
    {
        for (int i=0; i< len; i++)
        {
            if (str[i] >= 'A' && str[i]<= 'a')
            {
                sum += str[i] + ('a'-'A') ;
            }
            else
            {
                sum += str[i];
            }
            sum += str[i];
        }
        return sum;
    }

    else // a != A
    {
        for (int i=0; i< len; i++)
        {
            sum += str[i];
        }
        return sum;
    }

}
//------------------------------------------------


int student_id_difference(int* id1,int* id2)
{
    int res = &id1 - &id2;
    return (res >= 0) ? res : (res * (-1));

}

//------------------------------------------------

int check_hacker_file_friend_status(EnrollmentSystem sys, int hacker_id, int student_id )
{
    //find current hacker
    int hacker_index =0;
    while (hacker_id!= sys ->Hackers[hacker_index]->hacker_id)
    {
        hacker_index ++;
        if(hacker_index >= sys->num_of_hackers) {
            printf("no hacker found\n");
            break;
        }
    }//
    Hacker current_hacker = sys ->Hackers [hacker_index];

    //find if student is in friend list
    int num_of_friends = *(&(current_hacker->friends)+1) - (current_hacker->friends);
    for (int i = 0; i < num_of_friends; ++i)
    {
        if(student_id == current_hacker->friends[i])
        {
            return FRIEND;
        }
    }

    //find if student is in rival list
    int num_of_rivals = *(&(current_hacker->rivals)+1) - (current_hacker->rivals);
    for (int i = 0; i < num_of_rivals; ++i)
    {
        if(student_id == current_hacker->rivals[i])
        {
            return RIVAL;
        }
    }

    return NEUTRAL;

}

//---------------------------------------------------------------------------
int find_course_index_in_system ( int current_course_id, EnrollmentSystem sys)
{
    int course_index = 0;
    while (current_course_id != (sys ->ques[course_index]->course_id))
    {
        course_index++;
        if(course_index >= sys->num_of_ques)//not supposed to happen
        {
            printf("Error no course like that\n");
            break;
        }
    }
    return course_index;
}