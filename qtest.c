#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXREG 15

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
    car_t *car = (car_t *)elementp;
    house_t *house = (house_t *)elementp;
    fruit_t *fruit = (fruit_t *)elementp;

    if (car != NULL) {
        printf("Car with plate: %s, year: %d, price: %.2lf\n", car->plate, car->year, car->price);
    } else if (house != NULL) {
        printf("House with style: %s, year: %d, price: %.2lf\n", house->style, house->year, house->price);
    } else if (fruit != NULL) {
        printf("Fruit of type: %s\n", fruit->type);
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
    car_t car1 = {"ABC123", 20000.0, 2020};
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
    queue_t *qfound = qsearch(qp1, searchfn, (void *)qfind); // Search queue for house of style Colonial

    if (qfound != NULL) {
        printf("Found the house of style: %s\n", qfind);
    } else {
        printf("House of style: %s not found in the queue.\n", qfind);
    }
	// Initialize second queue
	queue_t *qp2 = qopen(); 
	
	//Define Elements of q2
    car_t car2 = {"XYZ789", 30000.0, 2023};
    house_t house2 = {"Art Deco", 1929, 550000.0};
    fruit_t fruit2 = {"Orange"};
    
    //Concatenate q1 and q2
    qconcat(qp1, qp2); 
    
    //Put Elements in queue (2)
	qput(qp1, &car2);
    qput(qp1, &house2);
    qput(qp1, &fruit2);
    
    //Apply function to new queue (q1)
    qapply(qp1,printq); 
    
    // Clean up
    qclose(qp1);

    return 0;
}
