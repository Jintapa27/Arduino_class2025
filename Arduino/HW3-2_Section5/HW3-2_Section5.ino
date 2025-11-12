const int buttonPin = 2;
const int ledPin    = 3;

int lastButtonState = HIGH;
int buttonState     = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

int mode = 0;
bool ledState = false;
unsigned long previousMillis = 0;
const unsigned long blinkIntervals[] = {0, 1000, 500, 200};

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // steady ON (because wiring is reversed)
  Serial.begin(9600);
  Serial.println("System ready");
}

void loop() {
  int reading = digitalRead(buttonPin);
  unsigned long currentMillis = millis();

  if (reading != lastButtonState) lastDebounceTime = currentMillis;
  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        mode = (mode + 1) % 4;
        previousMillis = currentMillis;
        ledState = false;
        digitalWrite(ledPin, LOW); // ensure ON when mode changes
        Serial.print("Mode: ");
        Serial.println(mode);
      }
    }
  }
  lastButtonState = reading;

  if (mode == 0) {
    digitalWrite(ledPin, LOW); // steady ON (active LOW)
  } else {
    unsigned long half = blinkIntervals[mode] / 2;
    if (currentMillis - previousMillis >= half) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(ledPin, ledState ? HIGH : LOW);
    }
  }
}
