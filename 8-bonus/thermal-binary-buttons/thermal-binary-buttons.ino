#include <SoftwareSerial.h>

#define ZERO_INPUT 0
#define ONE_INPUT 1

SoftwareSerial Thermal(10, 9);  // software RX, TX

char* controls[32] = {
  "NUL",
  "SOH",
  "STX",
  "ETX",
  "EOT",
  "ENQ",
  "ACK",
  "BEL",
  "BS",
  "TAB",
  "LF",
  "VT",
  "FF",
  "CR",
  "SO",
  "SI",
  "DLE",
  "DC1",
  "DC2",
  "DC3",
  "DC4",
  "NAK",
  "SYN",
  "ETB",
  "CAN",
  "EM",
  "SUB",
  "ESC",
  "FS",
  "GS",
  "RS",
  "US",
};

void setup() {
  pinMode(ZERO_INPUT, INPUT);
  pinMode(ONE_INPUT, INPUT);
  digitalWrite(ZERO_INPUT, HIGH);
  digitalWrite(ONE_INPUT, HIGH);

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
}

void loop() {
  unsigned char toPrint = 0;
  for (int i = 0; i < 8; i++) {
    Thermal.print('\n');
    bool last;
    while (true) {
      bool zero = digitalRead(ZERO_INPUT);
      bool one = digitalRead(ONE_INPUT);
      if (digitalRead(ZERO_INPUT) == LOW) {
        last = 0;
        break;
      } else if (digitalRead(ONE_INPUT) == LOW) {
        toPrint |= 1 << (7 - i);
        last = 1;
        break;
      } else {
        continue;
      }
    }
    Thermal.print(last);
    delay(500);
  }
  Thermal.print("  ");
  if (toPrint < 0x20) {
    Thermal.print("[");
    Thermal.print(controls[toPrint]);
    Thermal.print("]");
  } else if (toPrint < 0x7F) {
    Thermal.print((char)toPrint);
  } else if (toPrint == 0x7F) {
    Thermal.print("[DEL]");
  } else {
    Thermal.print("(out of range)");
  }
  Thermal.print("\n");
}

