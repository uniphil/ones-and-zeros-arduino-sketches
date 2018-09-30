#include <SoftwareSerial.h>
#include <Adafruit_Thermal.h>
#include <MicroView.h>

SoftwareSerial ser(5, 6);  // soft RX, TX
Adafruit_Thermal Thermal(&ser);

void setup() {
  String name = "Phil";
  String pronouns = "they/him";

  uView.begin();
  uView.clear(PAGE);
  uView.print("Welcome,\n");
  uView.print(name);
  uView.print("!");
  uView.display();

  pinMode(2, OUTPUT); digitalWrite(2, LOW);
  pinMode(3, INPUT); digitalWrite(3, HIGH);

  ser.begin(9600);
  Thermal.begin(0xCC);  // as dark as we can get for label printing

  Thermal.boldOn();
  Thermal.println("Hello world!");
  Thermal.boldOff();

  Thermal.println("\n\nmy name is\n");
  
  Thermal.doubleHeightOn();
  Thermal.doubleWidthOn();
  Thermal.println(name);
  Thermal.doubleWidthOff();
  Thermal.doubleHeightOff();
  
  Thermal.feed();
  Thermal.println(pronouns);

//  Thermal.feed(12);
  Thermal.println("@onesandzeros: binary solo");
  Thermal.feed(5);
}

void loop() {
  if (!digitalRead(3)) {
    Thermal.feedRows(1);
    delay(16);
  }
}
