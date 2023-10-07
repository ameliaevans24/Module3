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
#include <stdint.h>                                                                                                                                                                                         
#include <stdlib.h> // For malloc function                                                                                                                                                                  
#include <stdbool.h>                                                                                                                                                                                        
                                                                                                                                                                                                            
/* the queue representation is hidden from users of the module */                                                                                                                                           
//typedef void queue_t;                                                                                                                                                                                     
                                                                                                                                                                                                            
// Define custom data stucture for queue                                                                                                                                                                    
typedef struct queue{                                                                                                                                                                                       
  struct queue *front; // SHOULD THIS BE STRUCT QUEUE OR SOMETHING ELSE??                                                                                                                                   
  struct queue *back;                                                                                                                                                                                       
}queue_t;                                                                                                                                                                                                   
                                                                                                                                                                                                            
// Define custom data structure for element                                                                                                                                                                 
typedef struct node{                                                                                                                                                                                        
  struct node *previous;                                                                                                                                                                                    
  struct node *next;                                                                                                                                                                                        
}node_t;                                                                                                                                                                                                    
                                                                                                                                                                                                            
/* create an empty queue */                                                                                                                                                                                 
queue_t* qopen(void){                                                                                                                                                                                       
                                                                                                                                                                                                            
  // Allocate space for one instance of structure                                                                                                                                                           
  queue_t *qp = (queue_t*)malloc(sizeof(queue_t));                                                                                                                                                          
                                                                                                                                                                                                            
  // Assign front and back for new queue                                                                                                                                                                    
  qp -> front = NULL;                                                                                                                                                                                       
  qp -> back = NULL;                                                                                                                                                                                        
                                                                                                                                                                                                            
  return qp;                                                                                                                                                                                                
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
/* deallocate a queue, frees everything in it */                                                                                                                                                            
void qclose(queue_t *qp);                                                                                                                                                                                   
                                                                                                                                                                                                            
/* put element at the end of the queue                                                                                                                                                                      
 * returns 0 is successful; nonzero otherwise                                                                                                                                                               
 */                                                                                                                                                                                                         
int32_t qput(queue_t *qp, void *elementp){                                                                                                                                                                  
  if ((qp->front == NULL) && (qp->back == NULL)){                                                                                                                                                           
    qp->front = elementp;                                                                                                                                                                                   
    qp->back = elementp;                                                                                                                                                                                    
  }                                                                                                                                                                                                         
                                                                                                                                                                                                            
  else{                                                                                                                                                                                                     
    element->previous = qp->back;                                                                                                                                                                           
    element->next = NULL;                                                                                                                                                                                   
    qp -> back = elementp;                                                                                                                                                                                  
  }                                                                                                                                                                                                         
} 


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
