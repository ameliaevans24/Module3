/* qtest7.c ---                                                                                                                                                                                             
 *                                                                                                                                                                                                          
 *                                                                                                                                                                                                          
 * Author: Amelia H. Evans                                                                                                                                                                                  
 * Created: Mon Oct  9 17:57:07 2023 (-0400)                                                                                                                                                                
 * Version:                                                                                                                                                                                                 
 *                                                                                                                                                                                                          
 * Description: Test for functionality of qsearch                                                                                                                                                           
 *                                                                                                                                                                                                          
 */                                                                                                                                                                                                         
                                                                                                                                                                                                            
#include "queue.h"                                                                                                                                                                                          
#include <stdlib.h>                                                                                                                                                                                         
#include <stdio.h>                                                                                                                                                                                          
#include <stdbool.h>                                                                                                                                                                                        
#include <string.h>                                                                                                                                                                                         
                                                                                                                                                                                                            
#define MAXREG 15                                                                                                                                                                                           
                                                                                                                                                                                                            
//Define struct for printing                                                                                                                                                                                
typedef struct printStruct{                                                                                                                                                                                 
  char element[MAXREG];                                                                                                                                                                                     
} printStruct_t;                                                                                                                                                                                            
                                                                                                                                                                                                            
// Define car struct                                                                                                                                                                                        
typedef struct car {                                                                                                                                                                                        
    char plate[MAXREG];                                                                                                                                                                                     
    double price;                                                                                                                                                                                           
    int year;                                                                                                                                                                                               
} car_t;                                                                                                                                                                                                    
                                                                                                                                                                                                            
// Define house struct                                                                                                                                                                                      
typedef struct house {                                                                                                                                                                                      
    char style[MAXREG];                                                                                                                                                                                     
    double price;                                                                                                                                                                                           
    int year;                                                                                                                                                                                               
} house_t;                                                                                                                                                                                                  
                                                                                                                                                                                                            
// Define fruit struct                                                                                                                                                                                      
typedef struct fruit {                                                                                                                                                                                      
    char type[MAXREG];                                                                                                                                                                                      
} fruit_t;                                                                                                                                                                                                  
                                                                                                                                                                                                            
// Define print function                                                                                                                                                                                    
void printq(void *elementp) {                                                                                                                                                                               
    printStruct_t *printStruct = (printStruct_t *)elementp;                                                                                                                                                 
                                                                                                                                                                                                            
    if (printStruct->element != NULL) {                                                                                                                                                                     
        printf("The element stored in the queue here is: %s\n", printStruct->element);                                                                                                                      
    }                                                                                                                                                                                                       
}                                                                                                                                                                                                           
                                                                                                                                                                                                            
                                                                                                                                                                                                            
int main() {                                                                                                                                                                                                
    // Initialize queue                                                                                                                                                                                     
    queue_t *qp1 = qopen();                                                                                                                                                                                 
                                                                                                                                                                                                            
    // Define Elements                                                                                                                                                                                      
    car_t car1 = {"ABC123", 20000.0, 2014};                                                                                                                                                                 
    house_t house1 = {"Colonial", 1809, 500000.0};                     
   fruit_t fruit1 = {"Banana"};                                                                                                                                                                            
                                                                                                                                                                                                            
    // Put Elements in queue                                                                                                                                                                                
    qput(qp1, &car1);                                                                                                                                                                                       
    qput(qp1, &house1);                                                                                                                                                                                     
    qput(qp1, &fruit1);                                                                                                                                                                                     
                                                                                                                                                                                                            
  // Initialize second queue                                                                                                                                                                                
  queue_t *qp2 = qopen();                                                                                                                                                                                   
                                                                                                                                                                                                            
  //Define Elements of q2                                                                                                                                                                                   
    car_t car2 = {"XYZ789", 30000.0, 2023};                                                                                                                                                                 
    house_t house2 = {"Art Deco", 1929, 550000.0};                                                                                                                                                          
    fruit_t fruit2 = {"Orange"};                                                                                                                                                                            
                                                                                                                                                                                                            
                                                                                                                                                                                                            
    //Put Elements in queue 2                                                                                                                                                                               
    qput(qp2, &car2);                                                                                                                                                                                       
    qput(qp2, &house2);                                                                                                                                                                                     
    qput(qp2, &fruit2);                                                                                                                                                                                     
                                                                                                                                                                                                            
                                                                                                                                                                                                            
    //Concatenate queue 1 and queue 2                                                                                                                                                                       
    qconcat(qp1, qp2);        
    //Apply function to newly concatenated queue 1                                                                                                                                                          
    printf("The new queue 1 is:\n");                                                                                                                                                                        
    qapply(qp1,printq);                                                                                                                                                                                     
                                                                                                                                                                                                            
                                                                                                                                                                                                            
    // Clean up                                                                                                                                                                                             
    qclose(qp1);                                                                                                                                                                                            
                                                                                                                                                                                                            
    exit(EXIT_SUCCESS);                                                                                                                                                                                     
}                 
