#include "funshield.h"

constexpr int buttonPins[] {button1_pin, button2_pin};
constexpr int ledPins[] { led1_pin, led2_pin, led3_pin, led4_pin };
constexpr int ledPinsCount = sizeof(ledPins) / sizeof(ledPins[0]);

constexpr int activationDelay = 1000; // how long before button starts to perform periodic updates [ms]
constexpr int periodicDelay = 300; // delay between consecutive periodic updates [ms]

constexpr bool pressed = true;
constexpr bool notPressed = false;

int lastState1 = notPressed;
int lastState2 = notPressed;

int num = 0;

unsigned long previousMillis1 = 0, pressTime1 = 0;
unsigned long previousMillis2 = 0, pressTime2 = 0;

bool timerPeriodicDelay1(unsigned long period) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= period) {
    previousMillis1 = currentMillis;
    return true;
  }
  return false;
}

bool timerPeriodicDelay2(unsigned long period) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis2 >= period) {
    previousMillis2 = currentMillis;
    return true;
  }
  return false;
}


void dislayNumber(int num) {
   num = num % 16;
//  Serial.println(num);
  for (size_t i = 0; i < ledPinsCount; i++) {
      size_t state = bitRead(num, i); // state = 0 nebo 1     
      if (state == 0) {
        digitalWrite(ledPins[ledPinsCount-i-1],OFF); 
      } else {
        digitalWrite(ledPins[ledPinsCount-i-1], ON);
      }
    }

}

bool isButtonPressed(int button) {
  int state = digitalRead(button);
  if (!state) {
    return true;
  } else {
    return false;
  }
}

bool buttonStateChangePress(bool curr_state, bool lastState) {
  if (lastState == notPressed && curr_state == pressed) return true;
  else return false;
}

bool buttonStateChangeRelease(bool curr_state, bool lastState) {
  if (lastState == pressed && curr_state == notPressed) return true;
  else return false;
}

bool isButtonHeld(bool cur_state, bool lastState) {
  if (lastState == pressed && cur_state == pressed) return true;
  else return false;
}

void increment(int button){
  bool currentState = isButtonPressed(button);
  bool buttonIsPressed = buttonStateChangePress(currentState, lastState1);
  bool holding = isButtonHeld(currentState, lastState1);

  if (buttonIsPressed) {
    num++;
    dislayNumber(num);
    pressTime1 = millis();
  }
  else if (holding) {
    unsigned long currentTime = millis();
    if(currentTime - pressTime1 >= activationDelay){
      if(timerPeriodicDelay1(periodicDelay)){
        num++;
        dislayNumber(num);
      }
    }
  }
  lastState1 = currentState;
}

void decrement(int button){
  bool currentState = isButtonPressed(button);
  bool buttonIsPressed = buttonStateChangePress(currentState, lastState2);
  bool holding = isButtonHeld(currentState, lastState2);

  if (buttonIsPressed) {
    num--;
    dislayNumber(num);
    pressTime2 = millis();
  }
  else if (holding) {
    unsigned long currentTime = millis();
    if(currentTime - pressTime2 >= activationDelay){
      if(timerPeriodicDelay2(periodicDelay)){
        num--;
        dislayNumber(num);
      }
    }
  }
  lastState2 = currentState;
}

void setup() {
//  Serial.begin(9600);
  for (int i = 0; i < ledPinsCount; ++i) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], OFF);
  }
  pinMode(button1_pin, INPUT);
  pinMode(button2_pin, INPUT);
}

void loop() {
    increment(button1_pin);
    decrement(button2_pin);
}
