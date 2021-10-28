#include <Arduino.h>
#include <LibRobus.h>

void AvancerPID(uint32_t nbrPulse);
void AvancerDroite(uint32_t nbrPulse, float difference);
void AvancerGauche(uint32_t nbrPulse, float difference);
void TournerDroitePID(uint32_t nbrPulse);
void TournerGauchePID(uint32_t nbrPulse);
void Tourner90DroitePID(void);
void Tourner90GauchePID(void);