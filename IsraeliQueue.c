#include "stdio.h"
#include "stdlib.h"
#include "IsraeliQueue.h"

/*typedef struct node{
    int data;
    struct  node* next;
}*Node;

typedef struct IsraeliQueue_t{
    int *FriendshipFunction;
    int ComparisonFunction;
    int friendship_th;
    int rivalry_th;
    Node front;
    Node rear;
    int count;
}IsraeliQueue;*/

int isEmpty(IsraeliQueue q){
    return (q->rear==NULL);
}
Node* createNode(int data, Node *next){ /**NEW SHIT IDK*/
    Node new_node;
    new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = next;
    return new_node;
}
void destroyNode(Node *node){ /**  DESTROY THAT SHIT */
    free(node);
}
int (*pt)(void *,void *);
/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction *friendshipFunction, ComparisonFunction comparisonFunction, int friendship_th, int rivalry_th){//TODO how to use that function pointer
    IsraeliQueue new_queue;
    new_queue = malloc(sizeof (IsraeliQueue));
    new_queue->count = 0;
    new_queue->friendship_th = friendship_th;
    new_queue->rivalry_th = rivalry_th;
    new_queue->FriendshipFunction = friendshipFunction;
    new_queue->front = NULL;
    new_queue->rear = NULL;
    new_queue->ComparisonFunction = comparisonFunction;
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
Node friendsInQueueCheck(IsraeliQueue q, void * item){
    Node tmp = q->rear, friend;
    while (q->rear->next!=NULL){
        if(q->FriendshipFunction(item,q->rear)>FRIEND_QUOTA){
            friend = q->rear;
        }
    }

    q->rear = tmp;
    if(friend==NULL)
        return NULL;
    return friend;
} //TODO check
Node rivalsInQueueCheck(IsraeliQueue q, void  * item){

} //TODO check
bool canGoForward (IsraeliQueue q, void *next, void *friend){} //TODO
IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void* item){ /**   TODO: i don't understand what they want help */
    if(!isEmpty(q)){
        Node tmp;
        tmp = q->rear;
        if(q->count<=2)
             q->rear = createNode(item,q->front);
        Node items_friend = friendsInQueueCheck(q,item);
        if(items_friend == NULL) {
            q->rear = createNode(item, tmp);
        }else{
            Node items_tival = rivalsInQueueCheck(q,item);
            if(canGoForward(q,item,items_friend)){
                //TODO
            }
        }
    }else{
        q->front = createNode(item,NULL);
        q->rear = q->front;
    }
    q->count++;
} //TODO check

/**Removes and returns the foremost element of the provided queue. If the parameter
        * is NULL or a pointer to an empty queue, NULL is returned.*/
void* IsraeliQueueDequeue(IsraeliQueue q){
    if(q==NULL){
        return NULL;
    }
    Node  tmp;
    tmp;
    void* n = q->front->data;
    if(n==NULL){
        return NULL;
    }
    tmp = q->rear;
    while(q->rear->next->next!=NULL){
        q->rear = q->rear->next;
        if(q->rear->next->next==NULL) {
            q->rear->next = NULL;
            q->front = q->rear;
            q->rear = tmp;
            q->count--;
            return n;
        }
    }

}
/**Returns the number of elements of the given queue. If the parameter is NULL, 0
 * is returned.*/
int IsraeliQueueSize(IsraeliQueue q){
    if(isEmpty(q)) return 0L;
    return q->count;
}

/**@param item: an object comparable to the objects in the IsraeliQueue
 *
 * Returns whether the queue contains an element equal to item. If either
 * parameter is NULL, false is returned.*/
bool IsraeliQueueContains(IsraeliQueue q, void *item){
    Node copy = q->rear;
    while(copy->next!=NULL){
        if(copy->data==item){
            return true;
        }
    }
    return false;
}
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

/**Returns a new queue with the same elements as the parameter. If the parameter is NULL or any error occured during
* the execution of the function, NULL is returned.*/
IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    if(isEmpty(q)){
        return NULL;
    }
    IsraeliQueue new_queue = IsraeliQueueCreate(q->FriendshipFunction,q->ComparisonFunction,q->friendship_th,q->rivalry_th);
    Node tmp = q->rear;
    while (q->rear->next!=NULL){
        IsraeliQueueEnqueue(new_queue,q->rear->data);
        q->rear = q->rear->next;
    }
    q->rear = tmp;
    return new_queue;
}