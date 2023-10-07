/* qtest.c --- 
 * 
 * 
 * Author: Amelia H. Evans
 * Created: Fri Oct  6 15:29:14 2023 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
#include "queue.h"


#define MAXREG 15

//Define car struct
typedef struct car {
struct car *next;
char plate[MAXREG];
double price;
int year;
} car_t;

//define house struct
typedef struct house {
struct house *next;
char style[MAXREG];
double price;
int year;
} house_t;

//Define fruit struct
typedef struct fruit {
struct fruit *next; 
char type[MAXREG]; 
}
//Define print function 
void printq(queue_t *qp){
	printf("The element stored is a %s \n",qp); //print element stored in the queue
}
//define search funtion
bool searchfn(void* elementp,const void* keyp){

	  char *element = (char *)elementp;
    char *key = (char *)skey;
     
    return (*element == *key);	
}
//main function (to test qsearch and qapply)
int main(){
	
	//Define Elements
	car_t car1 = {NULL, "ABC123", 2020, 20000.0};
	house_t house1 = {NULL, "Colonial", 1809, 500000.0}; 
	fruit_t fruit1 = {NULL, "Banana"}; 
	
	//Initialize queue 
	*qp qopen(void); 
	
	//Put Elements in queue
	qput(qp, &fruit1);
	qput(qp, &house1); 
	qput(qp, &car1); 
	
	//Apply Function to queue
	qapply(printq); 
	
	//Use qsearch function
	qfind[] = "Colonial"; 
	queue_t *qfound = qsearch(qp, searchfn(house -> style,*qfind), *qfind); //Search queue for house of style Colonial	
}/* qtest.c --- 
 * 
 * 
 * Author: Amelia H. Evans
 * Created: Fri Oct  6 15:29:14 2023 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
#include "queue.h"


#define MAXREG 15

//Define car struct
typedef struct car {
struct car *next;
char plate[MAXREG];
double price;
int year;
} car_t;

//define house struct
typedef struct house {
struct house *next;
char style[MAXREG];
double price;
int year;
} house_t;

//Define fruit struct
typedef struct fruit {
struct fruit *next; 
char type[MAXREG]; 
}
//Define print function 
void printq(queue_t *qp){
	printf("The element stored is a %s \n",qp); //print element stored in the queue
}
//define search funtion
bool searchfn(void* elementp,const void* keyp){

	char *element = (char *)elementp;
    char *key = (char *)skey;
     
    return (*element == *key);	
}
//main function (to test qsearch and qapply)
int main(){
	
	//Define Elements
	car_t car1 = {NULL, "ABC123", 2020, 20000.0};
	house_t house1 = {NULL, "Colonial", 1809, 500000.0}; 
	fruit_t fruit1 = {NULL, "Banana"}; 
	
	//Initialize queue 
	*qp qopen(void); 
	
	//Put Elements in queue
	qput(qp, &fruit1);
	qput(qp, &house1); 
	qput(qp, &car1); 
	
	//Apply Function to queue
	qapply(printq); 
	
	//Use qsearch function
	qfind[] = "Colonial"; 
	queue_t *qfound = qsearch(qp, searchfn(house -> style,*qfind), *qfind); //Search queue for house of style Colonial	
}
