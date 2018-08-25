// TODO: change the code to make it say something different!

void setup() {
  // put your setup code here, to run once:

  // open up communication with the computer at 9600 bits/second
  Serial.begin(9600);

  // wait untilSerial is ready - Leonardo
  while (!Serial);

  // create an ascii message to send
  char message[] = { 0b01001000, 0b01000101, 0b01001100, 0b01001100, 0b01001111 };

  // send the message!
  Serial.println(message);
}


void loop() {
  // put your main code here, to run repeatedly:

  // do nothing :)
}

