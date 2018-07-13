/*
 To use this example code, attach
 Arduino : Printer
 D2 : Green wire (Printer TX)
 D3 : Yello wire (Printer RX)
 VIN (9V wall adapter) : Red wire
 GND : Black wires
 Open Arduino serial window at 38400bps. Turn on line endings!
 
 Looking at the rear of the unit, the left connector is for power (red/black cable). The right connector is 
 for serial communication. The middle pin on the right connector is yellow and is the pin to transmit serial 
 data into. The green pin on the end of the right connector is what serial comes out of.
 
 The thermal printer ships with default 19200bps baud rate. To discover the baud rate, hold down the 
 feed button, then attach the printer to the Vin pin on the Arduino. You'll need more current than a USB connection is
 capable of. The printer should go into demo mode. The final information after the Character Table (ABCDEFG), 
 is the baudrate and firmware information. 
 
 A 5V wall adapter worked fine.
 A 5V USB connection was not enough power to allow the roller to advance the paper.
 A 9V source caused the printer to run very fast, but did not complete the demo mode.
 
 Unit uses 4.8mA @ 9V in standby.
 Unit uses about 1.3A! @ 9V during printing. 
 */
#include <SoftwareSerial.h>

SoftwareSerial Thermal(10, 9);  // Soft RX from printer on D2, soft TX out to printer on D3

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
    0,           // [nul]
  };

  Thermal.print(message);
}

void loop() {}

