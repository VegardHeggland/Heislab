#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "startUp.h"
#include "utilities.h"



int main(){
    elevio_init();
    
    elevatorStartUp();
  
    return 0;
}
