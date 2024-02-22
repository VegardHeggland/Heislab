#include "utilities.h"
#include "driver/elevio.h"


void ligthON(int floor, ButtonType button) {
    elevio_buttonLamp(floor, button, 1); 
}

void lightOff(int floor, ButtonType button) {
    elevio_buttonLamp(floor, button, 0); 
}