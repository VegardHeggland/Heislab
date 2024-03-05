#include "queueSystem.h"

Order queueWithOrders[10];

void addOrder() {

        for(int inputFloor = 0; inputFloor < N_FLOORS; inputFloor++){        
            for(int inputBtn = 0; inputBtn < N_BUTTONS; inputBtn++){
                
                int btnPressed = elevio_callButton(inputFloor, inputBtn);
                
                if(btnPressed == 1) {
                    ligthOn(inputFloor, inputBtn); 
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

void removeOrder(){ 
    
    queueWithOrders[0].activeOrder = false;
    
    if(queueWithOrders[0].btnType == 2) {
        lightOff(queueWithOrders[0].designatedFloor, queueWithOrders[0].btnType);
    } else {
        lightOff(queueWithOrders[0].floor, queueWithOrders[0].btnType);
    }
    
    for (int i = 0; i < MAX_ORDERS-1; i++){
        
        queueWithOrders[i].btnType = queueWithOrders[i+1].btnType;
        queueWithOrders[i].floor = queueWithOrders[i+1].floor;
        queueWithOrders[i].designatedFloor = queueWithOrders[i+1].designatedFloor;
        queueWithOrders[i].activeOrder = queueWithOrders[i+1].activeOrder;
        
        if(queueWithOrders[i].activeOrder == false) {
            break;
        
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


        if(queueWithOrders[0].activeOrder == true) {
            switch (queueWithOrders[0].btnType) {

            case 0: //Bestilling utenfor heis, opp

                if(queueWithOrders[0].floor > lastDefinedFloor) {
                    elevio_motorDirection(DIRN_UP);
                } else if (queueWithOrders[0].floor < lastDefinedFloor) {
                    elevio_motorDirection(DIRN_DOWN);
                } else {
                    elevio_motorDirection(DIRN_STOP);
                    removeOrder();
                    door();
                } break;
                

            case 1: //Bestilling utenfor heis, ned

                if(queueWithOrders[0].floor > lastDefinedFloor) {
                    elevio_motorDirection(DIRN_UP);

                } else if (queueWithOrders[0].floor < lastDefinedFloor) {
                    elevio_motorDirection(DIRN_DOWN);

                } else {
                    elevio_motorDirection(DIRN_STOP);
                    removeOrder();
                    door();
                } break;
                

            case 2: //Bestilling fra heisen
                if(queueWithOrders[0].designatedFloor > lastDefinedFloor) {
                    elevio_motorDirection(DIRN_UP);

                } else if (queueWithOrders[0].designatedFloor < lastDefinedFloor) {
                    elevio_motorDirection(DIRN_DOWN);

                } else {
                    elevio_motorDirection(DIRN_STOP);
                    removeOrder();
                    door();
                } break;
            }
            
        }
        if(elevio_stopButton()) {
            break;
        }

    }

    for (int i = 0; i < MAX_ORDERS; i++) {
        printf("%d, %d, %d, %d\n", queueWithOrders[i].btnType, queueWithOrders[i].designatedFloor, queueWithOrders[i].floor, queueWithOrders[i].activeOrder);
    }
}
