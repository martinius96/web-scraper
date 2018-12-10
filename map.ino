#include <Keyboard.h>
const int buttonPin = 2;    // the number of the pushbutton pin        // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
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
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  int left = digitalRead(buttonLeft);
  int right = digitalRead(buttonRight);
  if(left==LOW){
    Keyboard.press('a');
    delay(100);
  Keyboard.releaseAll();
    }
    if(right==LOW){
    Keyboard.press('d');
    delay(100);
  Keyboard.releaseAll();
    }
if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
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
  Serial.println("Spika vpred");
  }
}
