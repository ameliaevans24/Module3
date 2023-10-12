/* htest1.c ---                                                                                                                                                                                             
 *                                                                                                                                                                                                          
 *                                                                                                                                                                                                          
 * Author: Rashad C. Brown-Mitchell I.                                                                                                                                                                      
 * Created: Wed Oct 11 18:31:32 2023 (-0400)                                                                                                                                                                
 * Version:                                                                                                                                                                                                 
 *                                                                                                                                                                                                          
 * Description:                                                                                                                                                                                             
 *                                                                                                                                                                                                          
 */                                                                                                                                                                                                         
                                                                                                                                                                                                            
#include "queue.h"                                                                                                                                                                                          
#include "hash.h"                                                                                                                                                                                           
#include <stdlib.h>                                                                                                                                                                                         
#include <stdio.h>                                                                                                                                                                                          
                                                                                                                                                                                                            
// Define car struct                                                                                                                                                                                        
typedef struct car {                                                                                                                                                                                        
                                                                                                                                                                                                                                                                                                                                                                                                
  char plate[10];                                                                                                                                                                                           
  double price;                                                                                                                                                                                             
  int year;                                                                                                                                                                                                 
} car_t;                                                                                                                                                                                                    
                                                                                                                                                                                                            
void printq(void* elementp){                                                                                                                                                                                
  printf("Contents of this element Address: %p\n", elementp);                                                                                                                                               
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
int main(){                                                                                                                                                                                                 
  car_t car1 = {"ABC123", 20000, 2020};                                                                                                                                                               
  car_t car2 = {"DEF456", 32000, 2001};                                                                                                                                                               
  car_t car3 = {"GHI789", 50000, 1997};                                                                                                                                                               
  const char* key1 = "Key1";      
  const char* key2 = "Key2";       
  const char* key3 = "Key3";                                                                                                                                                                         
                                                                                                                                                                                                         
  //void* car1adr = &car1;                                                                                                                                                                                    
  //void* car2adr = &car2;                                                                                                                                                                                    
  //void* car3adr = &car3;                                                                                                                                                                                    
  hashtable_t* hTable = hopen(5);                                                                                                                                                                           
                                                                                                                                                                                                            
  hput(hTable, &car1, key1, 4);                                                                                                                                                                            
  hput(hTable, &car2, key2, 4);                                                                                                                                                                            
  hput(hTable, &car3, key3, 4);                                                                                                                                                                            
  happly(hTable, printq);                                                                                                                                                                                   
                                                                                                                                                                                                            
  hclose(hTable);                                                                                                                                                                                           
  exit(EXIT_SUCCESS);                                                                                                                                                                                       
} 
