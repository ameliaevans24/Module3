#include "list.h"
#include <stddef.h>
#include <string.h>

static car_t *front = NULL;

int32_t lput(car_t *cp){
	if (cp == NULL) {
		return 1; //Invalid input
	}
	else { 
		cp -> next = front; 
		front = cp; 
		return 0; //success
	}  
} 

car_t *lget(){
	if (front == NULL){
		return NULL; //Empty List
	}
	car_t *car = front; 
	front = front -> next; 
	return car; 
}

/* apply a function to every car in the list */
void lapply(void (*fn)(car_t *cp)){
	car_t *current = front;
	while (current != NULL){
		fn(current); 
		current = current ->next; 
	}
}

car_t *lremove(char *platep){
	if (strcmp(front -> plate, platep) == 0){
		car_t *removed = front; 
		front = front -> next;
		return removed;
	}
	
	car_t *current = front; 
	while (current->next != NULL){
		if(strcmp(current->next->plate,platep) == 0){
			car_t *removed = current -> next; 
			current -> next = current -> next -> next; 
			return removed;
		}
		current = current -> next;
	}
	return NULL; //Address not found
}
