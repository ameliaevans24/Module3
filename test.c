/* test.c --- 
 * 
 * 
 * Author: Amelia H. Evans
 * Created: Sun Oct  1 21:43:56 2023 (-0400)
 * Version: 
 * 
 * Description: Test success case for list.c 
 * 
 */

# include "list.h"

void print_car(car_t *car) {
	printf("Plate = %s, Year: %d, Price %.2lf\n",car->plate, car -> year, car -> price);
}

int main(){
	//Initialize cars
	car_t car1 = {NULL, "ABC123", 2020, 20000.0};
	car_t car2 = {NULL, "DEF456", 2019, 24000.0};
	car_t car3 = {NULL, "XYZ789", 2000, 18000.0};

	//Add to cars to list
	lput(&car1);
	lput(&car2);
	lput(&car3);

	//Print car list
	lapply(print_car);

	//Remove car
	char plate_remove[] = "DEF456";
	car_t *removed_car = lremove(plate_remove);
	if (removed_car != NULL) {
		printf("\n Removed: %s\n",plate_remove);
		print_car(removed_car); 
	}

	//Get first car
	car_t *first_car = lget();
	if (first_car != NULL){
		printf("\nFirst car:");
		print_car(first_car);
	}
	return 0;
}
	
