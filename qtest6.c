/* qtest1.c --- 
 * 
 * 
 * Author: Amelia H. Evans
 * Created: Mon Oct  9 17:57:07 2023 (-0400)
 * Version: 
 * 
 * Description: Test for invalid inputs of qapply 
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

 	// Use qsearch function
    const char *qfind = "Colonial"; //element exists
    queue_t *qfound = qsearch(qp1, searchfn, (void *)qfind); // Search queue for house of style Colonial

    if (qfound != NULL) {
        fprintf(stdout, "Found the house of style: %s\n", qfind);
    } else {
        fprintf(stdout,"House of style: %s not found in the queue.\n", qfind);
    }
    

    
    // Use qsearch again
    const char *qnotfind = "Craftsman"; //element does not exist
    queue_t *qnotfound = qsearch(qp1, searchfn, (void *)qnotfind); // Search queue for house of style Crafstman

     if (qnotfound != NULL) {
        fprintf(stdout, "Found the house of style: %s\n", qnotfind);
    } else {
        fprintf(stdout,"House of style: %s not found in the queue.\n", qnotfind);
    }
    
    exit(EXIT_SUCCESS); 
    
}
