const int buttonPin = 2;
const int ledPin    = 3;

int reading = HIGH;
int lastReading = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Mode: 0=steady, 1=slow, 2=medium, 3=fast
int mode = 0;

bool ledState = true;
unsigned long previousMillis = 0;
const unsigned long intervals[] = {0, 1000, 500, 200};

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  ledState = true;
  previousMillis = millis();

  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {
  reading = digitalRead(buttonPin);
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        // change mode on press
        mode = (mode + 1) % 4;
        // reset blink timing and set a known led state when switching modes
        previousMillis = millis();
        if (mode == 0) {
          ledState = true;         // steady ON
          digitalWrite(ledPin, HIGH);
        } else {
          // start blink with LED ON
          ledState = true;
          digitalWrite(ledPin, HIGH);
        }
        Serial.print("Mode: ");
        Serial.println(mode);
      }
    }
  }

  lastReading = reading;

  unsigned long currentMillis = millis();

  if (mode == 0) {
    if (!ledState) {
      ledState = true;
      digitalWrite(ledPin, HIGH);
    }
  } else {
    unsigned long period = intervals[mode]; 
    unsigned long halfPeriod = period / 2;
    if (halfPeriod == 0) halfPeriod = 1;

    if (currentMillis - previousMillis >= halfPeriod) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
    }
  }
  delay(1);
}