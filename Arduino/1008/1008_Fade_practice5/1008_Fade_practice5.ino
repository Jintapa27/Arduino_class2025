/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Fade/
*/
const int RledPin =9;
const int GledPin = 10;
const int BledPin = 11;
int ledcolor = 0;         // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
    digitalWrite(RledPin, OUTPUT);
    digitalWrite(GledPin, OUTPUT);
    digitalWrite(BledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  if(ledcolor ==0){
    analogWrite(RledPin, brightness);
    analogWrite(GledPin, 255);
    analogWrite(BledPin, 255);
  }
  if(ledcolor == 1){
    analogWrite(RledPin, brightness);
    analogWrite(GledPin, 255);
    analogWrite(BledPin, 255);
  }
    if(ledcolor == 2){
    analogWrite(RledPin, brightness);
    analogWrite(GledPin, 255);
    analogWrite(BledPin, 255);
  }
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    if(brightness >= 255){
      ledcolor = ledcolor +1;
      if(ledcolor >2)
      ledcolor =0;
    }
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
