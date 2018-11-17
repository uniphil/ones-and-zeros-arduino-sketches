/**
 * Print images more easily!
 *
 * Find the image converter tool here:
 * https://codepen.io/uniphil/full/BGZXYL/
 **/
#include <SoftwareSerial.h>

#define GND_PIN 8
#define RX_PIN 10
#define TX_PIN 9

// Copy the image data here!

// Copy the drawImage function here!

SoftwareSerial Thermal = SoftwareSerial(RX_PIN, TX_PIN);

void setup() {
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW);
  Thermal.begin(19200);

  // you can put print settings here to make the printer work better
  // copy the code from from:
  // https://gist.github.com/uniphil/636f667d9a2e73f347a1c869cced5ab9
  // and look at your kit's parts list for some setings to start with

  Thermal.println("hello!");

  // Copy the draw command here!
}

void loop() {
}
