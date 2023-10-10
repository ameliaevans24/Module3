/*                                                                                           
 * queue.c -- public interface to the queue module                                           
 */                                                                                          
#include <stdint.h>                                                                          
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
}queue_t;                                                                                    
                                                                                             
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
void qclose(queue_t *qp){                                                       
  node_t *current = qp->front;                                                  
  node_t *temp = NULL;                                                          
  while (current != NULL) {                                                     
    temp = current->next;                                                       
    free(current);                                                              
    current = temp;                                                             
  }                                                                             
  free(qp);                                                                    \
                                                                                
}                                                                                                                                                                                  
                                                                                                                                                                                                            
/* put element at the end of the queue                                                                                                                                                                      
 * returns 0 is successful; nonzero otherwise                                                                                                                                                               
 */                                                                                                                                                                                                         
int32_t qput(queue_t *qp, void *elementp) {
    if (qp == NULL || elementp == NULL) {
        return -1; // Invalid input
    }

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return -1; // Memory allocation failed
    }
    
    new_node->next = NULL;
    new_node->elementp = elementp;

    if (qp->front == NULL && qp->back == NULL) {
        // The queue is empty, so both front and back point to the new element
        qp->front = new_node;
        qp->back = new_node;
    } else {
        // Add a new element to the end of the queue
        qp->back->next = new_node;
        qp->back = new_node;
    }

    return 0; // Success
}
                                                                                           
                                                                                             
/* get the first first element from queue, removing it from the queue */                     
void* qget(queue_t *qp){                                                                     
  if ((qp->front != NULL) && (qp->back != NULL)){                                            
    void *removed = qp->front;                                                               
                                                                                             
    node_t *current;                                                                         
    current = qp->front;                                                                     
    qp->front = current->next;                                                               
                                                                                             
    return removed;                                                                          
  }                                                                                          
}                                                                                            
                                                                                             
/* apply a function to every element of the queue */                                         
void qapply(queue_t *qp, void (*fn)(void* elementp)){                                        
  node_t *current = qp->front;                                                               
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
if (qp == NULL || searchfn == NULL || skeyp == NULL) {
        return NULL; // Invalid input
    }

    node_t *current = qp->front;

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
  if ((q1p->front != NULL)&&(q2p->front != NULL)){                              
    q1p->back->next = q2p->front;                                               
    q1p->back = q2p->back;                                                      
  }                                                                             
  free(q2p);                                                                    
} 
