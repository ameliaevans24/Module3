/* qtest8.c --- 
 * 
 * 
 * Author: Amelia H. Evans
 * Created: Wed Oct 11 20:34:07 2023 (-0400)
 * Version: 
 * 
 * Description: Test functionality of qremove
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

// Define search function
bool searchfn(void *elementp, const void *keyp) {
    house_t *house = (house_t *)elementp;
    const char *key = (const char *)keyp;

    if (house != NULL && strcmp(house->style, key) == 0) {
        return true;
    }

    return false;
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

    //Print queue
    printf("The the elements in queue are:\n"); 
    qapply(qp1,printq); 
	
	//Remove element from queue
	const char *qfind = "Colonial";
	house_t *qfound = qremove(qp1,searchfn, (void *)qfind);
	
	//Print removed element
	if (qfound != NULL) {
        printf("Found the house of style: %s\n", qfound->style);
    } else {
        printf("House of style: %s not found in the queue.\n", qfind);
    }
    
    //Remove non-existent element
    const char *qfind1 = "Tudor";
	house_t *qfound1 = qremove(qp1,searchfn, (void *)qfind1);
	
	//Print removed element
	if (qfound1 != NULL) {
        printf("Found the house of style: %s\n", qfound1->style);
    } else {
        printf("House of style: %s not found in the queue.\n", qfind1);
    }
    
    // Clean up
    qclose(qp1);

    exit(EXIT_SUCCESS);
}
