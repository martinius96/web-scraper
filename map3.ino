#include <Keyboard.h>
const int buttonPin = 2; 
int buttonState; 
int lastButtonState = HIGH; 
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50; 
int counter = 0;
const int buttonLeft = 3;
const int buttonRight = 4;
void setup() {
  Keyboard.begin();
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);
  while(!digitalRead(buttonLeft)){
  Keyboard.press('a');
  delay(300);
  Keyboard.releaseAll();
    }
    while(!digitalRead(buttonRight)){
    Keyboard.press('d');
  delay(300);
  Keyboard.releaseAll();
    }
if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        counter++;
      }
    }
  }
  lastButtonState = reading;
  Serial.println("Hodnota counteru:");
  Serial.println(counter);
if(counter>=5){
  Keyboard.write(218);
  counter = 0;
  Serial.println("Sipka vpred");
  }
}
