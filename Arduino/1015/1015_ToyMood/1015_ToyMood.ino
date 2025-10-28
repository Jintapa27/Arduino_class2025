const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;
const int buttonPin = 2;

int mood = 0;
const int neutralMood = 10;
int buttonState = HIGH;
bool ButtonPressed = false;

unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;

const long unTouchInterval = 5000;
const long reducedInterval = 1000;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  mood = neutralMood;
}

void loop() {
  showLEDState(mood);

  int reading = digitalRead(buttonPin);

  if (reading == LOW && !ButtonPressed) {
    mood += 1;
    mood = constrain(mood, 0, 20);
    touchedTimer = millis();
    ButtonPressed = true;
    delay(50);

    // blink green when mood reaches max
    if (mood == 20) {
      happyBlink();
    }
  }

  if (reading == HIGH && ButtonPressed) {
    ButtonPressed = false;
  }

  unsigned long currentTimer = millis();

  if (currentTimer - touchedTimer > unTouchInterval) {
    if (currentTimer - reducedTimer > reducedInterval) {
      mood -= 1;
      mood = constrain(mood, 0, 20);
      reducedTimer = currentTimer;
    }
  }
}

void showLEDState(int moodValue) {
  int red = map(moodValue, 0, 20, 255, 0);   // low mood = red
  int green = map(moodValue, 0, 20, 0, 255); // high mood = green
  int blue = map(moodValue, 0, 20, 0, 80);   // small blue when mood rises

  analogWrite(RledPin, 255 - red);
  analogWrite(GledPin, 255 - green);
  analogWrite(BledPin, 255 - blue);
}

void happyBlink() {
  for (int i = 0; i < 3; i++) {
    analogWrite(RledPin, 255);
    analogWrite(GledPin, 0);
    analogWrite(BledPin, 255);
    delay(150);
    analogWrite(RledPin, 255);
    analogWrite(GledPin, 255);
    analogWrite(BledPin, 255);
    delay(150);
  }
}
