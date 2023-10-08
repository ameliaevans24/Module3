#include <stdlib.h>                                                                                                                             
#include <stdio.h>                                                                                                                              
#include "queue.h"                                                                                                                              
                                                                                                                                                
int main(){                                                                                                                                     
  typedef struct car{                                                                                                                           
    int model;                                                                                                                                  
  }car_t;                                                                                                                                       
                                                                                                                                                
  car_t car1 = {0};                                                                                                                             
  car_t car2 = {2};                                                                                                                             
                                                                                                                                                
  queue_t *qp = qopen();                                                                                                                        
                                                                                                                                                
  qput(qp, &car1);                                                                                                                              
  qput(qp, &car2);                                                                                                                              
  void* frontTakenPointer = qget(qp);                                                                                                           
  car_t* pointerToCarPointer = (car_t*)frontTakenPointer;                                                                                       
  car_t pointerToCar = *pointerToCarPointer;                                                                                                    
  void* frontTakenPointer2 = qget(qp);                                                                                                          
  car_t* pointerToCarPointer2 = (car_t*)frontTakenPointer2;                                                                                     
  car_t pointerToCar2 = *pointerToCarPointer2;                                                                                                  
  printf("Our pointer for our queue is %p\n", qp);  
  printf("Hello! \n");                                                                                                                          
  printf("The model is %d \n", pointerToCar.model);                                                                                             
  printf("Hello 2! \n");                                                                                                                        
  printf("The model of the second car is %d \n", pointerToCar2.model);                                                                          
  fflush(stdout);                                                                                                                               
  exit(EXIT_SUCCESS);                                                                                                                           
  return 0;   
}
