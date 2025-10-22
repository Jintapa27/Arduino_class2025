const int buttonPin = 2;

const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000; // 2 seconds for long press

int currentMode = 0;
unsigned long blinkTimer = 0;
const int blinkInterval = 1000;
bool blinkOn = true;

int lightNum = 0;

int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;
int RCurrentColor = 0;
int GCurrentColor = 0;
int BCurrentColor = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {
  checkButton();
  updateLEDColor();
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor); // ✅ Use current mode color
}

// ===== LED CONTROL =====
void setRGBLEDColor(int r, int g, int b) {
  // Invert output for common anode LED
  analogWrite(RledPin, 255 - r);
  analogWrite(GledPin, 255 - g);
  analogWrite(BledPin, 255 - b);
}

// ===== BUTTON CONTROL =====
void checkButton() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && !buttonPressed) {
    pressingTime = millis();
    buttonPressed = true;
  }

  if (buttonState == LOW && buttonPressed) {
    unsigned long currentTime = millis();
    if (currentTime - pressingTime < longPressInterval) {
      changeLEDColor();  // short press = change color
    } else {
      changeMode();      // long press = change mode
    }
    buttonPressed = false;
  }
}

// ===== COLOR SELECTION =====
void changeLEDColor() {
  lightNum++;
  if (lightNum >= 5) lightNum = 0;

  if (lightNum == 0) { RLightColor = 0; GLightColor = 0; BLightColor = 0; }           // off
  if (lightNum == 1) { RLightColor = 0; GLightColor = 255; BLightColor = 255; }       // cyan
  if (lightNum == 2) { RLightColor = 255; GLightColor = 0; BLightColor = 255; }       // magenta
  if (lightNum == 3) { RLightColor = 255; GLightColor = 255; BLightColor = 0; }       // yellow
  if (lightNum == 4) { RLightColor = 0; GLightColor = 0; BLightColor = 255; }         // blue
}

// ===== MODE SELECTION =====
void changeMode() {
  currentMode++;
  if (currentMode >= 3) currentMode = 0;

  if (currentMode == 1) {
    blinkTimer = 0;
    blinkOn = true;
  }
}

// ===== LED BEHAVIOR =====
void updateLEDColor() {
  if (currentMode == 0) {
    // Solid color
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }

  else if (currentMode == 1) {
    // Blink mode
    unsigned long currentTime = millis();
    if (currentTime - blinkTimer > blinkInterval) {
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }

    if (blinkOn) {
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    } else {
      RCurrentColor = 255;
      GCurrentColor = 255;
      BCurrentColor = 255;
    }
  }

  else if (currentMode == 2) {
    // Fade mode
    static int fadeValue = 0;
    static int fadeDirection = 1;

    fadeValue += fadeDirection * 5;
    if (fadeValue <= 0 || fadeValue >= 255) fadeDirection *= -1;

    RCurrentColor = (RLightColor * fadeValue) / 255;
    GCurrentColor = (GLightColor * fadeValue) / 255;
    BCurrentColor = (BLightColor * fadeValue) / 255;

    delay(20); // smooth fade
  }
}
