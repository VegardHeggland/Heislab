#include "startUp.h"
#include "queueSystem.h"

extern Order queueWithOrders[10];

void elevatorStartUp() {
    int floor = -1;
    while(floor == -1){
        elevio_motorDirection(DIRN_UP);
        floor = elevio_floorSensor();
    }
    elevio_motorDirection(DIRN_STOP);

     for (int i = 0; i < MAX_ORDERS; i++) {
        queueWithOrders[i].floor = -1;
        queueWithOrders[i].designatedFloor = -1;
        queueWithOrders[i].activeOrder = false;
    } 
}
