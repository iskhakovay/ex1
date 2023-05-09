#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "IsraeliQueue.h"

#define FRIEND 1
#define RIVAL -1
#define NEUTRAL 0
// i guess it should be here
typedef struct node{
    int data;
    struct  node* next;
    int friendship;
    int rival;
}*Node;
//and this too

typedef struct IsraeliQueue_t{
    int* (*FriendshipFunction)(void*,void*);
    int (*ComparisonFunction)(void*,void*);
    int friendship_function_len;
    int friendship_th;
    int rivalry_th;
    Node front;
    Node rear;
    int count;
} * IsraeliQueue;

int isEmpty(IsraeliQueue q){
    return (q->rear==NULL);
}
Node* createNode(int data, Node *next){ /**NEW SHIT IDK*/
    Node new_node;
    new_node = malloc(sizeof(Node));
    if(new_node==NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    new_node->data = data;
    if((new_node->data=NULL)){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    new_node->next = next;
    if((new_node->next =NULL)){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    new_node->friendship = FRIEND_QUOTA;
    new_node->rival = RIVAL_QUOTA;
    return new_node;
}
void destroyNode(Node *node){ /**  DESTROY THAT SHIT */
    free(node);
}

/**Creates a new IsraeliQueue_t object with the provided friendship functions, a NULL-terminated array,
 * comparison function, friendship threshold and rivalry threshold. Returns a pointer
 * to the new object. In case of failure, return NULL.*/
IsraeliQueue IsraeliQueueCreate(FriendshipFunction *friendshipFunction, ComparisonFunction comparisonFunction, int friendship_th, int rivalry_th){//TODO how to use that function pointer
    IsraeliQueue new_queue;
    new_queue = malloc(sizeof (IsraeliQueue));
    if(new_queue==NULL){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    new_queue->count = 0;
    if(friendshipFunction==NULL || comparisonFunction==NULL){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    new_queue->friendship_th = friendship_th;
    new_queue->rivalry_th = rivalry_th;
    new_queue->FriendshipFunction = friendshipFunction[0];
    new_queue->friendship_function_len = *(&friendshipFunction+1) - friendshipFunction;
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
int statusCheck(void* item1, void* item2, IsraeliQueue q){
    int len = q->friendship_function_len;
    int  sum = 0, avr = 0;

    for(int i = 0; i<len; i++) {
        int tmp = (q->FriendshipFunction + i)(item1, item2);
        sum+=tmp;
        if(tmp > q->friendship_th){
            return FRIEND;
        }
    }

    avr = sum/len;
    if(avr<q->rivalry_th){
        return RIVAL;
    }

    return NEUTRAL;
}

Node getPlacement(IsraeliQueue q, void * item){
    Node tmp = q->rear, tmp_friend=NULL, tmp_rival=NULL;
    int status = 0;
    bool used;
    while (q->rear->next!=NULL){
        status = statusCheck(item,q->rear,q);
        if(status == NEUTRAL){
            continue;
        }
        if(status == RIVAL){
            if(q->rear->rival>0){
                tmp_rival = q->rear;
                used = false;
            }
        } else if(status == FRIEND){
            if(q->rear->friendship>0){
                if(tmp_rival!=NULL){
                    if(used == false){
                        used = true;
                        tmp_rival->rival--;
                    }
                }else{
                    tmp_friend = q->rear;
                }

            }
        }
        q->rear=q->rear->next;

    }
    q->rear = tmp;
    if(tmp_friend==NULL){
        return NULL;
    }
    tmp_friend->friendship--;
    return tmp_friend;

} //TODO check
IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void* item){ /**   TODO: i don't understand what they want help */
    Node placement;
    Node tmp;
    tmp = q->rear;
    if(!isEmpty(q)){
        if(q->count<=2)
             q->rear = createNode(item,q->front);
        placement = getPlacement(q,item);
        while(q->rear->next!=NULL){
            if(q->rear->next == placement){
                Node new_item = createNode(item,placement);
                q->rear->next = new_item;
            }
        }

    }else{
        q->front = createNode(item,NULL);
        q->rear = q->front;
    }
    q->rear = tmp;
    q->count++;
    return ISRAELIQUEUE_SUCCESS;
} //TODO check

/**Removes and returns the foremost element of the provided queue. If the parameter
        * is NULL or a pointer to an empty queue, NULL is returned.*/
void* IsraeliQueueDequeue(IsraeliQueue q){
    if(q==NULL){
        return NULL;
    }
    Node  tmp;
    void* n = q->front->data;
    if(n==NULL){
        return NULL;
    }
    tmp = q->rear;
    while(true){
        if(q->rear->next->next==NULL) {
            q->rear->next = NULL;
            q->front = q->rear;
            q->rear = tmp;
            q->count--;
            return n;
        }
        q->rear = q->rear->next;
    }


}
/**Returns the number of elements of the given queue. If the parameter is NULL, 0
 * is returned.*/
int IsraeliQueueSize(IsraeliQueue q){
    if(isEmpty(q)) return 0;
    return q->count;
}

/**@param item: an object comparable to the objects in the IsraeliQueue
 *
 * Returns whether the queue contains an element equal to item. If either
 * parameter is NULL, false is returned.*/
bool IsraeliQueueContains(IsraeliQueue q, void *item){
    Node copy = q->rear;
    while(copy->next!=NULL){
        if(q->ComparisonFunction(&(q->rear->data),item)){
            return true;
        }
    }
    return false;
}

/**Advances each item in the queue to the foremost position accessible to it,
 * from the back of the queue frontwards.*/
 int maxItemValue(IsraeliQueue q){
     int max = 0;
     Node tmp = q->rear;
     while(q->rear->next!=NULL){
         if(q->rear->data>max){
             max = q->rear->data;
         }
     }
     q->rear = tmp;
    return max;
 }
IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue q){ //TODO CHECK
  /**  Node  current_item, suggested_position, tmp, new_first;
    int len = maxItemValue(q);
    int hist [len] ;
    */
    Node tmp, new_first;
    int q_len = q->count;
    while(q_len>0){
        tmp = createNode(q->rear->data,NULL); /** MAYBE IT IS BETTER */
        new_first = q->rear->next;
        q->rear->next = NULL;
        q->rear = new_first;
        IsraeliQueueEnqueue(q,tmp);
        q_len--;
    }

    /**

    for(int i = 0; i<len;i++){/
        hist[i] = 0;
    }
    while(q->rear->next!=NULL){
        if(hist[q->rear->data]>0){
            q->rear= q->rear->next;
            continue;
        }else{
            tmp = q->rear->next;
            q->rear->next = NULL;
            suggested_position = getPlacement(q,q->rear);
            if(q->rear->next==suggested_position){
                q->rear->next = tmp;
                continue;
            } else{
                current_item->data = q->rear->data;
                current_item->next=NULL;
                IsraeliQueueEnqueue(q,current_item);
                hist[current_item->data]++;
            }
        }
        q->rear= q->rear->next;
    } */

}

//TODO
/**@param q_arr: a NULL-terminated array of IsraeliQueues
 * @param ComparisonFunction: a comparison function for the merged queue
 *
 * Merges all queues in q_arr into a single new queue, with parameters the parameters described
 * in the exercise. Each queue in q_arr enqueues its head in the merged queue, then lets the next
 * one enqueue an item, in the order defined by q_arr. In the event of any error during execution, return NULL. WHAT THE FUCK IT MEANS*/
int newFriendshipTh(IsraeliQueue* arr){
    int i  = 0, sum = 0;
    while((arr+i)!=NULL){
        sum+= (*(arr+i))->friendship_th;
        i++;
    }
    return  sum/(i-1);
}
int newRivalTh(IsraeliQueue* arr){
    int i  = 0, sum = 0;
    while((arr+i)!=NULL){
        sum+= (*(arr+i))->rivalry_th;
        i++;
    }
    return  sum/(i-1);
}
int* mergeFriendshipFunctions(IsraeliQueue* arr){//TODO CHECK
    int len_of_arr = *(&arr + 1)-arr;
    int len_of_all_functions_arr = 0;
    for(int i = 0; i<len_of_arr; i++){
        len_of_all_functions_arr+= (*(arr+i))->friendship_function_len;
    }

    int new_arr[len_of_all_functions_arr];

    for(int i = 0; i <len_of_all_functions_arr; i++){
        for(int j = i; j<(*(arr+i))->friendship_function_len+i; j++)
            new_arr[i] = (*(arr+j))->FriendshipFunction;
    }
    return new_arr;
}
IsraeliQueue longestQueue(IsraeliQueue* arr, int len){//TODO CHECK
    int max_len = 0;
    IsraeliQueue longest_queue;
    for(int i = 0; i<len;i++){
        if((*arr+i)->count>max_len){
            max_len = (*arr+i)->count;
            longest_queue = (*arr+i);
        }
    }
    return longest_queue;
}
IsraeliQueue IsraeliQueueMerge(IsraeliQueue* arr,ComparisonFunction comparisonFunction){//TODO CHECK
    IsraeliQueue new_queue,tmp;
    IsraeliQueue longest_queue;

    int new_friendship_th = newFriendshipTh(arr), new_rival_th = newRivalTh(arr);
    int* new_friendship_arr = mergeFriendshipFunctions(arr);
    int len_of_arr = *(&arr + 1)-arr;

    longest_queue = longestQueue(arr,len_of_arr);

    new_queue = IsraeliQueueCreate(new_friendship_arr,comparisonFunction,new_friendship_th,new_rival_th);

    Node new_item, next_item, first_item, current_item;
    while(longest_queue->rear!=NULL) {
        first_item = createNode((*arr)->front->data,NULL);
        new_queue->front=first_item;

        new_item = createNode((*arr+1)->front->data,first_item);
        new_queue->rear = new_item;

        next_item = new_item;                                   /**  idk.............. fishy.....*/

        IsraeliQueueDequeue((*arr));
        IsraeliQueueDequeue(tmp);
        for (int i = 2; i < len_of_arr; i++) {
            tmp = (*arr + i);
            if(tmp->front==NULL){
                continue;
            }
            current_item = createNode(tmp->front->data,next_item);
            IsraeliQueueDequeue(tmp);
            next_item = current_item;
        }
    }
    return new_queue;

}


/**@param IsraeliQueue: an IsraeliQueue to which the function is to be added
 * @param FriendshipFunction: a FriendshipFunction to be recognized by the IsraeliQueue
 * going forward.
 *
 * Makes the IsraeliQueue provided recognize the FriendshipFunction provided.*/
 //TODO
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friendshipFunction){ /**  i don't care i'll just make a new array*/ //TODO CHECK
    int len = q->friendship_function_len+1;
    int* arr[len];
    for(int i = 0; i<len-1;i++){
        arr[i] = (q->FriendshipFunction+i);
    }
    arr[len] = friendshipFunction;
    q->FriendshipFunction = arr;                /** idk...*/

}

/**@param IsraeliQueue: an IsraeliQueue whose friendship threshold is to be modified
 * @param friendship_threshold: a new friendship threshold for the IsraeliQueue*/

IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int new_friendship_th){
    q->friendship_th=new_friendship_th;
}


/**@param IsraeliQueue: an IsraeliQueue whose rivalry threshold is to be modified
 * @param friendship_threshold: a new rivalry threshold for the IsraeliQueue*/

IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int new_rival_th){
    q->rivalry_th = new_rival_th;
}


/**Returns a new queue with the same elements as the parameter. If the parameter is NULL or any error occured during
* the execution of the function, NULL is returned.*/
IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    if(isEmpty(q)){
        return NULL;
    }
    IsraeliQueue new_queue = IsraeliQueueCreate(q->FriendshipFunction,q->ComparisonFunction,q->friendship_th,q->rivalry_th);
    Node tmp = q->rear;
    while (q->rear->next->next!=NULL){
        new_queue->rear->data = q->rear->data;
        new_queue->rear->next = createNode(q->rear->next->next->data,NULL);
        q->rear = q->rear->next;
    }
    q->rear = tmp;
    return new_queue;
}//TODO ?????