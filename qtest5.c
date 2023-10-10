/* qtest5.c --- 
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
        fprintf( stdout, "The element stored in the queue here is: %s\n", printStruct->element);
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

    // Apply Function to queue
    qapply(qp1, printq);
    
    exit(EXIT_SUCCESS); 
    
}
