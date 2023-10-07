#include "queue.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXREG 15

// Define car struct
typedef struct car {
    struct car *next;
    char plate[MAXREG];
    double price;
    int year;
} car_t;

// Define house struct
typedef struct house {
    struct house *next;
    char style[MAXREG];
    double price;
    int year;
} house_t;

// Define fruit struct
typedef struct fruit {
    struct fruit *next;
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
    queue_t *qp = qopen();

    // Define Elements
    car_t car1 = {NULL, "ABC123", 2020, 20000.0};
    house_t house1 = {NULL, "Colonial", 1809, 500000.0};
    fruit_t fruit1 = {NULL, "Banana"};

    // Put Elements in queue
    qput(qp, &fruit1);
    qput(qp, &house1);
    qput(qp, &car1);

    // Apply Function to queue
    qapply(qp, printq);

    // Use qsearch function
    const char *qfind = "Colonial";
    queue_t *qfound = qsearch(qp, searchfn, (void *)qfind); // Search queue for house of style Colonial

    if (qfound != NULL) {
        printf("Found the house of style: %s\n", qfind);
    } else {
        printf("House of style: %s not found in the queue.\n", qfind);
    }

    // Clean up
    qclose(qp);

    return 0;
}
