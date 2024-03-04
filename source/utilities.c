#include "utilities.h"


void ligthON(int floor, ButtonType button) {
    elevio_buttonLamp(floor, button, 1); 
}

void lightOff(int floor, ButtonType button) {
    elevio_buttonLamp(floor, button, 0); 
}

void door(){
    if(elevio_floorSensor() != -1 ){
        elevio_doorOpenLamp(1);
        sleep(3);
        while (elevio_obstruction() == 0)
        {
        elevio_doorOpenLamp(0);
        }
    }
}