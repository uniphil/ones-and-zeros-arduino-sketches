#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>

SoftwareSerial SSer(5, 6);  // soft RX, TX
Adafruit_Thermal Thermal(&SSer);

void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);  // ground

  
  SSer.begin(19200);  // Setup soft serial for ThermalPrinter control
  while(!SSer);  // fix for leonardo
  Thermal.begin(0xFF);  // as dark as we can get for label printing

  Thermal.println("Hello world!");
  Thermal.println("\nmy name is");
  Thermal.doubleHeightOn();
  Thermal.doubleWidthOn();
  Thermal.println("Eren");
  Thermal.doubleWidthOff();
  Thermal.doubleHeightOff();
  Thermal.println("\n\nones and zeros: binary solo");
}

void loop() {
  // put your main code here, to run repeatedly:

}
