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
int maxBrightness = 0;         // the PWM pin the LED is attached to
int currentBrightness = 0;  // how bright the LED is
int fadingDirection = 1;  // how many points to fade the LED by
unsigned long previousMillis = 0;
int interval = 1000;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
    pinMode(RledPin, OUTPUT);
    pinMode(GledPin, OUTPUT);
    pinMode(BledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A0);
  maxBrightness = map(sensorValue, 0, 1023, 0, 255);
  maxBrightness = 255;

  unsigned long currentMillis = millis();
  int fadingAmount = fadingDirection * map(currentMillis - previousMillis, 0, interval, 0, maxBrightness);
  currentBrightness = currentBrightness + fadingAmount;
  if (currentBrightness >= 255) {
    currentBrightness = 255;
    fadingDirection = -fadingDirection;
  }

if(currentBrightness <= 0){
  currentBrightness = 0;
  fadingDirection = -fadingDirection;
}
  analogWrite(RledPin, currentBrightness);
  analogWrite(GledPin, currentBrightness);
  analogWrite(BledPin, currentBrightness);
  previousMillis = currentMillis;
  delay(1);
}
