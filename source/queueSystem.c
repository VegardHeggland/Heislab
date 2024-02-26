#include "queueSystem.h"
#include "driver/elevio.h"
#include "stdbool.h"


typedef struct {
    bool hallUpActivated;
    bool hallDownActivated;
    bool inCabOrder;
} FloorSignals;

FloorSignals signalArray[N_FLOORS];

void updateFloorSignals() {
    for (int floor = 0; floor < N_FLOORS; floor++) {
        signalArray[floor].hallUpActivated = elevio_callButton(floor, 0);
        signalArray[floor].hallDownActivated = elevio_callButton(floor, 1);
        signalArray[floor].inCabOrder = elevio_callButton(floor, 2);
             
    }
}

typedef struct {
    ButtonType btnType; 
    int currentFloor;
    int designatedFloor;
} Order; 

Order queueWithOrders[10];

