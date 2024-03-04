#include "utilities.h"


void ligthOn(int floor, int btnType) {
    elevio_buttonLamp(floor, btnType, 1); 
}

void lightOff(int floor, int btnType) {
    elevio_buttonLamp(floor, btnType, 0); 
}