....const int buttonPin = 2;  // the number of the pushbutton pin
const int RledPin = 3;    // the number of the LED pin
const int GledPin = 4;
const int BledPin = 5;  

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
int ledColor = 0;
bool ButtonPressed = false;
unsigned long previousMillis = 0;
const long interval =1000;
bool ledColorOrder = true;

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
    ledColorOrder = !ledColorOrder;
    ButtonPressed = true;
    //delay(100);
  }
  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledColorOrder == true){
        ledColor = ledColor + 1;
        if(ledColor > 3)
          ledColor = 0;
    }
    else {
        ledColor =ledColor -1;
        if(ledColor < 0)
          ledColor= 3;
    }
  }
  if (ledColor ==0){
    //RED
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledColor ==1) {
    //GREEN
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  }
  else if (ledColor ==2) {
    // BLUE
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  }

  else if (ledColor ==3) {
    // BLUE
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);   
  }
}
