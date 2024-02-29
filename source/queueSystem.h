#pragma once


typedef struct FloorSignals{};
typedef struct Order{};

void updateFloorSignals();

void addOrder(); //Legg til ordre bakerst i listen.  Parameter eller sjekke mot signalMatrkse?
void removeOrder(int index); //iterere gjennom liste og fjerne ordre på indeks = teller under iterering? INkludere dytting av listen fremover
