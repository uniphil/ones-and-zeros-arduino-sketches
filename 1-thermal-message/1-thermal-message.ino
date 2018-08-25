/*
 Looking at the rear of the unit, the left connector is for power (red/black cable). The right connector is 
 for serial communication. The middle pin on the right connector is yellow and is the pin to transmit serial 
 data into. The green pin on the end of the right connector is what serial comes out of.
 */
#include <SoftwareSerial.h>

SoftwareSerial Thermal(10, 9);  // Software RX, TX

void setup() {
  Thermal.begin(19200);  // Setup soft serial for ThermalPrinter control

  char message[] = {
    0b01001000,  // H
    0b01000101,  // E
    0b01001100,  // L
    0b01001100,  // L
    0b01001111,  // O
    0b00001010,  // [lf]
    0b00001010,  // [lf]
  };

  Thermal.print(message);
}

void loop() {}

