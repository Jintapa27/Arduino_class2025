const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int mode = 0; // 0 = off, 1 = flicker, 2 = fading red
bool lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // button connected to GND
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  // Cycle through modes on button press
  if (lastButtonState == HIGH && buttonState == LOW) {
    mode++;
    if (mode > 2) mode = 0;
    delay(200); // debounce
  }
  lastButtonState = buttonState;

  if (mode == 0) {
    // Off
    setColor(0, 0, 0);
  }

  else if (mode == 1) {
    // Flickering flame (orange/red)
    int r = random(220, 255);
    int g = random(10, 60);
    int b = random(0, 10);
    setColor(r, g, b);
    delay(random(50, 150));
  }

  else if (mode == 2) {
    // Fading red mode
    static int fadeValue = 0;
    static int fadeDirection = 1;

    fadeValue += fadeDirection * 5; // fade speed
    if (fadeValue <= 0 || fadeValue >= 255) fadeDirection *= -1;

    int r = fadeValue;
    int g = fadeValue / 10;  // tiny bit of orange warmth
    int b = 0;

    setColor(r, g, b);
    delay(20);
  }
}

// ===== COMMON-ANODE COLOR OUTPUT =====
void setColor(int r, int g, int b) {
  analogWrite(RledPin, 255 - r);
  analogWrite(GledPin, 255 - g);
  analogWrite(BledPin, 255 - b);
}
