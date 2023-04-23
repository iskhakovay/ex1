#include "stdio.h"
#include "stdlib.h"
#include "IsraeliQueue.h"

typedef struct node{
    int data;
    struct  node* next;
}*Node;

struct IsraeliQueue_t{
    int *FriendshipFunction;
    int friendship_th;
    int rivalry_th;
    Node front;
    Node rear;
    int count;
};

int isEmpty(IsraeliQueue q){
    return (q->rear==NULL);
}

/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction * friendship_function, ComparisonFunction, int friendship_th, int rivalry_th){
    IsraeliQueue new_queue;
    *new_queue = malloc(sizeof (IsraeliQueue_t));
    new_queue->count = 0;
    new_queue->friendship_th = friendship_th;
    new_queue->rivalry_th = rivalry_th;
    new_queue->FriendshipFunction = friendship_function;
    new_queue->front = NULL;
    new_queue->rear = NULL;
    return new_queue; //pointer?
}

/**@param IsraeliQueue: an IsraeliQueue created by IsraeliQueueCreate
 *
 * Deallocates all memory allocated by IsraeliQueueCreate for the object pointed to by
 * the parameter.*/
void IsraeliQueueDestroy(IsraeliQueue q){
    free(q); ///????????????????
}

/**@param IsraeliQueue: an IsraeliQueue in which to insert the item.
 * @param item: an item to enqueue
 *
 * Places the item in the foremost position accessible to it.*/
IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void* item){
    Node tmp;
    tmp = malloc(sizeof(Node));
    tmp->data = item;
    tmp->next = NULL;
    if(!isEmpty(q)){
        q->rear->next = tmp;
        q->rear = tmp;
    }else{
        q->front = q->rear = tmp;
    }
    q->count++;
    free(tmp);
}

/**Removes and returns the foremost element of the provided queue. If the parameter
        * is NULL or a pointer to an empty queue, NULL is returned.*/
void* IsraeliQueueDequeue(IsraeliQueue q){
    if(q==NULL){
        return NULL;
    }
    Node  *tmp;
    tmp = malloc(sizeof(Node));
    void* n = q->front->data;
    if(n==NULL){
        return NULL;
    }
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return n;
}
/**Returns the number of elements of the given queue. If the parameter is NULL, 0
 * is returned.*/
int IsraeliQueueSize(IsraeliQueue q){
    if(isEmpty(q)) return NULL;
    return q->count;
}

//TODO
/**@param item: an object comparable to the objects in the IsraeliQueue
 *
 * Returns whether the queue contains an element equal to item. If either
 * parameter is NULL, false is returned.*/
bool IsraeliQueueContains(IsraeliQueue, void *);
//TODO
/**Advances each item in the queue to the foremost position accessible to it,
 * from the back of the queue frontwards.*/
IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue);
//TODO
/**@param q_arr: a NULL-terminated array of IsraeliQueues
 * @param ComparisonFunction: a comparison function for the merged queue
 *
 * Merges all queues in q_arr into a single new queue, with parameters the parameters described
 * in the exercise. Each queue in q_arr enqueues its head in the merged queue, then lets the next
 * one enqueue an item, in the order defined by q_arr. In the event of any error during execution, return NULL.*/
IsraeliQueue IsraeliQueueMerge(IsraeliQueue*,ComparisonFunction);
//TODO
/**@param IsraeliQueue: an IsraeliQueue to which the function is to be added
 * @param FriendshipFunction: a FriendshipFunction to be recognized by the IsraeliQueue
 * going forward.
 *
 * Makes the IsraeliQueue provided recognize the FriendshipFunction provided.*/
 //TODO
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue, FriendshipFunction);

/**@param IsraeliQueue: an IsraeliQueue whose friendship threshold is to be modified
 * @param friendship_threshold: a new friendship threshold for the IsraeliQueue*/
 //TODO
IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue, int);

/**@param IsraeliQueue: an IsraeliQueue whose rivalry threshold is to be modified
 * @param friendship_threshold: a new rivalry threshold for the IsraeliQueue*/
 //TODO
IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue, int);
//TODO
/**Returns a new queue with the same elements as the parameter. If the parameter is NULL or any error occured during
* the execution of the function, NULL is returned.*/
IsraeliQueue IsraeliQueueClone(IsraeliQueue q);