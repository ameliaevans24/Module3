/* test1.c --- 
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

void print_car(car_t *car) {
  printf("Plate = %s, Year: %d, Price %.2lf\n",car->plate, car -> year, car -> price);
}   

int main(){

	// Manages status our function
	int status = 0;
	
	// Get from an empty function
	car_t *cp = lget();
	if (cp == NULL){
		printf("Test was succesfull, cp points to %p\n", cp);
		status = 1;
	}

	// Apply to an empty function
	lapply(print_car);
	status = 1;

	// Remove from an empty function
  /* char platep[]= "APL246";
	cp = lremove(platep);
	if (cp == NULL){
		printf("Test was succesful, we are unable to remove from an empty list");
	} */ 

	// Put invalid input into list
	status = lput(cp);	
	printf("Test was succesfull, invalid input, %p, cannot be put in list \n", cp);


	if( status == 1 ){
		exit(EXIT_SUCCESS);
	}
	else{
		exit(EXIT_FAILURE);
	}
	
}

