#include <stdio.h>
int sum(int a, int b,int c);
int subtract(int a, int b);
int mul(int a, int b);
int div(int a, int b);

int (*p[4]) (int x, int y);

int main() {
    // simple array
    p[0] = sum; /* address of sum() */
    p[1] = subtract; /* address of subtract() */
    p[2] = mul; /* address of mul() */
    p[3] = div; /* address of div() */
    int arr[] = {1,2,3,4,5,6,7,8,1,0,2,3,4,5,1,};
    int arr_len = *(&p + 1) - p; // using pointer arithmetic.
    //printf("The length of the char array is: %d", arr_len);
    int arr2[2][10] = {0};
    //arr2[0][0] = 0;
    int a = 0;
    return 0;
}
int sum(int a, int b,int c)
{
    return a + b;
}
int* (*pt)(void*, void*);
void hackEnrollment(EnrollmentSystem sys, FILE* out)
{
    IsraeliQueue q;
    q = malloc(sizeof (IsraeliQueue));
    (q->FriendshipFunction) = (pt);
    (&pt)[0] = (&student_id_difference); //TODO check pointers
    (&pt)[1] = (&Name_distance);
    (&pt)[2] = (&check_hacker_file_friend_status);

}//TODO

int subtract(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int div(int a, int b)
{
    if(b)
        return a / b;
    else
        return 0;
}