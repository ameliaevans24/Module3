/*                                                                                           
 * queue.c -- public interface to the queue module                                           
 */                                                                                          
#include <stdint.h>
#include "queue.h"
#include <stdlib.h> // For malloc function                                                   
#include <stdbool.h>                                                                         
                                                                                             
/* the queue representation is hidden from users of the module */                            
//typedef void queue_t;                                                                      
                                                                                             
// Define custom data structure for element                                                  
typedef struct node{                                                                         
  void* elementp;     //pointer to element stored in node                                                                   
  struct node *next; //pointer to the next node                                                                         
}node_t;                                                                                     
                                                                                             
// Define custom data stucture for queue                                                     
typedef struct queue{                                                                        
struct node* front;                                                                        
struct node* back;                                                                         
}iqueue_t;                                                                                    
                                                                                             
/* create an empty queue */                                                                  
queue_t* qopen(void){                                                                        
                                                                                             
  // Allocate space for one instance of structure                                            
  iqueue_t *iqp = (iqueue_t*)malloc(sizeof(iqueue_t));                                           
                                                                                             
  // Assign front and back for new queue                                                     
  iqp -> front = NULL;                                                                        
  iqp -> back = NULL;                                                                         
                                                                                             
  return (queue_t*) iqp;                                                                                 
}                                                                                            
                                                                                             
/* deallocate a queue, frees everything in it */                                             
void qclose(queue_t *qp){   
  iqueue_t *iqp = (iqueue_t*) qp;                                                     
  node_t *current = iqp->front;                                                  
  node_t *temp = NULL;                                                          
  while (current != NULL) {                                                     
    temp = current->next;                                                       
    free(current);                                                              
    current = temp;                                                             
  }                                                                             
  free(iqp);                                                                    
                                                                                
}                                                                                                                                                                                  
                                                                                                                                                                                                            
/* put element at the end of the queue                                                                                                                                                                      
 * returns 0 is successful; nonzero otherwise                                                                                                                                                               
 */                                                                                                                                                                                                         
int32_t qput(queue_t *qp, void *elementp) {
  iqueue_t *iqp = (iqueue_t*) qp;  
    if (iqp == NULL || elementp == NULL) {
        return -1; // Invalid input
    }

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return -1; // Memory allocation failed
    }
    
    new_node->next = NULL;
    new_node->elementp = elementp;

    if (iqp->front == NULL && iqp->back == NULL) {
        // The queue is empty, so both front and back point to the new element
        iqp->front = new_node;
        iqp->back = new_node;
    } else {
        // Add a new element to the end of the queue
        iqp->back->next = new_node;
        iqp->back = new_node;
    }

    return 0; // Success
}
                                                                                           
                                                                                             
/* get the first first element from queue, removing it from the queue */                     
void* qget(queue_t *qp){ 
  iqueue_t *iqp = (iqueue_t*) qp;                                                                      
  if ((iqp->front != NULL) && (iqp->back != NULL)){                                            
    void *removed = iqp->front;                                                               
                                                                                             
    node_t *current;                                                                         
    current = iqp->front;                                                                     
    iqp->front = current->next;                                                               
                                                                                             
    return removed;                                                                          
  }      
  else {
  	return NULL; //Queue Empty
  }                                                                                    
}                                                                                            
                                                                                             
/* apply a function to every element of the queue */                                         
void qapply(queue_t *qp, void (*fn)(void* elementp)){  
  iqueue_t *iqp = (iqueue_t*) qp;                                        
  node_t *current = iqp->front;                                                               
  while (current != NULL) {                                                                                        
    fn(current->elementp);                                                                             
    current = current->next;                                                                 
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
void* qsearch(queue_t *qp, bool (*searchfn)(void* elementp, const void* keyp), const void* skeyp) {
  iqueue_t *iqp = (iqueue_t*) qp;  
if (iqp == NULL || searchfn == NULL || skeyp == NULL) {
        return NULL; // Invalid input
    }

    node_t *current = iqp->front;

    while (current != NULL) {
        if (searchfn(current->elementp, skeyp)) {
            return current->elementp; // Found a matching element
        }
        current = current->next;
    }

    return NULL; // Element not found
}

/* concatenatenates elements of q2 into q1
 * q2 is dealocated, closed, and unusable upon completion 
 */
void qconcat(queue_t *q1p, queue_t *q2p){     
  iqueue_t *iq1p = (iqueue_t*) q1p;  
    iqueue_t *iq2p = (iqueue_t*) q2p;                                                                    
    if ((iq1p->front != NULL)&&(iq2p->front != NULL)){                                                            
    iq1p->back->next = iq2p->front;                                                                               
    iq1p->back = iq2p->back;                                                                                      
      }                                                                                                         
    else{                                                                                                       
      iq1p->front = iq2p->front;                                                                                  
      iq1p->back = iq2p->back;                                                                                    
    }                                                                                                           
  free(iq2p);                                                                                                    
} 

void* qremove(queue_t *qp, bool (*searchfn)(void* elementp,const void* keyp),const void* skeyp){
	  iqueue_t *iqp = (iqueue_t*) qp;  
	if (skeyp == NULL || iqp == NULL) {
        return NULL; // Invalid input or empty queue
    }
    node_t *current = iqp->front; 
    
    if (current != NULL && searchfn(current->elementp, skeyp)) {
        // Element to be removed is the front of the queue
        iqp->front = current->next;
        if (current == iqp->back) {
            iqp->back = NULL;
        }
        void* removed = current->elementp;
        free(current);
        return removed; 
    }
    
    while (current != NULL && current->next != NULL) {
        if (searchfn(current->next->elementp, skeyp)) {
            if (current->next == iqp->back) {
                iqp->back = current;
            }
            node_t *temp = current->next;
            current->next = current->next->next;
            void* removed_element = temp->elementp;
            free(temp);
            return removed_element; // Element found and removed
        }
        current = current->next;
    }

    return NULL; // Element not found
}
							
