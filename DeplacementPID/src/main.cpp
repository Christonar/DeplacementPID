#include <Arduino.h>
#include <LibRobus.h>
#include "PID.h"


void setup() {
  // put your setup code here, to run once:
  BoardInit();
  delay(1500);
  //AvancerPID(14000); // Avancer 1 metre 700 pulses = 5cm.
  
  for(uint8_t i = 0; i < 4 ; i++)
  {
    //TournerDroitePID(1675); // 1675 = 90 degrès droite
    //TournerGauchePID(1680);  // 1680 = 90 degrès gauche
    Tourner90GauchePID();
    delay(1500);
  }
  for(uint8_t i = 0; i < 4 ; i++)
  {
    //TournerDroitePID(1675); // 1675 = 90 degrès droite
    //TournerGauchePID(1680);  // 1680 = 90 degrès gauche
    Tourner90DroitePID();
    delay(1500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}