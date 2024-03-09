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

void removeOrder(int currentFloor){ 
    int index; 
    for (int i = 0; i < MAX_ORDERS; i++) {
        if (queueWithOrders[i].floor == currentFloor || queueWithOrders[i].designatedFloor == currentFloor) {
            index = i;
            queueWithOrders[i].activeOrder = false;
            
            if(queueWithOrders[i].btnType == 2) {
                lightOff(queueWithOrders[i].designatedFloor, queueWithOrders[i].btnType);
            } else {
                lightOff(queueWithOrders[i].floor, queueWithOrders[i].btnType);
            }
    
            for (int j = 0; j < MAX_ORDERS-1; j++){
                queueWithOrders[j].btnType = queueWithOrders[j+1].btnType;
                queueWithOrders[j].floor = queueWithOrders[j+1].floor;
                queueWithOrders[j].designatedFloor = queueWithOrders[j+1].designatedFloor;
                queueWithOrders[j].activeOrder = queueWithOrders[j+1].activeOrder;
                
                if(queueWithOrders[j].activeOrder == false) {
                    break;
            
                }
            }
        }
    } 
}





void runElevator() {
    int lastDefinedFloor;
    MotorDirection currentDirection;

    while(1) {
        int currentFloor = elevio_floorSensor();
        if (currentFloor != -1) {
            lastDefinedFloor = currentFloor;
        }
        elevio_floorIndicator(lastDefinedFloor);
        
        
        addOrder();
        if (elevio_stopButton() == 1) {
            stopActivated();
        }

        for (int i = 0; i < MAX_ORDERS; i++) {
            if (queueWithOrders[i].activeOrder == true) {
                
                if (queueWithOrders[i].btnType == 0 && currentDirection == DIRN_UP) {
                    if(currentFloor == queueWithOrders[i].floor){
                        elevio_motorDirection(DIRN_STOP);
                        removeOrder(currentFloor);
                        door();
                    }
                }
                else if (queueWithOrders[i].btnType == 1 && currentDirection == DIRN_DOWN) {
                    if(currentFloor == queueWithOrders[i].floor){
                        elevio_motorDirection(DIRN_STOP);
                        removeOrder(currentFloor);
                        door();
                    }
                }
                else if (queueWithOrders[i].btnType == 2 && queueWithOrders[i].designatedFloor == currentFloor) {
                    elevio_motorDirection(DIRN_STOP);
                    removeOrder(currentFloor);
                    door();
                }        
            }
        }


        if(queueWithOrders[0].activeOrder == true) {
            switch (queueWithOrders[0].btnType) {

            case 0: //Bestilling utenfor heis, opp

                if(queueWithOrders[0].floor > lastDefinedFloor) {
                    currentDirection = DIRN_UP;
                    
                } else if (queueWithOrders[0].floor < lastDefinedFloor) {
                    currentDirection = DIRN_DOWN;
                    
                } else {
                    currentDirection = DIRN_STOP;
                    elevio_motorDirection(DIRN_STOP);
                    removeOrder(lastDefinedFloor);
                    door();
                } 
                elevio_motorDirection(currentDirection);
                break;
                

            case 1: //Bestilling utenfor heis, ned

                if(queueWithOrders[0].floor > lastDefinedFloor) {
                    currentDirection = DIRN_UP;

                } else if (queueWithOrders[0].floor < lastDefinedFloor) {
                    currentDirection = DIRN_DOWN;

                } else {
                    currentDirection = DIRN_STOP;
                    elevio_motorDirection(DIRN_STOP);
                    removeOrder(lastDefinedFloor);
                    door();
                } 
                elevio_motorDirection(currentDirection);
                break;
                

            case 2: //Bestilling fra heisen
                if(queueWithOrders[0].designatedFloor > lastDefinedFloor) {
                    currentDirection = DIRN_UP;

                } else if (queueWithOrders[0].designatedFloor < lastDefinedFloor) {
                    currentDirection = DIRN_DOWN;

                } else {
                    currentDirection = DIRN_STOP;
                    elevio_motorDirection(DIRN_STOP);
                    removeOrder(lastDefinedFloor);
                    door();
                } 
                elevio_motorDirection(currentDirection);
                break;

            }
        }
    }
}
