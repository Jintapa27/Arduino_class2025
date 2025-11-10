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
const int fadeAmount = 2;
int fadeDirection = 1;

// ===== NEW BONUS FEATURE =====
unsigned long randomColorTimer = 0;
const int randomColorInterval = 1000; // 1 second
// ==============================

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  randomSeed(analogRead(0)); // seed random for bonus mode
}

void loop() {
  checkButton();
  updateLEDColor();
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor); 
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
  lightNum = lightNum + 1;
  if (lightNum >= 5)
    lightNum = 0;

  if (lightNum == 0) { RLightColor = 0; GLightColor = 0; BLightColor = 0; }           // off
  if (lightNum == 1) { RLightColor = 0; GLightColor = 255; BLightColor = 255; }       // cyan
  if (lightNum == 2) { RLightColor = 255; GLightColor = 0; BLightColor = 255; }       // magenta
  if (lightNum == 3) { RLightColor = 255; GLightColor = 255; BLightColor = 0; }       // yellow
  if (lightNum == 4) { RLightColor = 0; GLightColor = 0; BLightColor = 255; }         // blue

  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;
}

// ===== MODE SELECTION =====
void changeMode() {
  currentMode = currentMode + 1;
  if (currentMode >= 4) {  
    currentMode = 0;
  }
  if (currentMode == 1) {
    blinkTimer = 0;
    blinkOn = true;
  }
  if (currentMode == 2) {
    fadeDirection = 1;
  }
  if (currentMode == 3) {
    randomColorTimer = 0;
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
    bool negativeDir = false;
    if (RLightColor == 0) {
      RCurrentColor = RCurrentColor + fadeDirection * fadeAmount;
      if (RCurrentColor > (255 - RLightColor) || (RCurrentColor < 0)) {
        negativeDir = true;
      }
      RCurrentColor = constrain(RCurrentColor, 0, 255);
    }

    if (GLightColor == 0) {
      GCurrentColor = GCurrentColor + fadeDirection * fadeAmount;
      if (GCurrentColor > (255 - GLightColor) || (GCurrentColor < 0)) {
        negativeDir = true;
      }
      GCurrentColor = constrain(GCurrentColor, 0, 255);
    }

    if (BLightColor == 0) {
      BCurrentColor = BCurrentColor + fadeDirection * fadeAmount;
      if (BCurrentColor > (255 - BLightColor) || (BCurrentColor < 0)) {
        negativeDir = true;
      }
      BCurrentColor = constrain(BCurrentColor, 0, 255);
    }

    if (negativeDir)
      fadeDirection = -fadeDirection;

    delay(10);
  }

  else if (currentMode == 3) {
    // RANDOM COLOR MODE
    unsigned long currentTime = millis();
    if (currentTime - randomColorTimer > randomColorInterval) {
      RCurrentColor = random(0, 256);
      GCurrentColor = random(0, 256);
      BCurrentColor = random(0, 256);
      randomColorTimer = currentTime;
    }
  }
}
