/* htest2.c ---                                                                                                                                                                                             
 *                                                                                                                                                                                                          
 *                                                                                                                                                                                                          
 * Author: Rashad C. Brown-Mitchell I.                                                                                                                                                                      
 * Created: Wed Oct 11 18:31:32 2023 (-0400)                                                                                                                                                                
 * Version:                                                                                                                                                                                                 
 *                                                                                                                                                                                                          
 * Description:     Test hremove                                                                                                                                                                                        
 *                                                                                                                                                                                                          
 */                                                                                                                                                                                                         
                                                                                                                                                                                                            
#include "queue.h"                                                                                                                                                                                          
#include "hash.h"                                                                                                                                                                                           
#include <stdlib.h>                                                                                                                                                                                         
#include <stdio.h>                                                                                                                                                                                          
#include <string.h>                                                                                                                                                                                         
                                                                                                                                                                                                            
#define MAXREG 10                                                                                                                                                                                           
                                                                                                                                                                                                            
// Define car struct                                                                                                                                                                                        
typedef struct car {                                                                                                                                                                                        
  char plate[10];                                                                                                                                                                                           
  double price;                                                                                                                                                                                             
  int year;                                                                                                                                                                                                 
} car_t;                                                                                                                                                                                                    
                                                                                                                                                                                                            
// Define house struct                                                                                                                                                                                      
typedef struct house {                                                                                                                                                                                      
  char style[MAXREG];                                                                                                                                                                                       
  double price;                                                                                                                                                                                             
  int year;                                                                                                                                                                                                 
} house_t;                                                                                                                                                                                                  
                                                                                                                                                                                                            
void printq(void* elementp){                                                                                                                                                                                
  printf("Contents of this element Address: %p\n", elementp);                                                                                                                                               
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
// Define search function                                                                                                                                                                                   
bool searchfn(void *elementp, const void *keyp) {                                                                                                                                                           
  house_t *house = (house_t *)elementp;                                                                                                                                                                     
  const char *key = (const char *)keyp;                                                                                                                                                                     
  if (house != NULL && strcmp(house->style, key) == 0) {                                                                                                                                                    
    return true;                                                                                                                                                                                            
  }                                                                                                                                                                                                         
  return false;                                                                                                                                                                                             
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
int main(){                                                                                                                                                                                                 
  car_t car1 = {"ABC123", 20000, 2020};                                                                                                                                                               
  house_t house1 = {"Colonial", 1809, 5000000.};                                                                                                                                                            
  const char* key = "Key";                                                                                                                                                                                  
                                                                                                                                                                                                            
  void* car1adr = &car1;                                                                                                                                                                                    
  void* house1adr = &house1;                                                                                                                                                                                
  hashtable_t* hTable = hopen(5);                                                                                                                                                                           
                                                                                                                                                                                                            
  hput(hTable, car1adr, key, 1);                                                                                                                                                                            
  hput(hTable, house1adr, key, 2);                                                                                                                                                                          
  happly(hTable, printq); 
  //Test Search Function 
  const char *qfind = "Colonial"; 
  uint32_t keylen = strlen("Coloial");                                                                                                                                                                                                      
  void* hFound=hsearch(hTable,searchfn,qfind,keylen);                                                                                                                                                       
  if(hFound != NULL){                                                                                                                                                                                       
    printf("Our pointer to the entry is %p\n",hFound);                                                                                                                                                      
  }                                                                                                                                                                                                         
  else{                                                                                                                                                                                                     
    printf("The entry was not found\n");                                                                                                                                                                    
  }                                                                                                                                                                                                         
  void* removed = hremove(hTable, searchfn,qfind, keylen); 
	
  if(removed != NULL){                                                                                                                                                                                       
    printf("Our pointer to the removed entry is %p\n",removed);   
    printf("The new Hashtable is:\n"); 
    happly(hTable,printq);                                                                                                                                                    
  }                                                                                                                                                                                                         
  else{                                                                                                                                                                                                     
    printf("The entry was not found\n");                                                                                                                                                                    
  }                                                                                                                                                                                    
  hclose(hTable);                                                                                                                                                                                           
  exit(EXIT_SUCCESS);                                                                                                                                                                                       
}  
