/* test2.c --- 
 * 
 * 
 * Author: Rashad C. Brown-Mitchell I.
 * Created: Mon Oct  2 21:25:00 2023 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_car(car_t *car) {
  printf("Plate = %s, Year: %d, Price %.2lf\n",car->plate, car -> year, car -> price);
}   

int main(){

	int status = 0;
	car_t *cp = NULL;
	car_t car1 = {NULL, "ABC123", 2020, 20000};
	car_t car2 = {NULL, "DEF456", 2024, 45000};
	car_t car3 = {NULL, "GHI789", 2000, 2003};
	car_t car4 = {NULL, "GDD777", 1999, 20320};
	car_t car5 = {NULL, "BDD666", 1273, 54293}; 	

	// Put elements into list
	lput(&car1);
	lput(&car2);
	lput(&car3);
	lput(&car4);
	lput(&car5);
	lapply(print_car);
	printf("\n");

	// Remove element from end of list
	char platep[] = "ABC123";
	cp = lremove(platep);
	if (cp == NULL){
		printf(" Test was unsuccesul, car pointer is :%p\n", cp);
		status = 0;
	}
	else{
		printf("Test was succesful, we removed the following car from the list\n");
		print_car(cp);
		printf("Our list is now \n\n");
		lapply(print_car);
		printf("\n");
		status = 1;
	}

	// Remove element from beginning of list
	strcpy(platep,"BDD666");
	cp = lremove(platep);
	if (cp == NULL){
		printf("Test was unsuccesul, car pointer is :%p\n", cp);
		status = 0;
	}
	else{
		printf("Test was succesful, we removed the following car from the list\n");
		print_car(cp);
		printf("Our list is now \n\n");
		lapply(print_car);
		printf("\n");
		status = 1;
	}

	// Remove element from middle of list
	strcpy(platep,"GHI789");
	cp = lremove(platep);
	if (cp == NULL){
		printf("Test was unsuccesul, car pointer is :%p\n", cp);
		status = 0;
	}
	else{
		printf("Test was succesful, we removed the following car from the list\n");
		print_car(cp);
		printf("Our list is now \n\n");
		lapply(print_car);
		status = 1; 
	}

	if ( status == 1 ){
		exit(EXIT_SUCCESS);
	}
	else{
		exit(EXIT_FAILURE);
	}
	
}



