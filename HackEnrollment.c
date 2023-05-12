#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "HackEnrollment.h"
#include "IsraeliQueue.h"
#include "Headers.h"


#define ID_SIZE 9
#define FRIEND_IN_FILE 20
#define RIVAL_IN_FILE (-20)
#define NEUTRAL_IN_FILE 0
#define FRIENDSHIP_TH 20
#define RIVALRY_TH 0

//------------------------------------------------
bool capslock = true;
void defineCapsLock(bool caps_lock)
{
   capslock = caps_lock;
   return;
}

//------------------------------------------------
/** main functions are declared in HackEnrollment.h:
EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);

void hackEnrollment(EnrollmentSystem sys, FILE* out);
 */

//------------------------------------------------
//friendship functions declaration

/**
checks to see the absolute difference between the student_id of two students.

Parameters :
----------
- student1 : Student

- student2 : Student

Returns :
--------
- res: INT
absolute value of result.
*/
int studentIdDifference(void* student1, void* student2);

/**
checks to see the absolute difference between [ASCII value of Name1] - [ASCII value of Name2]
Parameters :
----------
- student1 : Student

- student2 : Student

- caps_lock : const BOOL
defult- true- 'A' != 'a'
false- 'A' == 'a'
 gets changed as flag in begining.

Returns :
--------
- res: INT
absolute value of result.
*/
int nameDistance (void* student1, void* student2);


/**
checks to see the if the student id of the student appers in the list of friends or rivals of the hacker.
Parameters :
----------
- hacker : Student

- student : Student


Returns :
--------
- res: INT
FRIEND_IN_FILE = 20
RIVAL_IN_FILE = (-20)
NEUTRAL_IN_FILE = 0
*/
int checkHackerFileFriendStatus(void* hacker, void* student );



// help for nameDistance function
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
int strAsciiValue(char* str, bool caps_lock);

//------------------------------------------------
//functions for reading files and entering them into system declaration:

/**
reads the students info (student_id, name) from file and enters it into system

 Parameters :
----------
 * @param students : students file stream
 * @param num_of_students : int
 * @param system : enrollment system

Returns :
--------
NONE
 */
void readStudentFromFile(FILE* students, int num_of_students, EnrollmentSystem system);

/**
reads the courses info (courses_id, size) from file and enters it into system

 Parameters :
----------
 * @param courses : courses file stream
 * @param num_of_courses : int
 * @param system : enrollment system

Returns :
--------
NONE
 */
void readCoursesFromFile(FILE* courses, int num_of_courses, EnrollmentSystem system);

/**
reads the hackers info from file and enters it into system (ito hacker and student):
 Hacker  ->hacker_id
         ->desired_courses
         ->num_of_desired_courses
 Student ->friends
         ->num_of_friends
         ->rivals
         ->num_of_rivals

 Parameters :
----------
 * @param hackers : courses file stream
 * @param num_of_hackers : int
 * @param system : enrollment system

 Returns :
--------
NONE
 */
void readHackersFromFile(FILE* hackers, int num_of_hackers, EnrollmentSystem system);

//------------------------------------------------
//functions to make the file reading nicer declaration:

/**
reads stream and places it in string until stop_char shows up the number of times (num_of_stops)

Parameters :
----------
 * @param stream : file stream that we read
 * @param str :pointer to return string
 * @param stop_char : char used to stop reading
 * @param num_of_stops : number of times stop_char needs to show up.

 Returns :
--------
 * @return : len of return string
 */
int readString(FILE* stream, char* str, char stop_char , int num_of_stops);

/**
reads list of "int"s that are sperted with a space, antil end o line (or EOF), and plasecs them in arry.

Parameters :
----------
 * @param stream
 * @param arr

Returns :
--------
 * @return : len of arr
 */
int readArrOfStrings(FILE* stream, int* arr);

/**
 * progrsses in stream untill reaches '\n'
 * @param stream
 */
void getToNextLine(FILE* stream);

/**
 * counts number of lines ('\n') in file.
 * @param file
 * @param file_name
 * @return number of lines in file
 */
int getNumberOfLines (FILE* file, char* file_name);

/**
 * skips the " credits" and "GPA" in students info
 * @param stream
 */
void skipCreditsAndGpa(FILE* stream);


//------------------------------------------------
// system orientation functions declaration:

/**
 * find the index of a course in sys ->ques
 * @param current_course_id
 * @param sys
 * @return course index in system
 */
int findCourseIndexInSystem (int current_course_id, EnrollmentSystem sys);

/**
 * find the index of a student in sys ->students
 * @param id
 * @param sys
 * @return  student index in system
 */
int findStudentIndexInSystem (int id, EnrollmentSystem sys);

//------------------------------------------------
//more functions declaration:

/**
Prints the updated enrollment lists of each course to out.
 * @param sys : EnrollmentSystem
 * @param out : FILE*
 */
void printNewQues (EnrollmentSystem sys, FILE* out);

/**
creates IsraeliQueues for each course and adds students to them based on their enrollment.
 * @param sys : EnrollmentSystem
 * @param arr_of_queues : array of IsraeliQueue pointers to store the created queues.
 * @param pt : array of function pointers to be used as friendship functions in the IsraeliQueue.
 */
void turnEnrollmentListToIsrealiQues (EnrollmentSystem sys, IsraeliQueue* arr_of_queues, FriendshipFunction *pt);

/**
 * enrolls hackers into Israeli queues based on their desired courses.
 * @param sys
 * @param arr_of_queues
 */
void enrollHackers(EnrollmentSystem sys, IsraeliQueue* arr_of_queues);

/**
cleans up the enrollment queues for each course in the enrollment system by removing students who can't fit in their
desired courses, and updating the enrollment lists for each course.
then destroy each queue and free the memory allocated for the array of queue pointers.
 * @param sys
 * @param arr_of_queues
 */
void cleanEnrollmentQueues(EnrollmentSystem sys, IsraeliQueue *arr_of_queues);

/**
determines if a hacker can successfully enroll in a course, based on the size of the course and the current number of
students enrolled in the course.
 * @param current_hacker
 * @param system
 * @param needed_queue
 * @param course
 * @return true if the hacker can enroll in the course
 */
bool isEnrollmentSuccess(Hacker current_hacker, IsraeliQueue needed_queue, Courses course);



/**===================================================================================================================*/
//main functions:

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers)
{
    printf("inside of createEnrollment");

    EnrollmentSystem  system;
    system = malloc(sizeof (EnrollmentSystem)); /** IMPORTANT*/
    if(system!=NULL){
        printf("memory allocated");
    }else{
        printf("memory error");
    }

    int num_of_students = getNumberOfLines(students, "students.txt");
    Student* students_arr = malloc(num_of_students*sizeof (Student));
    if(num_of_students==0){
        printf("error: count lines");
    }
    if(students_arr==NULL){
        printf("memory error student arr");
    }
    system->students = students_arr;
    readStudentFromFile(students, num_of_students, system);
    system->num_of_students = num_of_students;

    int num_of_courses = getNumberOfLines(courses, "courses.txt");
    Courses * courses_arr = malloc(num_of_courses*sizeof (Courses));
    system->ques = courses_arr;
    system->num_of_ques = num_of_courses;
    readCoursesFromFile(courses, num_of_courses, system);



    int num_of_hackers = getNumberOfLines(hackers, "hackers.txt") / 4;
    Hacker * hacker_arr = malloc(num_of_hackers * sizeof (Hacker));
    system->Hackers = hacker_arr;
    readHackersFromFile(hackers, num_of_hackers, system);
    system ->num_of_hackers = num_of_hackers;

    return system; /** IMPORTANT*/
}

//------------------------------------------------
EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues)
{
    int num_of_queues = getNumberOfLines(queues, "queues.txt");
    for (int i = 0; i < num_of_queues; ++i)
    {
        //get course number id
        char* course_id_temp = malloc(sizeof (char));
        readString(queues, course_id_temp, ' ', 1);
        int current_course_id = atoi(course_id_temp);
        free(course_id_temp);

        // find course id in courses arr in system
        int course_index = findCourseIndexInSystem(current_course_id, sys);


        //enter the students ids
        sys->ques[course_index]->enrollment_list = malloc(sizeof (int));
        sys->ques[course_index]->size_of_enrolment_list = readArrOfStrings(queues,
                                                                           sys->ques[course_index]->enrollment_list);
        sys->ques[course_index]->enrollment_list = realloc(sys->ques[course_index]->enrollment_list,(sys->ques[course_index]->size)*sizeof (int)); /** why */

    }
    return sys;

}

//------------------------------------------------

int (*pt)(void*, void*);
void hackEnrollment(EnrollmentSystem sys, FILE* out)
{
    (&pt)[0] = (studentIdDifference); //TODO check pointers
    (&pt)[1] = (nameDistance);
    (&pt)[2] = (&checkHackerFileFriendStatus);

    IsraeliQueue* arr_of_queues = malloc(sizeof(IsraeliQueue)*sys->num_of_ques);

    // turned all enrollment lists to israeli queues
    turnEnrollmentListToIsrealiQues(sys, arr_of_queues, &pt);

    //put hackers inside of queues
    enrollHackers(sys, arr_of_queues);



    for(int hacker_index = 0; hacker_index < sys->num_of_hackers; hacker_index++)
    {
        for(int i = 0; i < sys->Hackers[hacker_index]->num_of_desired_courses;i++)
        {
            int desired_course_id = sys->Hackers[hacker_index]->desired_courses[i];
            int index_of_current_desired_course = findCourseIndexInSystem(desired_course_id, sys);
            isEnrollmentSuccess(sys->Hackers[hacker_index],  arr_of_queues[index_of_current_desired_course],
                                sys->ques[index_of_current_desired_course]);

        }
        if(sys->Hackers[hacker_index]->register_course_succsesful < 2)
        {
            out = fopen("out.txt", "w");
            fprintf(out, "Cannot satisfy constraints for %d\n", sys->Hackers[hacker_index]->hacker_id);
            fclose(out);
            return;
        }

    }
    cleanEnrollmentQueues(sys, arr_of_queues);

    printNewQues(sys, out);
    free(sys);
    return;

}

/**===================================================================================================================*/

//------------------------------------------------
bool isEnrollmentSuccess(Hacker current_hacker, IsraeliQueue needed_queue, Courses course)
{
    int queue_size = IsraeliQueueSize(needed_queue);
    if(queue_size<=course->size){
        current_hacker->register_course_succsesful++;
        return true;
    }
    int diff = queue_size - course->size;
    Node tmp = needed_queue->rear;
    for(int i = 0; i<diff;i++){
        if(needed_queue->rear->data->student_id == current_hacker->hacker_id){
            needed_queue->rear = tmp;
            return false;
        }
        needed_queue->rear= needed_queue->rear->next;
    }
    needed_queue->rear = tmp;
    current_hacker->register_course_succsesful++;
    return true;
}

//----------------------------------------------------------------------------

void cleanEnrollmentQueues(EnrollmentSystem sys, IsraeliQueue *arr_of_queues)
{
    //going through each course
    IsraeliQueue trash = IsraeliQueueCreate(NULL,NULL,0,0);
    for(int course_index = 0; course_index< sys->num_of_ques ;course_index++){
        // taking queue that matches the course index
        int queue_size = IsraeliQueueSize(*(arr_of_queues+course_index));
        // calculating how many students we need to cut off
        int diff = queue_size - sys->ques[course_index]->size;
        //absolute value
        //erase students that don't fit in current course
        if(diff<0){
            sys->ques[course_index]->size_of_enrolment_list = queue_size;
        }
        while(diff>0){
            trash->rear =arr_of_queues[course_index]->rear;
            arr_of_queues[course_index]->rear = arr_of_queues[course_index]->rear->next;
            diff--;
        }
        IsraeliQueueDestroy(trash);
        //updating enrollment list for current course
        for(int current_student_index = 0; current_student_index < sys->ques[course_index]->size_of_enrolment_list; current_student_index++){
            sys->ques[course_index]->enrollment_list[current_student_index] = arr_of_queues[course_index]->rear->data->student_id;
        }
        IsraeliQueueDestroy(arr_of_queues[course_index]);
    }
    free(arr_of_queues);
}

//------------------------------------------------
void enrollHackers(EnrollmentSystem sys, IsraeliQueue* arr_of_queues)
{
    for(int hacker_index = 0; hacker_index < sys->num_of_hackers; hacker_index++)
    {
        //checking which courses hacker wants
        for(int i = 0; i<sys->Hackers[hacker_index]->num_of_desired_courses;i++){
            int desired_course_id = sys->Hackers[hacker_index]->desired_courses[i];
            int index_of_current_desired_course = findCourseIndexInSystem(desired_course_id, sys);
            int current_hacker_system_index = findStudentIndexInSystem(sys->Hackers[hacker_index]->hacker_id, sys);
            Student current_hacker = sys->students[current_hacker_system_index];
            IsraeliQueueEnqueue(arr_of_queues[index_of_current_desired_course],current_hacker);
        }
    }
}
//------------------------------------------------


void turnEnrollmentListToIsrealiQues (EnrollmentSystem sys, IsraeliQueue* arr_of_queues, FriendshipFunction *pt)
{
    for (int queue_index = 0; queue_index<sys->num_of_ques; queue_index++)
    {
        IsraeliQueue current_course_queue = IsraeliQueueCreate(pt,NULL,FRIENDSHIP_TH,RIVALRY_TH);
        int current_queue_len = sys->ques[queue_index]->size_of_enrolment_list;

        for(int student_index = 0; student_index<current_queue_len; student_index++){
            int current_student_id = sys->ques[queue_index]->enrollment_list[student_index];
            int current_student_sys_index = findStudentIndexInSystem(current_student_id, sys);
            Student current_student = sys->students[current_student_sys_index]; //TODO change enrollment list & israeli queue nodes
            IsraeliQueueEnqueue(current_course_queue,current_student);
        }
        arr_of_queues[queue_index] = current_course_queue;

    }
    //put hackers inside of queues

}

//------------------------------------------------

void printNewQues (EnrollmentSystem sys, FILE* out)
{
    out = fopen("out.txt", "w");
    for (int i = 0; i < sys->num_of_ques; ++i)
    {
        fprintf(out, "%d", sys->ques[i]->course_id);
        for (int j = 0; j < sys->ques[i]->size_of_enrolment_list; ++j)
        {
            fprintf(out, " %d", sys->ques[i]->enrollment_list[j]);
        }
        fprintf(out, "\n");

    }
    fclose(out);

}

//------------------------------------------------

void readStudentFromFile(FILE* students, int num_of_students, EnrollmentSystem system)
{
    // if((students = fopen("students.txt","r")) == NULL )/** IMPORTANT*/ /** a lot of warnings of incompatible pointer types in every fopen. must check it*/
    // {
    //     //HACK_ENROLLMENT_FAILED_READ_FILE;
    // }
    rewind(students);
    for (int i= 0; i < num_of_students; i++)
    {
        char id_temp[ID_SIZE]="";

        fgets(id_temp, ID_SIZE, students); /** IMPORTANT*/
        printf("Here0");
        fflush(stdout);
        skipCreditsAndGpa(students);

        printf("Here1");
        fflush(stdout);
        system->students[i]->name = malloc(sizeof (char));
        readString(students, system->students[i]->name, ' ', 2);
        printf("Here2");
        fflush(stdout);

        system->students[i]->student_id = atoi(id_temp);

        getToNextLine(students);

    }
    return;



}

//------------------------------------------------

void readCoursesFromFile(FILE* courses, int num_of_courses, EnrollmentSystem system)
{
    if((courses = fopen("courses.txt","r")) == NULL ) /** IMPORTANT*/ /** a lot of warnings of incompatible pointer types in every fopen. must check it*/
    {
        //HACK_ENROLLMENT_FAILED_READ_FILE;
    }
    for (int i= 0; i < num_of_courses; i++)
    {

        char* course_id_temp = malloc(sizeof (char));
        readString(courses, course_id_temp, ' ', 1);

        system->ques[i] = malloc(sizeof (Courses));
        system->ques[i]->course_id = atoi(course_id_temp);


        readString(courses, course_id_temp, '\n', 1);

        system->ques[i]->size = atoi(course_id_temp);
        free(course_id_temp);/** IMPORTANT*/

        getToNextLine(courses);

    }
    fclose(courses);
    return;



}

//------------------------------------------------

void readHackersFromFile(FILE* hackers, int num_of_hackers, EnrollmentSystem system)
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
        system->Hackers[i]->num_of_desired_courses  = readArrOfStrings(hackers, system->Hackers[i]->desired_courses);

        int sys_student_index = findStudentIndexInSystem(system->Hackers[i]->hacker_id, system);

        //read friends
        system->students[sys_student_index]->friends  = malloc(sizeof (int));
        system->students[sys_student_index]->num_of_friends = readArrOfStrings(hackers,
                                                                               system->students[sys_student_index]->friends);


        //read rivals
        system->students[sys_student_index]->rivals  = malloc(sizeof (int));
        system->students[sys_student_index]->num_of_rivals = readArrOfStrings(hackers,
                                                                              system->students[sys_student_index]->rivals);

    }
    fclose(hackers);
    return;



}



//------------------------------------------------
//mini functions:



int getNumberOfLines (FILE* file, char* file_name )
{
    // if((fopen(file_name,"r"))==NULL){
    //     return HACK_ENROLLMENT_FAILED_READ_FILE;
    // }
    rewind(file);
    int lines = 0;
    char tmp_char = fgetc(file);
    while (tmp_char != EOF)
    {
        tmp_char = fgetc(file);
        if (tmp_char == '\n')
        {
            lines++;
        }
    }
    return lines;
    // // if((fopen(file_name,"r"))==NULL){
    // //     return HACK_ENROLLMENT_FAILED_READ_FILE;
    // // }
    // int lines_counter = 0;
    // char* char_temp = malloc(sizeof (char));
    // fgets(char_temp, 1, file);
    // while ((*char_temp)!=EOF)
    // {
    //     // printf("\nHere\n");
    //     printf("%c", *char_temp);
    //     // printf("%c", *char_temp);
    //     // if (strcmp(char_temp,"\n")==0)
    //     if (*char_temp == '\n')
    //     {
    //         lines_counter++;
    //     }
    //     fgets(char_temp, 1, file);
    // }
    // free(char_temp);
    // fclose( file);
    // return lines_counter;
}


//------------------------------------------------


int readString(FILE* stream, char* str, char stop_char , int num_of_stops)
{
    char* char_temp = malloc(sizeof (char));/** IMPORTANT*/
    int i = 0;
    while (num_of_stops > 0 )
    {
        i++;
        fgets(char_temp, 1, stream);
        str = realloc(str, (i+1) * sizeof(char));
        str[i]= *char_temp; /** IMPORTANT*/
        if (*char_temp == stop_char)/** IMPORTANT*/
        {
            num_of_stops--;
        }
    }
    str[i+1]= '\0';
    free(char_temp);
    return i;
}
//------------------------------------------------
int readArrOfStrings(FILE* stream, int* arr)
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

void skipCreditsAndGpa(FILE* stream)
{
    int num_of_spaces = 3;
    char char_temp = fgetc(stream);
    while (num_of_spaces > 0) {
        if (char_temp == ' ') {
            num_of_spaces--;
        }
        char_temp = fgetc(stream);
    }
    return;
    // char* char_temp = malloc(sizeof (char )); /** IMPORTANT*/
    // int num_of_spaces = 3;
    // while (num_of_spaces > 0 )
    // {
    //     fgets(char_temp, 1, stream);
    //     if (*char_temp == ' ')/** IMPORTANT*/
    //     {
    //         num_of_spaces--;
    //     }
    // }
    // free(char_temp);
    // return;

}



void getToNextLine(FILE* stream)
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

int nameDistance (void* student1, void* student2)
{
    Student *pt1 = (Student*) student1;
    Student *pt2 = (Student*) student2;
    int res = strAsciiValue((*pt1)->name, capslock) - strAsciiValue((*pt2)->name, capslock);
    return (res >= 0) ? res : (res * (-1));
}
//------------------------------------------------


int strAsciiValue(char* str, bool caps_lock)
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


int studentIdDifference(void* student1, void* student2)
{
    Student *pt1 = (Student*) student1;
    Student *pt2 = (Student*) student2;
    int result = (*pt1)->student_id - (*pt2)->student_id;
    return (result >= 0) ? result : (result * (-1));

}

//------------------------------------------------

int checkHackerFileFriendStatus(void* hacker, void* student )
{
    Student *pt1 = (Student*) hacker;
    Student *pt2 = (Student*) student;

    //find if student is in friend list
    for (int i = 0; i < (*pt1)->num_of_friends; ++i)
    {
        if((*pt2)->student_id == (*pt2)->friends[i])
        {
            return FRIEND_IN_FILE;
        }
    }

    //find if student is in rival list
    for (int i = 0; i < (*pt1)->num_of_rivals; ++i)
    {
        if((*pt2)->student_id == (*pt1)->rivals[i])
        {
            return RIVAL_IN_FILE;
        }
    }

    return NEUTRAL_IN_FILE;

}

//---------------------------------------------------------------------------
int findCourseIndexInSystem (int current_course_id, EnrollmentSystem sys)
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
int findStudentIndexInSystem (int id, EnrollmentSystem sys)
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