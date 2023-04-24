#include "stdio.h"
#include "stdlib.h"
#include "IsraeliQueue.h"
#include "IsraeliQueue.c"

int main(){
    IsraeliQueue q;
    q = IsraeliQueueCreate(NULL,NULL,2,3);
    int arr[6] = {2,3,4,1,2,4};
    for(int i = 0; i<6; i++){
        IsraeliQueueEnqueue(q,arr[i]);
    }
    IsraeliQueueDequeue(q);
    return 0;

}