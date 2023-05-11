
#ifndef EX1_HEADERS_H
#define EX1_HEADERS_H
typedef struct student_t{
    char* name;
    int student_id;
    int* friends;
    int num_of_friends;
    int* rivals;
    int num_of_rivals;

}* Student;
typedef struct node{
    Student data;
    struct  node* next;
    int friendship;
    int rival;
}*Node;
#endif //EX1_HEADERS_H
