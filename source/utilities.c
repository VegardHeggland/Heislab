#include "utilities.h"


void ligthOn(int floor, ButtonType btnType) {
    elevio_buttonLamp(floor, btnType, 1); 
}

void lightOff(int floor, ButtonType btnType) {
    elevio_buttonLamp(floor, btnType, 0); 
}

void door(){
    if(elevio_floorSensor() != -1 ){
        elevio_doorOpenLamp(1);
        sleep(3);
        while (1){
            if (elevio_obstruction() == 0) {
                sleep(3);
                elevio_doorOpenLamp(0);
                break;
            }
        }
    }
}