#include <stdint.h>                                                                                                                             
#include <stdlib.h> // For malloc function                                                                                                      
#include <stdbool.h>                                                                                                                            
#include <stdio.h>                                                                                                                              
/* the queue representation is hidden from users of the module */                                                                               
//typedef void queue_t;                                                                                                                         
                                                                                                                                                
//create an object for the node so that the element can go in it                                                                                
typedef struct node{                                                                                                                            
  void* element;                                                                                                                                
  struct node* next;                                                                                                                            
} node;  
// Define custom data stucture                                                                                                                  
typedef struct queue{                                                                                                                           
  struct node* front; // SHOULD THIS BE STRUCT QUEUE OR SOMETHING ELSE??                                                                        
  struct node* back;                                                                                                                            
  int counter;                                                                                                                                  
}queue_t;                                                                                                                                       
                                                                                                                                                
/* create an empty queue */                                                                                                                     
queue_t* qopen(void){                                                                                                                           
                                                                                                                                                
  // Allocate space for one instance of structure                                                                                               
  queue_t *qp = (queue_t*)malloc(sizeof(queue_t));                                                                                              
                                                                                                                                                
  // Assign front and back for new queue                                                                                                        
  qp -> front = NULL;                                                                                                                           
  qp -> back = NULL;                                                                                                                            
  qp -> counter = 0;  
                                                                                                                                                
  return qp;                                                                                                                                    
}                                                                                                                                               
                                                                                                                                                
/* deallocate a queue, frees everything in it */                                                                                                
//void qclose(queue_t *qp);                                                                                                                     
                                                                                                                                                
/* put element at the end of the queue                                                                                                          
 * returns 0 is successful; nonzero otherwise                                                                                                   
 */                                                                                                                                             
int32_t qput(queue_t *qp, void *elementp){                                                                                                      
  node* newElement = (node*)(malloc(sizeof(node)));                                                                                             
  newElement->element = elementp;                                                                                                               
  newElement-> next = NULL;                                                                                                                     
  if (qp->front==NULL){                                                                                                                         
    qp->front = newElement;                                                                                                                     
    qp->back = newElement;                                                                                                                      
           }                                                                                                                                             
  return 0;                                                                                                                                     
}                                                                                                                                               
                                                                                                                                                
                                                                                                                                                
                                                                                                                                                
/* get the first first element from queue, removing it from the queue */                                                                        
void* qget(queue_t *qp){                                                                                                                        
    if ((qp->front != NULL) && (qp->back != NULL)){                                                                                             
      void* oldfront = qp->front->element;                                                                                                      
      qp -> front = qp->front->next;                                                                                                            
      return oldfront;                                                                                                                          
    }                                                                                                                                           
    else {                                                                                                                                      
      printf("queue is empty");                                                                                                                 
      return (void*)1;                                                                                                                          
    }                                                                                                                                           
}     
