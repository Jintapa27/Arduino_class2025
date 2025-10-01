const int buttonPin = 2;  // the number of the pushbutton pin
const int RledPin = 3;    // the number of the LED pin
const int GledPin = 4;
const int BledPin = 5;  

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
int ledcolor = 0;

bool ButtonPressed = false;

void setup() {
  // initialize the LED pin as an output:
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && !ButtonPressed) {
    ledcolor = ledcolor + 1;
    ButtonPressed = true;
    //delay(100);
  }
  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }
  if (ledcolor ==0){
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor ==1) {
    // RED
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor ==2) {
    // GREEN
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor ==3) {
    // BLUE
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor ==4) {
    // YELLOW
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledcolor ==5) {
    // PURPLE
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor ==6) {
    // CYAN
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor ==7) {
    // WHITE
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
  else if (ledcolor ==8){
    ledcolor = 0;
  }
}
