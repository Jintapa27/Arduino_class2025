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

const long unTouchInterval = 5000;  // 5 sec inactivity before mood decreases
const long reducedInterval = 1000;  // reduce mood every 1 sec

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // stable input
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  mood = neutralMood;
}

void loop() {
  showLEDState(mood);

  int reading = digitalRead(buttonPin);

  // Detect button press (LOW = pressed in INPUT_PULLUP)
  if (reading == LOW && !ButtonPressed) {
    mood += 1;
    mood = constrain(mood, 0, 20);  // keep mood in range
    touchedTimer = millis();
    ButtonPressed = true;
    delay(50); // debounce delay
  }

  if (reading == HIGH && ButtonPressed) {
    ButtonPressed = false;
  }

  unsigned long currentTimer = millis();

  // If not touched for a while, reduce mood gradually
  if (currentTimer - touchedTimer > unTouchInterval) {
    if (currentTimer - reducedTimer > reducedInterval) {
      mood -= 1;
      mood = constrain(mood, 0, 20);
      reducedTimer = currentTimer;
    }
  }
}

// Function to control LED color based on mood value
void showLEDState(int moodValue) {
  // Map mood to color range
  int red = map(moodValue, 0, 20, 255, 0);   // low mood → red
  int green = map(moodValue, 0, 20, 0, 255); // high mood → green
  int blue = 50;                             // faint blue for blend

  // Invert values for common anode LED
  analogWrite(RledPin, 255 - red);
  analogWrite(GledPin, 255 - green);
  analogWrite(BledPin, 255 - blue);
}
