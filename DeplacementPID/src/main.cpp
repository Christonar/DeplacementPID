#include <Arduino.h>
#include <LibRobus.h>
#include "PID.h"


void setup() {
  // put your setup code here, to run once:
  BoardInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  AvancerPID(140000); // Avancer 1 metre 700 pulses = 5cm 
}