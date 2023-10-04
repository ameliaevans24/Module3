/* queue.c --- 
 * 
 * 
 * Author: Amelia H. Evans
 * Created: Tue Oct  3 10:23:09 2023 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
#include "queue.h"

/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)){
	while (current->next != NULL){
		fn(qp); 
		qp -> next = next; 
	}
}

/* search a queue using a supplied boolean function
 * skeyp -- a key to search for
 * searchfn -- a function applied to every element of the queue
 *          -- elementp - a pointer to an element
 *          -- keyp - the key being searched for (i.e. will be 
 *             set to skey at each step of the search
 *          -- returns TRUE or FALSE as defined in bool.h
 * returns a pointer to an element, or NULL if not found
 */
void* qsearch(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp), const void* skeyp){
 	
 	if (qp == NULL || searchfn == NULL || skeyp == NULL) {
        return NULL; // Invalid input
    }
	queue_t *current = qp -> front; 
	
	while(!searchfn(current -> elementp, skeyp)){
		current -> next = next; 
	}	
	return current -> elementp; 
}