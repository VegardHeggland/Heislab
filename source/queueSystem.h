#pragma once
#include "driver/elevio.h"
#include "stdbool.h" 

#define MAX_ORDERS 10

typedef struct {
    bool hallUpActivated;
    bool hallDownActivated;
    bool inCabOrder;
} FloorSignals;

typedef struct {
    ButtonType btnType; 
    int currentFloor;
    int designatedFloor;
    bool activeOrder;
} Order; 

void updateFloorSignals();

void addOrder(ButtonType inputBtn, int inputFloor, int inputDesignatedFloor); //Legg til ordre bakerst i listen.  Parameter eller sjekke mot signalMatrkse?

void removeOrder(int index); //iterere gjennom liste og fjerne ordre på indeks = teller under iterering? INkludere dytting av listen fremover
