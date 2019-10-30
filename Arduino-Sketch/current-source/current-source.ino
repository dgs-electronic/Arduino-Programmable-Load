/*
  Reading a serial ASCII-encoded string.

  This sketch demonstrates the Serial parseInt() function.
  It looks for an ASCII string of comma-separated values.
  It parses them into ints, and uses those to fade an RGB LED.

  Circuit: Common-Cathode RGB LED wired like so:
  - red anode: digital pin 3
  - green anode: digital pin 5
  - blue anode: digital pin 6
  - cathode: GND

  created 13 Apr 2012
  by Tom Igoe
  modified 14 Mar 2016
  by Arturo Guadalupi

  This example code is in the public domain.
*/

//Shunt-Widerstand
const int ciShunt = 1; //1 Ohm Shunt
const int cimaxCurrent_1mA0 = 3100;

// pins for the LEDs:
const int redPin = 3;
const int greenPin = 9;
const int bluePin = 6;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  //Frequenz der PWM auf Maximum stellen
  TCCR1B |= 0x01;
  TCCR1B &= ~0x06;

}

void setCurrent(int iCurrent1_1mA0, int iCurrent2_1mA0)
{
  long Digit1 = (long)iCurrent1_1mA0;
  long Digit2 = (long)iCurrent2_1mA0;

  Digit1 = constrain(Digit1, 0, cimaxCurrent_1mA0);
  Digit2 = constrain(Digit2, 0, cimaxCurrent_1mA0);

  Digit1 *= (long)ciShunt;
  Digit1 *= 256L;
  Digit1 += 2500L;
  Digit1 /= 5000L;
  Digit1 = constrain(Digit1, 0, 255);

  Digit2 *= (long)ciShunt;
  Digit2 *= 256L;
  Digit2 += 2500L;
  Digit2 /= 5000L;
  Digit2 = constrain(Digit2, 0, 255);

  analogWrite(redPin,Digit1);
  analogWrite(greenPin,Digit2);

  Serial.print("Kanal1: 0x");
  Serial.println(Digit1, HEX);
  Serial.print("Kanal2: 0x");
  Serial.println(Digit2, HEX);
  
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int Kanal1 = Serial.parseInt();
    // do it again:
    int Kanal2 = Serial.parseInt();
    
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      
      setCurrent(Kanal1,Kanal2);
      
      
    }
  }
}
