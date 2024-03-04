#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "startUp.h"
#include "queueSystem.h"

extern Order queueWithOrders[10];

int main(){
    elevio_init();
    elevatorStartUp();
    door();
    //runElevator();
  
    return 0;
}
