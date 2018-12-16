/**
 * Print images more easily!
 *
 * Find the image converter tool here:
 * https://codepen.io/uniphil/full/BGZXYL/
 *
 **/
#include <SoftwareSerial.h>
#include "image.h"

#define GND_PIN 8
#define RX_PIN 10
#define TX_PIN 9

SoftwareSerial Thermal = SoftwareSerial(RX_PIN, TX_PIN);

void setup() {
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW);
  Thermal.begin(19200);

  // you can put print settings here for darker/better prints
  // copy the code from from:
  // https://gist.github.com/uniphil/636f667d9a2e73f347a1c869cced5ab9
  // and look at your kit's parts list for some setings to start with


  // From here until the "}" on line __ are the things we'll print
  Thermal.println("hello!");

  // Copy the draw command here!
  drawImage(&Thermal, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE);

}

void loop() {
}

void drawImage(Stream * ser, uint8_t w, uint16_t h, byte pgm[]) {
  byte row[48];
  for (uint16_t y = 0; y < h; y++) {
    for (uint8_t x = 0; x < w; x++) {
      row[x] = pgm_read_byte_near(pgm + y * w + x);
    }
    ser->write(0x12);
    ser->write('*');
    ser->write(1);
    ser->write(w);
    ser->write(row, w);
    delay(10 + w / 4);  // try not to fill up the buffer
  }
}
