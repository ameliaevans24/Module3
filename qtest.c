#include "queue.h"
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

    // Apply Function to queue
    qapply(qp1, printq);

    // Use qsearch function
    const char *qfind = "Colonial";
    house_t *qfound = (house_t *)qsearch(qp1, searchfn, (void *)qfind);

    if (qfound != NULL) {
        printf("Found the house of style: %s\n", qfound->style);
    } else {
        printf("House of style: %s not found in the queue.\n", qfind);
    }
    
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
    
    //Apply function to queue 2
	printf("The queue 2 is:\n"); 
    qapply(qp2,printq); 
        
    //Concatenate queue 1 and queue 2
    qconcat(qp1, qp2);  
    
    //Apply function to newly concatenated queue 1
    printf("The new queue 1 is:\n"); 
    qapply(qp1,printq); 

	//Create Empty queue
	queue_t *qp3 = qopen(); 
	queue_t *qp4 = qopen(); 
	
	//Concat Empty queues
	qconcat(qp3, qp4);  
	
	//Apply function to newly concatenated queues
	qapply(qp3,printq); 
	printf("Queue is Empty!\n"); 
	
	//Concat non-Empty and Empty queues:
	qconcat(qp1,qp3); 
	
	//Print new queue
	printf("New non-Empty and Empty queue 1:\n");
	qapply(qp1,printq); 
	
	//Concat Empty and non-Empty queue
	queue_t *qp5 = qopen(); //new empty queue
	qconcat(qp5,qp1); 
	
	//Print new queue
	printf("New Empty and non-Empty queue 1:\n");
	qapply(qp5, printq);
	 
    // Clean up
    qclose(qp5);
		
    return 0;
}
