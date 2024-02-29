#include "queueSystem.h"
#include "stdbool.h"

FloorSignals signalArray[N_FLOORS];

void updateFloorSignals() {
    for (int floor = 0; floor < N_FLOORS; floor++) {
        signalArray[floor].hallUpActivated = elevio_callButton(floor, 0);
        signalArray[floor].hallDownActivated = elevio_callButton(floor, 1);
        signalArray[floor].inCabOrder = elevio_callButton(floor, 2);
             
    }
}

Order queueWithOrders[10];

void addOrder(ButtonType inputBtn, int inputFloor, int inputDesignatedFloor) {
    for (int i = 0; i < MAX_ORDERS; i++) {
        if(queueWithOrders[i].activeOrder == false) {
            queueWithOrders[i].btnType = inputBtn;
            if (inputBtn != 2) {
                queueWithOrders[i].currentFloor = inputFloor;
                queueWithOrders[i].designatedFloor = -1;
            } else {
                queueWithOrders[i].designatedFloor = inputDesignatedFloor;
                queueWithOrders[i].currentFloor = -1;
            }
            queueWithOrders[i].activeOrder = true;
            break;
        }
    }
}

void removeOrder(int index){ //Kanskje bytte fra index til etasje. Altså fjerne alle ordre med denne sluttetasjen 
    for (int i = index; i < MAX_ORDERS-1; i++){
        queueWithOrders[i].btnType = queueWithOrders[i+1].btnType;
        queueWithOrders[i].currentFloor = queueWithOrders[i+1].currentFloor;
        queueWithOrders[i].designatedFloor = queueWithOrders[i+1].designatedFloor;
        queueWithOrders[i].activeOrder = queueWithOrders[i+1].activeOrder;
        
        if(queueWithOrders[i].activeOrder == false) {
            break;
        }
        printf("i: %d\n", i);
        if (i == 8) {
            queueWithOrders[i+1].activeOrder = false;
        }
    }
} 


//Bruke lampen til å sjekke eller signalmatrise for å hindre mye trykking