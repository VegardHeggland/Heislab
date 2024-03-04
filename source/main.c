#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "startUp.h"
#include "queueSystem.h"

extern Order queueWithOrders[10];

int main(){
    elevio_init();
    elevatorStartUp();
    printf("queueSystem: \n");
    runElevator();
    /*
    for (int i = 0; i < MAX_ORDERS; i++) {
        printf("Bestilling: currentFloor: %d, designatedFloor: %d, activeOrder?: %d\n" , queueWithOrders[i].floor, queueWithOrders[i].designatedFloor, queueWithOrders[i].activeOrder);
    } printf("\n");

    for (int i = 0; i < 8; i++) {
        addOrder(1, 3, -1);
    }

   for (int i = 0; i < MAX_ORDERS; i++) {
        printf("Bestilling: currentFloor: %d, designatedFloor: %d, activeOrder?: %d\n" , queueWithOrders[i].floor, queueWithOrders[i].designatedFloor, queueWithOrders[i].activeOrder);
    } printf("\n");
    
    removeOrder(6);
    
    for (int i = 0; i < MAX_ORDERS; i++) {
        printf("Bestilling: currentFloor: %d, designatedFloor: %d, activeOrder?: %d\n" , queueWithOrders[i].floor, queueWithOrders[i].designatedFloor, queueWithOrders[i].activeOrder);
    } printf("\n");
    */
    return 0;
}
