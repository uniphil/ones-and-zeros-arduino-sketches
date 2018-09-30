#include <SoftwareSerial.h>

SoftwareSerial Thermal(10, 9);  // Software RX, TX

void setup() {
  Thermal.begin(19200);  // Setup soft serial for ThermalPrinter control

  // set print speed and heat
  Thermal.write(27);
  Thermal.write(55);
  Thermal.write(7);   // default 64 dots = 8*('7'+1)
  Thermal.write(255); // heat time, default 80 or 800us
  Thermal.write(255); // heat interval, default 2 or 20us

  // set print density and timeout
  Thermal.write(18);
  Thermal.write(35);
  Thermal.write((15<<4) | 15); //Combination of printDensity and printBreakTime


  // tell the printer we're going to send an image
  Thermal.write(0b00010010);  // [DC2]
  Thermal.write(0b00101010);  // '*'
  Thermal.write(0b00010000);  // 16, the height
  Thermal.write(0b00000010);  // 2, the width (in bytes, x8 pixels)
  // :/
  char im[] = {
    0b00000111, 0b11100000,
    0b00011000, 0b00011000,
    0b00100000, 0b00000100,
    0b01000000, 0b00000010,
    0b01000100, 0b00100010,
    0b10001100, 0b00110001,
    0b10000000, 0b00000001,
    0b10000000, 0b00000001,
    0b10000000, 0b00000001,
    0b10011000, 0b00000001,
    0b10000110, 0b00000001,
    0b01000001, 0b10000010,
    0b01000000, 0b01100010,
    0b00100000, 0b00000100,
    0b00011000, 0b00011000,
    0b00000111, 0b11100000,
  };
  // blank 16x16
  // char im[] = {
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  //   0b00000000, 0b00000000,
  // };
  Thermal.print(im);

  Thermal.print(0b00001010);  // [LF] line feed
  Thermal.print(0b00001010);  // [LF] line feed
}

void loop() {}

