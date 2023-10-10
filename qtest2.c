/* qtest2.c ---                                                                 
 *                                                                              
 *                                                                              
 * Author: Rashad C. Brown-Mitchell I.                                          
 * Created: Sun Oct  8 13:15:24 2023 (-0400)                                    
 * Version:                                                                     
 *                                                                              
 * Description:                                                                 
 *                                                                              
 */                                                                             
                                                                                
#include "queue.h"                                                              
#include <stdlib.h>                                                             
#include <stdio.h>                                                              
                                                                                
#define MAXREG 15                                                               
                                                                                
// Define car struct                                                            
typedef struct car {                                                            
  struct car *next;                                                             
  char plate[MAXREG];                                                           
  double price;                                                                 
  int year;                                                                     
} car_t;                                                                        
                                                                                
int main(){                                                                     
                                                                                
  void* qp = qopen();                                                           
  printf("The address of our queue is %p\n", qp);                               
                                                                                
  car_t car1 = {NULL, "ABC123", 20000, 2020};                                   
  qput(qp, &car1);                                                              
                                                                                
  // Verify that first element is removed from queue                            
  void* removedElmt = qget(qp);                                                 
  printf("The address of our removed element is %p\n", removedElmt);            
  exit(EXIT_SUCCESS);                                                           
                                                                                
    // qclose(qp);                                                              
}                 
