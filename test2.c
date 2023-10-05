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

void print_car(car_t *car) {
  printf("Plate = %s, Year: %d, Price %.2lf\n",car->plate, car -> year, car -> price);
}   

int main(){

	int status = 0;
	car_t car1 = {NULL, "ABC123", 2020, 20000};
	car_t car2 = {NULL, "DEF456", 2024, 45000};
	car_t car3 = {NULL, "GHI789", 2000, 2003};
	
	// Put into a empty function
	lput(&car1);
	lput(&car2);
	lput(&car3);


	// Get from a non-empty list
	car_t *first_car = lget();
	print_car(first_car);
	if (first_car == NULL){
		printf("Test was unsuccesfull, first car points to %p\n\n", first_car);
		status = 0;
	}
	else{
		printf("Test was succesful, first car points to %p\n\n", first_car);
		status = 1;
	}

  // Apply to a non-empty function
	lapply(print_car);
	printf("\n");
	status = 1;

	// Put into a non-empty list
	car_t car4 = {NULL, "CooLvn", 2017, 30000};
	lput(&car4);
	lapply(print_car);
	

	if( status == 1 ){
		exit(EXIT_SUCCESS);
	}
	else{
		exit(EXIT_FAILURE);
		} 
	

	//Print out car info
	//lapply(print_car);
	//	exit(EXIT_SUCCESS);

	/*	//Remove car from list
	char platep[] = "DEF456";
	car_t *removed_car = lremove(platep);
	print_car(removed_car); */
}

