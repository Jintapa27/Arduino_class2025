const int buttonPin = 2;  
const int RledPin = 3;    
const int GledPin = 4;
const int BledPin = 5;  

int buttonState = 0;       
int ledcolor = 0;
bool ButtonPressed = false;

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // button just pressed
  if (buttonState == HIGH && !ButtonPressed) {
    ButtonPressed = true;
    
    blinkBeforeNextColor();   // blink once before changing
    
    // normal color cycle
    ledcolor++;
    if (ledcolor > 7) ledcolor = 0;
    
    delay(100);               // debounce
  }

  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  // original LED color logic
  if (ledcolor == 0){
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 1) {
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 2) {
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 3) {
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 4) {
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor == 5) {
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 6) {
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor == 7) {
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
}

// blink once quickly before showing next color
void blinkBeforeNextColor() {
  digitalWrite(RledPin, HIGH);
  digitalWrite(GledPin, HIGH);
  digitalWrite(BledPin, HIGH);
  delay(200);
  
  // turn off LEDs briefly
  digitalWrite(RledPin, LOW);
  digitalWrite(GledPin, LOW);
  digitalWrite(BledPin, LOW);
  delay(200);
}
