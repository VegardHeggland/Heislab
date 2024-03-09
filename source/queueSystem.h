#pragma once
#include "driver/elevio.h"
#include "stdbool.h"
#include "utilities.h"

#define MAX_ORDERS 10

typedef struct {
    ButtonType btnType; 
    int floor;
    int designatedFloor;
    bool activeOrder;
} Order; 

void addOrder();

void removeOrder(int currentFloor);

void runElevator();
