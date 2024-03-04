#include "queueSystem.h"
#include "stdio.h"
#include "utilities.h"

/* FloorSignals signalArray[N_FLOORS];

void updateFloorSignals() {
    for (int floor = 0; floor < N_FLOORS; floor++) {
        signalArray[floor].hallUpActivated = elevio_callButton(floor, 0);
        signalArray[floor].hallDownActivated = elevio_callButton(floor, 1);
        signalArray[floor].inCabOrder = elevio_callButton(floor, 2);
             
    }
}
*/

Order queueWithOrders[10];

void addOrder() {

        for(int inputFloor = 0; inputFloor < N_FLOORS; inputFloor++){        
            for(int inputBtn = 0; inputBtn < N_BUTTONS; inputBtn++){
                
                int btnPressed = elevio_callButton(inputFloor, inputBtn);
                
                if(btnPressed == 1) {
                    elevio_buttonLamp(inputFloor, inputBtn, 1); 
                        for (int i = 0; i < MAX_ORDERS; i++) {
                            if(queueWithOrders[i].activeOrder == false) {
                                queueWithOrders[i].btnType = inputBtn;
                                
                                if (inputBtn != 2) {
                                    queueWithOrders[i].floor = inputFloor;
                                    queueWithOrders[i].designatedFloor = -1;
                                } else {
                                    queueWithOrders[i].designatedFloor = inputFloor;
                                    queueWithOrders[i].floor = -1;
                                }
                                queueWithOrders[i].activeOrder = true;
                                break;
                            } else {
                                if (inputBtn == queueWithOrders[i].btnType && 
                                   (inputFloor == queueWithOrders[i].floor || inputFloor == queueWithOrders[i].designatedFloor)) {
                                    break;
                                }
                            }            
                        }
                }
            }
        }
}

void removeOrder(int index){ //Kanskje bytte fra index til etasje. Altså fjerne alle ordre med denne sluttetasjen 
    
    for (int i = index; i < MAX_ORDERS-1; i++){
        queueWithOrders[i].btnType = queueWithOrders[i+1].btnType;
        queueWithOrders[i].floor = queueWithOrders[i+1].floor;
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


void runElevator() { // Passe på håndtering og fjerning av så mange bestillinger som mulig samtidig.
    int lastDefinedFloor;

    while(1) {
        int currentFloor = elevio_floorSensor();
        if (currentFloor != -1) {
            lastDefinedFloor = currentFloor;
        }
        
        addOrder();


        /*
        switch (queueWithOrders[0].btnType) {

        case 0: //Bestilling utenfor heis, opp

            if(queueWithOrders[0].floor > lastDefinedFloor) {
                elevio_motorDirection(DIRN_UP);
            } else if (queueWithOrders[0].floor < lastDefinedFloor) {
                elevio_motorDirection(DIRN_DOWN);
            } else {
                elevio_motorDirection(DIRN_STOP);
                //removeOrder();
                //door();
            }
            

        case 1: //Bestilling utenfor heis, ned

             if(queueWithOrders[0].floor > lastDefinedFloor) {
                elevio_motorDirection(DIRN_UP);

            } else if (queueWithOrders[0].floor < lastDefinedFloor) {
                elevio_motorDirection(DIRN_DOWN);

            } else {
                elevio_motorDirection(DIRN_STOP);
                //removeOrder();
                //door();
            }
            

        case 2: //Bestilling fra heisen
            if(queueWithOrders[0].designatedFloor > lastDefinedFloor) {
                elevio_motorDirection(DIRN_UP);

            } else if (queueWithOrders[0].designatedFloor < lastDefinedFloor) {
                elevio_motorDirection(DIRN_DOWN);

            } else {
                elevio_motorDirection(DIRN_STOP);
                //removeOrder();
                //door();
            }
        }
        */

        if(elevio_stopButton()) {
            break;
        }

    }

    for (int i = 0; i < MAX_ORDERS; i++) {
        printf("%d, %d, %d, %d", queueWithOrders[i].btnType, queueWithOrders[i].designatedFloor, queueWithOrders[i].floor, queueWithOrders[i].activeOrder);
    }
}