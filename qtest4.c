/* qtest4.c ---                                                                 
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
                                                                                
// Define print function                                                        
void printq(void* elementp){                                                    
  printf("Contents of this element Address: %p\n", elementp);                   
  }                                                                             
                                                                                
int main(){                                                                     
                                                                                
  void* qp = qopen();                                                           
  printf("The address of our queue is %p\n", qp);                               
                                                                                
  car_t car1 = {NULL, "ABC123", 20000, 2020};                                   
  car_t car2 = {NULL, "DEF456", 32000, 2001};                                   
  car_t car3 = {NULL, "GHI789", 50000, 1997};                                   
  car_t car4 = {NULL, "AAA666", 17000, 2017};                                   
                                                                                
  void* car1adr = &car1;                                                        
  void* car2adr = &car2;                                                        
  void* car3adr = &car3;                                                        
  void* car4adr = &car4;                                                        
                                                                                
  qput(qp, &car1);                                                              
  qput(qp, &car2);                                                              
  qput(qp, &car3);                                                              
  qput(qp, &car3);  

  // Verify that first element is removed from queue                            
  void* removedElmt = qget(qp);                                                 
  printf("The address of our removed element is %p\n", removedElmt);            
  removedElmt = qget(qp);                                                       
  printf("The address of our removed element is %p\n", removedElmt);            
  removedElmt = qget(qp);                                                       
  printf("The address of our removed element is %p\n", removedElmt);            
  exit(EXIT_SUCCESS);                                                           
                                                                                
    // qclose(qp);                                                              
}   
