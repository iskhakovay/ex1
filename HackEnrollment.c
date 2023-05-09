#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"
#include "IsraeliQueue.h"
#include "IsraeliQueue.c"

#define ID_SIZE 9
#define FRIEND_IN_FILE 20
#define RIVAL_IN_FILE (-20)
#define NEUTRAL_IN_FILE 0
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
    int* friends;
    int num_of_friends;
    int* rivals;
    int num_of_rivals;

}* Student;

typedef struct hacker_t{
    int hacker_id;
    int* desired_courses;
    bool register_course_succsesful;
    int num_of_desired_courses;
    //int* friends;
    //int num_of_friends;
    //int* rivals;
    //int num_of_rivals;
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

//------------------------------------------------
//mini functions declaration:



int read_string(FILE* stream, char* str,char stop_char ,int num_of_stops);

int read_arr_of_strings(FILE* stream, int* arr);//return len


void get_to_next_line(FILE* stream);

int get_number_of_lines (FILE* file, char* file_name);

void skip_credits_and_gpa(FILE* stream);

int find_course_index_in_system ( int current_course_id, EnrollmentSystem sys);

int find_student_index_in_system ( int id, EnrollmentSystem sys);

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
int student_id_difference(Student student1,Student student2);

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
int Name_distance (Student student1,Student student2);

int check_hacker_file_friend_status(Student hacker, Student student );



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


        //enter the students ids
       // int size_of_current_course = sys->ques[course_index]->size;
        //int* students_of_current_course_arr = malloc( sizeof (int));
        sys->ques[course_index]->enrollment_list = malloc(sizeof (int));
        sys->ques[course_index]->size_of_enrolment_list = read_arr_of_strings(queues, sys->ques[course_index]->enrollment_list);
        sys->ques[course_index]->enrollment_list = realloc(sys->ques[course_index]->enrollment_list,(sys->ques[course_index]->size)*sizeof (int)); /** why */
        //sys->ques[course_index]->enrollment_list = students_of_current_course_arr;


    }
    return sys;

}

//------------------------------------------------


//------------------------------------------------
int* (*pt)(void*, void*);
void hackEnrollment(EnrollmentSystem sys, FILE* out)
{
    (&pt)[0] = (int *(*)(void *, void *)) (&student_id_difference); //TODO check pointers
    (&pt)[1] = (int *(*)(void *, void *)) (&Name_distance);
    (&pt)[2] = (int *(*)(void *, void *)) (&check_hacker_file_friend_status);

    IsraeliQueue* arr_of_queues = malloc(sizeof(IsraeliQueue)*sys->num_of_ques);


    for (int queue_index = 0; queue_index<sys->num_of_ques; queue_index++)
    {
        IsraeliQueue current_course_queue = IsraeliQueueCreate(pt,NULL,FRIENDSHIP_TH,RIVALRY_TH);
        int current_queue_len = sys->ques[queue_index]->size_of_enrolment_list;

        for(int student_index = 0; student_index<current_queue_len; student_index++){
            int current_student_id = sys->ques[queue_index]->enrollment_list[student_index];
            int current_student_sys_index = find_student_index_in_system(current_student_id, sys);
            Student current_student = sys->students[current_student_sys_index]; //TODO change enrollment list & israeli queue nodes
            IsraeliQueueEnqueue(current_course_queue,current_student);
        }
        arr_of_queues[queue_index] = current_course_queue;
    }




}

/**  for (int i = 0; i < sys->Hackers[hackerIndex]->num_of_desired_courses; ++i)
        {
            int currentCourseId = sys->Hackers[hackerIndex]->desired_courses[i];
            int courseSysIndex = find_course_index_in_system (currentCourseId, sys);


            //make isreali q from regular q
            IsraeliQueue q = IsraeliQueueCreate(pt,NULL, FRIENDSHIP_TH,RIVALRY_TH);

            for (int j = 0; j < sys->ques[courseSysIndex]->size_of_enrolment_list; ++j)
            {
                int* currentStudentPt = &(sys->ques[courseSysIndex]->enrollment_list[j]);

                IsraeliQueueError q_attemp = IsraeliQueueEnqueue(q, currentStudentPt);
                if (q_attemp != ISRAELIQUEUE_SUCCESS)
                {
                    printf("fail!!!\n");
                }

            }

            //try to enter hacker into q
            int* currentHackerPt = &(sys->Hackers[hackerIndex]->hacker_id);
            IsraeliQueueError hacker_attemp_to_enter = IsraeliQueueEnqueue(q, currentHackerPt);

            if (hacker_attemp_to_enter != ISRAELIQUEUE_SUCCESS)
            {
                printf("fail!!!\n");
            }

            if( q->rear->data == *currentHackerPt)
            {
                out = fopen("out.txt", "w");
                fprintf(out, "Cannot satisfy costraints for %d\n", *currentHackerPt);
                fclose(out);
            }
*/


//TODO
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


       // char* name_temp = malloc(sizeof (char));
       // int name_len_temp = read_string(students, name_temp, ' ',2);
        system->students[i]->name = malloc(sizeof (char));
        read_string(students, system->students[i]->name, ' ',2);


       // Student student_temp = malloc(sizeof(Student)); /** IMPORTANT*/
       // student_temp->name[name_len_temp]= *name_temp;

       // free(name_temp);

        system->students[i]->student_id = atoi(id_temp);
       // system->students[i] = student_temp;

        get_to_next_line(students);
        //free(student_temp);     /** IMPORTANT*/

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
        //Courses course_temp = malloc(sizeof (Courses)); /** IMPORTANT*/
        //course_temp ->course_id = atoi(course_id_temp);

        system->ques[i] = malloc(sizeof (Courses));
        system->ques[i]->course_id = atoi(course_id_temp);


        char* course_size_temp = malloc(sizeof (char));
        read_string(courses, course_id_temp, '\n',1);
        //course_temp ->size =  atoi(course_size_temp);
        system->ques[i]->size = atoi(course_id_temp);
        //free(course_size_temp);
        free(course_id_temp);/** IMPORTANT*/

        //system ->ques[i]= course_temp;

        get_to_next_line(courses);
        //free( course_temp);/** IMPORTANT*/

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

        //read hacker id
        char id_temp[ID_SIZE]="";
        fgets(id_temp, ID_SIZE, hackers); /** IMPORTANT*/
        system->Hackers[i]->hacker_id= atoi(id_temp);

        char* trash =""; /** IMPORTANT*/
        fgets(trash, 1, hackers);


        //read desired courses
        system->Hackers[i]->desired_courses= malloc(sizeof (int));
        system->Hackers[i]->num_of_desired_courses  = read_arr_of_strings(hackers,system->Hackers[i]->desired_courses);

        int sys_student_index = find_student_index_in_system(system->Hackers[i]->hacker_id, system);

        //read friends
       // system->Hackers[i]->friends= malloc(sizeof (int));
        system->students[sys_student_index]->friends  = malloc(sizeof (int));
        //system->Hackers[i]->num_of_friends= read_arr_of_strings(hackers,system->Hackers[i]->friends);
        system->students[sys_student_index]->num_of_friends = read_arr_of_strings(hackers,system->students[sys_student_index]->friends);


        //read rivals
       // system->Hackers[i]->rivals= malloc(sizeof (int));
        system->students[sys_student_index]->rivals  = malloc(sizeof (int));
        //system->Hackers[i]->num_of_rivals = read_arr_of_strings(hackers,  system->Hackers[i]->rivals);
        system->students[sys_student_index]->num_of_rivals = read_arr_of_strings(hackers,system->students[sys_student_index]->rivals);



        //free(hacker_temp);/** IMPORTANT*/

    }
    fclose(hackers);
    return;



}



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


int Name_distance (Student student1,Student student2)
{
    int res = str_ASCII_value(student1->name, capslock) - str_ASCII_value(student2->name, capslock);
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


int student_id_difference(Student student1,Student student2)
{
    int result = student1->student_id - student2->student_id;
    return (result >= 0) ? result : (result * (-1));

}

//------------------------------------------------

int check_hacker_file_friend_status(Student hacker, Student student )
{

    //find if student is in friend list
    for (int i = 0; i < hacker->num_of_friends; ++i)
    {
        if(student->student_id == hacker->friends[i])
        {
            return FRIEND_IN_FILE;
        }
    }

    //find if student is in rival list
    for (int i = 0; i < hacker->num_of_rivals; ++i)
    {
        if(student->student_id == hacker->rivals[i])
        {
            return RIVAL_IN_FILE;
        }
    }

    return NEUTRAL_IN_FILE;

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

//---------------------------------------------------------------------------
int find_student_index_in_system ( int id, EnrollmentSystem sys)
{
    int student_index = 0;
    while (id != (sys ->students[student_index]->student_id))
    {
        student_index++;
        if(student_index >= sys->num_of_students)//not supposed to happen
        {
            printf("Error no student like that\n");
            break;
        }
    }
    return student_index;
}