#include "startUp.h"
#include "driver/elevio.h"

void elevatorStartUp() {
    int floor;
    while(1) {
        elevio_motorDirection(DIRN_UP);
        floor = elevio_floorSensor();
        if(floor== 0 || floor== 1 || floor == 2 || floor ==3) {
            elevio_motorDirection(DIRN_STOP);
            break;
        } 
    }    
}
