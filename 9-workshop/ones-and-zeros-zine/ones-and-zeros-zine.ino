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

#define BAUD 9600
#define DOTS 64
#define HEAT_TIME 127
#define HEAT_INTERVAL 64
#define PRINT_DENSITY 0b000
#define PRINT_TIMEOUT 0b00000

#define EMPH 0b00001000
#define TALL 0b00010000
#define WIDE 0b00100000
#define DEL  0b01000000
#define UL   0b10000000

void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  
  // don't do anything until a jumper conntcts pins 2-3
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(2, LOW);  // make it like a ground
  digitalWrite(3, HIGH);  // turn on internal pull-up
  while(digitalRead(3));  // wait for it to go low (jumper connect to ground)


  Thermal.begin(BAUD);  // Setup soft serial for ThermalPrinter control

  delay(1000);

  //Modify the print speed and heat
  Thermal.write(27);
  Thermal.write(55);
  Thermal.write(DOTS);   // default 64 = 8*('7'+1)
  Thermal.write(HEAT_TIME); // default 80 or 800us
  Thermal.write(HEAT_INTERVAL); // default 2 or 20us

  //Modify the print density and timeout
  Thermal.write(18);
  Thermal.write(35);
  Thermal.write((byte)((PRINT_DENSITY<<5) | PRINT_TIMEOUT));
  delay(100);

  // set up text
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH | TALL | WIDE);
  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  Thermal.println("Ones and Zeros");
  // big text off
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);

  delay(1000);

  Thermal.print("\n\n\n");

  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" Social Rules \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(1000);

  Thermal.println("- No feigning surprise");
  Thermal.println("- No well-actuallys");
  Thermal.println("- No back-seat driving");
  Thermal.println("- No subtlisms");
  Thermal.println(F("\nIf someone says, \"hey, you just feigned surprise,\" or \"that's subtly sexist,\" don't worry. Just apologize, reflect for a second, and move on."));

  delay(1000);

  Thermal.print("\n\n\n");

  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" How to Count in Binary \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(1000);

  Thermal.println("Count like you normally do, but remove all the numbers that aren't just 1s and 0s. eg.,\n\n");
  Thermal.println("0,");
  Thermal.println("1,");
  
  // del
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(DEL);
  Thermal.println("-- 2, 3, 4, 5, 6, 7, 8, 9,");
  // undel
  Thermal.write(27);
  Thermal.write("!");
  Thermal.write((byte)0);

  Thermal.println("10,");
  Thermal.println("11,");
  // del
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(DEL);
  Thermal.println("-- 12, 13, ... 98, 99,");
  // undel
  Thermal.write(27);
  Thermal.write("!");
  Thermal.write((byte)0);

  Thermal.println("100,");
  Thermal.println("101,");
  Thermal.println("...");

  delay(1000);

  Thermal.print("\n\n\n");

  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" Arduino \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(1000);

  Thermal.println("An open-source electronics platform based on easy-to-use hardware and software, intended for anyone making interactive projects.");

  Thermal.println("\n\n\n");

  delay(1200);

  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" ASCII \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(1000);

  Thermal.println(F("American Standard Code for Information Interchange: Most modern text-encoding schemes are based on ASCII, although they support many additional characters."));

  delay(1200);

  Thermal.print("\n\n\n");

  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" Bits and Bites \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(1200);

  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  Thermal.println("Combine:");
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  Thermal.println("1 box shreddies");
  Thermal.println("1 box crispix");
  Thermal.println("1 box cherios");
  Thermal.println("1 bag pretzels");
  Thermal.println("1 pkg peanuts or sunflower seeds");
  Thermal.println("2 cups melted margarine");
  Thermal.println("1/3 cup worcestershire sauce");
  Thermal.println("1 tbsp onion powder");
  Thermal.println("1 tbsp garlic powder");
  Thermal.println("1 tbsp salt");
  Thermal.println("1 tsp celery salt");
  Thermal.println("1 tsp chili powder");

  Thermal.println("\n");

  delay(1500);

  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  Thermal.println("Bake:");
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  Thermal.println("Spread on parchment-lined baking trays.");
  Thermal.println("Bake at 250 until the most soaked shreddies are crisp.");
 
  delay(1000);

  Thermal.print("\n\n\n");
  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" Bits and BYTES \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(1000);

  Thermal.println("bit: 1 or 0");
  Thermal.println("byte: 8 bits");
  Thermal.println("eg. 10110100, or 00000110.");
  Thermal.println("A single byte can only represent numbers 0-255 (00000000-11111111)");

  delay(1000);

  Thermal.print("\n\n\n");

  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" Binary Solo, Decoded \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(1000);

  Thermal.println("00000010 STX: start transmission");
  Thermal.println("00000110 ACK: acknowledge");
  Thermal.println("00000111 BEL: bell!");
  Thermal.println("00001111  SI: change instrument!");
  

  Thermal.print("\n\n\n");

  // center
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write(1);
  // bold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  // invert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write(1);
  // title!
  Thermal.println(" ASCII Cheat Sheet \n\n");  
  // left
  Thermal.write(27);
  Thermal.write('a');
  Thermal.write((byte)0);
  // uninvert
  Thermal.write(29);
  Thermal.write('B');
  Thermal.write((byte)0);
  // unbold
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(500);


  Thermal.write(27);
  Thermal.write('!');
  Thermal.write(EMPH);
  Thermal.println("Dec   Hex    Binary      Char");
  Thermal.write(27);
  Thermal.write('!');
  Thermal.write((byte)0);

  delay(300);

  Thermal.println(F("  0   0x00   0000 0000   [NUL]"));
  Thermal.println(F("  1   0x01   0000 0001   [SOH]"));
  Thermal.println(F("  2   0x02   0000 0010   [STX]"));
  Thermal.println(F("  3   0x03   0000 0011   [ETX]"));
  Thermal.println(F("  4   0x04   0000 0100   [EOT]"));
  Thermal.println(F("  5   0x05   0000 0101   [ENQ]"));
  Thermal.println(F("  6   0x06   0000 0110   [ACK]"));
  Thermal.println(F("  7   0x07   0000 0111   [BEL]"));
  Thermal.println(F("  8   0x08   0000 1000   [BS]"));
  Thermal.println(F("  9   0x09   0000 1001   [TAB]"));
  Thermal.println(F(" 10   0x0A   0000 1010   [LF]"));
  Thermal.println(F(" 11   0x0B   0000 1011   [VT]"));
  Thermal.println(F(" 12   0x0C   0000 1100   [FF]"));
  Thermal.println(F(" 13   0x0D   0000 1101   [CR]"));
  Thermal.println(F(" 14   0x0E   0000 1110   [SO]"));
  Thermal.println(F(" 15   0x0F   0000 1111   [SI]"));
  delay(3000);
  Thermal.println(F(" 16   0x10   0001 0000   [DLE]"));
  Thermal.println(F(" 17   0x11   0001 0001   [DC1]"));
  Thermal.println(F(" 18   0x12   0001 0010   [DC2]"));
  Thermal.println(F(" 19   0x13   0001 0011   [DC3]"));
  Thermal.println(F(" 20   0x14   0001 0100   [DC4]"));
  Thermal.println(F(" 21   0x15   0001 0101   [NAK]"));
  Thermal.println(F(" 22   0x16   0001 0110   [SYN]"));
  Thermal.println(F(" 23   0x17   0001 0111   [ETB]"));
  Thermal.println(F(" 24   0x18   0001 1000   [CAN]"));
  Thermal.println(F(" 25   0x19   0001 1001   [EM]"));
  Thermal.println(F(" 26   0x1A   0001 1010   [SUB]"));
  Thermal.println(F(" 27   0x1B   0001 1011   [ESC]"));
  Thermal.println(F(" 28   0x1C   0001 1100   [FS]"));
  Thermal.println(F(" 29   0x1D   0001 1101   [GS]"));
  Thermal.println(F(" 30   0x1E   0001 1110   [RS]"));
  Thermal.println(F(" 31   0x1F   0001 1111   [US]"));
  delay(3000);
  Thermal.println(F(" 32   0x20   0010 0000   ' '"));
  Thermal.println(F(" 33   0x21   0010 0001   !"));
  Thermal.println(F(" 34   0x22   0010 0010   \""));
  Thermal.println(F(" 35   0x23   0010 0011   #"));
  Thermal.println(F(" 36   0x24   0010 0100   $"));
  Thermal.println(F(" 37   0x25   0010 0101   %"));
  Thermal.println(F(" 38   0x26   0010 0110   &"));
  Thermal.println(F(" 39   0x27   0010 0111   '"));
  Thermal.println(F(" 40   0x28   0010 1000   ("));
  Thermal.println(F(" 41   0x29   0010 1001   )"));
  Thermal.println(F(" 42   0x2A   0010 1010   *"));
  Thermal.println(F(" 43   0x2B   0010 1011   +"));
  Thermal.println(F(" 44   0x2C   0010 1100   ,"));
  Thermal.println(F(" 45   0x2D   0010 1101   -"));
  Thermal.println(F(" 46   0x2E   0010 1110   ."));
  Thermal.println(F(" 47   0x2F   0010 1111   /"));
  delay(3000);
  Thermal.println(F(" 48   0x30   0011 0000   0"));
  Thermal.println(F(" 49   0x31   0011 0001   1"));
  Thermal.println(F(" 50   0x32   0011 0010   2"));
  Thermal.println(F(" 51   0x33   0011 0011   3"));
  Thermal.println(F(" 52   0x34   0011 0100   4"));
  Thermal.println(F(" 53   0x35   0011 0101   5"));
  Thermal.println(F(" 54   0x36   0011 0110   6"));
  Thermal.println(F(" 55   0x37   0011 0111   7"));
  Thermal.println(F(" 56   0x38   0011 1000   8"));
  Thermal.println(F(" 57   0x39   0011 1001   9"));
  Thermal.println(F(" 58   0x3A   0011 1010   :"));
  Thermal.println(F(" 59   0x3B   0011 1011   ;"));
  Thermal.println(F(" 60   0x3C   0011 1100   <"));
  Thermal.println(F(" 61   0x3D   0011 1101   ="));
  Thermal.println(F(" 62   0x3E   0011 1110   >"));
  Thermal.println(F(" 63   0x3F   0011 1111   ?"));
  delay(3000);
  Thermal.println(F(" 64   0x40   0100 0000   @"));
  Thermal.println(F(" 65   0x41   0100 0001   A"));
  Thermal.println(F(" 66   0x42   0100 0010   B"));
  Thermal.println(F(" 67   0x43   0100 0011   C"));
  Thermal.println(F(" 68   0x44   0100 0100   D"));
  Thermal.println(F(" 69   0x45   0100 0101   E"));
  Thermal.println(F(" 70   0x46   0100 0110   F"));
  Thermal.println(F(" 71   0x47   0100 0111   G"));
  Thermal.println(F(" 72   0x48   0100 1000   H"));
  Thermal.println(F(" 73   0x49   0100 1001   I"));
  Thermal.println(F(" 74   0x4A   0100 1010   J"));
  Thermal.println(F(" 75   0x4B   0100 1011   K"));
  Thermal.println(F(" 76   0x4C   0100 1100   L"));
  Thermal.println(F(" 77   0x4D   0100 1101   M"));
  Thermal.println(F(" 78   0x4E   0100 1110   N"));
  Thermal.println(F(" 79   0x4F   0100 1111   O"));
  delay(3000);
  Thermal.println(F(" 80   0x50   0101 0000   P"));
  Thermal.println(F(" 81   0x51   0101 0001   Q"));
  Thermal.println(F(" 82   0x52   0101 0010   R"));
  Thermal.println(F(" 83   0x53   0101 0011   S"));
  Thermal.println(F(" 84   0x54   0101 0100   T"));
  Thermal.println(F(" 85   0x55   0101 0101   U"));
  Thermal.println(F(" 86   0x56   0101 0110   V"));
  Thermal.println(F(" 87   0x57   0101 0111   W"));
  Thermal.println(F(" 88   0x58   0101 1000   X"));
  Thermal.println(F(" 89   0x59   0101 1001   Y"));
  Thermal.println(F(" 90   0x5A   0101 1010   Z"));
  Thermal.println(F(" 91   0x5B   0101 1011   ["));
  Thermal.println(F(" 92   0x5C   0101 1100   \\"));
  Thermal.println(F(" 93   0x5D   0101 1101   ]"));
  Thermal.println(F(" 94   0x5E   0101 1110   ^"));
  Thermal.println(F(" 95   0x5F   0101 1111   _"));
  delay(3000);
  Thermal.println(F(" 96   0x60   0110 0000   `"));
  Thermal.println(F(" 97   0x61   0110 0001   a"));
  Thermal.println(F(" 98   0x62   0110 0010   b"));
  Thermal.println(F(" 99   0x63   0110 0011   c"));
  Thermal.println(F("100   0x64   0110 0100   d"));
  Thermal.println(F("101   0x65   0110 0101   e"));
  Thermal.println(F("102   0x66   0110 0110   f"));
  Thermal.println(F("103   0x67   0110 0111   g"));
  Thermal.println(F("104   0x68   0110 1000   h"));
  Thermal.println(F("105   0x69   0110 1001   i"));
  Thermal.println(F("106   0x6A   0110 1010   j"));
  Thermal.println(F("107   0x6B   0110 1011   k"));
  Thermal.println(F("108   0x6C   0110 1100   l"));
  Thermal.println(F("109   0x6D   0110 1101   m"));
  Thermal.println(F("110   0x6E   0110 1110   n"));
  Thermal.println(F("111   0x6F   0110 1111   o"));
  delay(3000);
  Thermal.println(F("112   0x70   0111 0000   p"));
  Thermal.println(F("113   0x71   0111 0001   q"));
  Thermal.println(F("114   0x72   0111 0010   r"));
  Thermal.println(F("115   0x73   0111 0011   s"));
  Thermal.println(F("116   0x74   0111 0100   t"));
  Thermal.println(F("117   0x75   0111 0101   u"));
  Thermal.println(F("118   0x76   0111 0110   v"));
  Thermal.println(F("119   0x77   0111 0111   w"));
  Thermal.println(F("120   0x78   0111 1000   x"));
  Thermal.println(F("121   0x79   0111 1001   y"));
  Thermal.println(F("122   0x7A   0111 1010   z"));
  Thermal.println(F("123   0x7B   0111 1011   ("));
  Thermal.println(F("124   0x7C   0111 1100   |"));
  Thermal.println(F("125   0x7D   0111 1101   )"));
  Thermal.println(F("126   0x7E   0111 1110   ~"));
  Thermal.println(F("127   0x7F   0111 1111   [DEL]"));
  Thermal.println("\n\n\n");
  delay(3000);

}


void loop() {}

