#include <SoftwareSerial.h>

SoftwareSerial Thermal(10, 9);  // Software RX, TX

void setup() {
  Thermal.begin(19200);  // Setup soft serial for ThermalPrinter control

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

  // // here is a blank 16x16 to start with:
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


  // send all the bytes in the image, one by one
  // the "2 * 16" on the next line is width * height -- it must match the image commands above!
  for (int i = 0; i < 2 * 16; i++) {
    Thermal.write(im[i]);
  }

  // feed two lines (otherwise the image is still inside the printer)
  Thermal.print(0b00001010);  // [LF] line feed
  Thermal.print(0b00001010);  // [LF] line feed
}

void loop() {}

