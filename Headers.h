
#ifndef EX1_HEADERS_H
#define EX1_HEADERS_H
#include "IsraeliQueue.h"
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
struct IsraeliQueue_t{
    FriendshipFunction *friendshipFunction;
    ComparisonFunction comparisonFunction;
    int friendship_function_len;
    int friendship_th;
    int rivalry_th;
    Node front;
    Node rear;
    int count;
};
#endif //EX1_HEADERS_H
