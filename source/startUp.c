#include "startUp.h"
#include "driver/elevio.h"

void elevatorStartUp() {
    int currentFloor = -1;
    while(currentFloor == -1) {
        elevio_motorDirection(DIRN_UP);
        currentFloor = elevio_floorSensor();
    }    
}
