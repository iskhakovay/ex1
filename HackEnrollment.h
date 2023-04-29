#ifndef EX1_HACKENROLLMENT_H
#define EX1_HACKENROLLMENT_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"


typedef struct EnrollmentSystem_t *EnrollmentSystem;

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);

void hackEnrollment(EnrollmentSystem sys, FILE* out);




#endif //EX1_HACKENROLLMENT_H
