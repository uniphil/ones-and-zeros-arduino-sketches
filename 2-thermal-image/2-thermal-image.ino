#include <SoftwareSerial.h>

SoftwareSerial Thermal(10, 9);  // Software RX, TX

void setup() {
  Thermal.begin(19200);  // Setup soft serial for ThermalPrinter control

  // tell the printer we're going to send an image
  Thermal.write(0b00010010);  // [DC2]
  Thermal.write(0b00101010);  // '*'
  Thermal.write(0b00010000);  // 16, the height
  Thermal.write(0b00000010);  // 2, the width (in bytes, x8 pixels)
  char im[] = {
    0b00110011, 0b00110011,
    0b01100110, 0b01100110,
    0b11001100, 0b11001100,
    0b10011001, 0b10011001,
    0b00110011, 0b00110011,
    0b01100110, 0b01100110,
    0b11001100, 0b11001100,
    0b10011001, 0b10011001,
    0b00110011, 0b00110011,
    0b01100110, 0b01100110,
    0b11001100, 0b11001100,
    0b10011001, 0b10011001,
    0b00110011, 0b00110011,
    0b01100110, 0b01100110,
    0b11001100, 0b11001100,
    0b10011001, 0b10011001,
  };
  Thermal.print(im);

  Thermal.write(0b00001010);  // [LF] line feed
  Thermal.write(0b00001010);  // [LF] line feed
}

void loop() {}

