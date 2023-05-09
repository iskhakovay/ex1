#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"
#include "HackEnrollment.h"
#include "HackEnrollment.c"


int main(int argc, char** argv)//????
{
    EnrollmentSystem sys =createEnrollment(students, courses, hackers);
    sys =readEnrollment(sys, queues);
    hackEnrollment(sys, FILE* out);



}

