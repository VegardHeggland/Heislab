#include "utilities.h"
#include "queueSystem.h"
#include <sys/time.h>

extern Order queueWithOrders[10];


void ligthOn(int floor, ButtonType btnType) {
    elevio_buttonLamp(floor, btnType, 1); 
}

void lightOff(int floor, ButtonType btnType) {
    elevio_buttonLamp(floor, btnType, 0); 
}
void threeSecPause() {
    time_t timestamp = time(0);
    time_t newTimestamp;
        while (newTimestamp-timestamp < 3){
            newTimestamp = time(0);
            addOrder(); 
        }
}

void door(){
    if(elevio_floorSensor() != -1 ){
        elevio_doorOpenLamp(1);
        elevio_stopLamp(0);
        threeSecPause();
        

        while(elevio_obstruction() == 1) {
            threeSecPause();
        }
        elevio_doorOpenLamp(0);  
    }
}

void resetOrders() {
     for (int i = 0; i < MAX_ORDERS; i++) {
        queueWithOrders[i].floor = -1;
        queueWithOrders[i].designatedFloor = -1;
        queueWithOrders[i].activeOrder = false;
    }
    for(int f = 0; f < N_FLOORS; f++){        
        for(int b = 0; b < N_BUTTONS; b++){
            lightOff(f, b);
            elevio_stopLamp(0);
        }
    }
}

void stopActivated() {
    resetOrders();
    elevio_stopLamp(1);
    elevio_motorDirection(DIRN_STOP);
    while(elevio_stopButton() == 1) {
        door();
    }
    
    elevio_stopLamp(0);
}