#include <Arduino.h>
#include <LibRobus.h>

void AvancerPID(uint32_t nbrPulse);
void AvancerDroitePID(uint32_t nbrPulse, uint32_t difference);
void TournerDroitePID(uint32_t nbrPulse);
void TournerGauchePID(uint32_t nbrPulse);