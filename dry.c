/**
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "assert.h"

char* stringDuplicator(char* str, int times)
{
    //no need to check if input is valid, but can be nice:
    //assert(str != NULL);
    //assert(times > 0);
    int len = strlen(str);
    char* out = malloc(len * times * sizeof (char));
    if(out == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < times; ++i)
    {
        strcat(out, str);
    }
    return out;
}

int main()
{
    char* str = "hello";
    printf("%s",stringDuplicator( str, 3));
    return 0;
}
*/