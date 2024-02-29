#include "startUp.h"
#include "driver/elevio.h"
#include "queueSystem.h"
#include "stdbool.h"
extern Order queueWithOrders[10];

void elevatorStartUp() {
    int floor = -1;
    while(floor == -1){
        elevio_motorDirection(DIRN_UP);
        floor = elevio_floorSensor();
    }

     for (int i = 0; i < MAX_ORDERS; i++) {
        queueWithOrders[i].currentFloor = -1;
        queueWithOrders[i].designatedFloor = -1;
        queueWithOrders[i].activeOrder = false;
    } 
}
