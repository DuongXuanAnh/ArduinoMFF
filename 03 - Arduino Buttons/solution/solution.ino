#include "funshield.h"

constexpr int ledPins[] { led1_pin, led2_pin, led3_pin, led4_pin };
constexpr int ledPinsCount = sizeof(ledPins) / sizeof(ledPins[0]);
constexpr int buttonPins[] { button1_pin, button2_pin };
constexpr int buttonPinsCount = sizeof(buttonPins) / sizeof(buttonPins[0]);

constexpr int activationDelay = 1000; // how long before button starts to perform periodic updates [ms]
constexpr int periodicDelay = 300; // delay between consecutive periodic updates [ms]

//---------------------------------------------------------
size_t num = 0;
const size_t modulo = 16; // Nase cislo num nebude vetzi nez hodnota modulo

bool btn1_notPressYet = true; // promnena pro kratke smacknuti
unsigned long timerOneSecond = 0;
unsigned long timerDelay = 0;

bool btn2_notPressYet = true; // promnena pro kratke smacknuti
unsigned long timerOneSecond2 = 0;
unsigned long timerDelay2 = 0;

class NumberManager{
  public:
    size_t increamentNumber(size_t number){
      return (number+1) % modulo;
    }
    size_t decreamentNumber(size_t number){
      return (number-1) % modulo;
    }

    void dislayNumber(int num) {
    for (size_t i = 0; i < ledPinsCount; i++) {
        size_t state = bitRead(num, i); // state = 0 nebo 1     
        if (state == 0) {
          digitalWrite(ledPins[ledPinsCount-i-1],OFF); 
        } else {
          digitalWrite(ledPins[ledPinsCount-i-1], ON);
        }
      }
  }    
};

NumberManager numManager;

void setup() {
//  Serial.begin(9600);
  for (int i = 0; i < buttonPinsCount; ++i) {
    pinMode(buttonPins[i], INPUT);
  }
  for (int i = 0; i < ledPinsCount; ++i) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], OFF);
  }
}

void btn1(){
  if(digitalRead(buttonPins[0]) == ON){ // Jestli btn1 je smacknuty
      if(btn1_notPressYet){ // Press kratce
        num = numManager.increamentNumber(num);
        numManager.dislayNumber(num);
        btn1_notPressYet = false;
      }
      if((unsigned long) millis() - timerOneSecond >= activationDelay){ // Jestli btn1 je drzeny vic jak 1 sekundu
        if((unsigned long) millis() - timerDelay >= periodicDelay){
          num = numManager.increamentNumber(num);
          numManager.dislayNumber(num);
          timerDelay = millis();
        }
      }
    }else{
      btn1_notPressYet = true;
      timerOneSecond = millis();
    }
}

void btn2(){
   if(digitalRead(buttonPins[1]) == ON){ // Jestli btn2 je smacknuty
      if(btn2_notPressYet){ // Press kratce
        num = numManager.decreamentNumber(num);
        numManager.dislayNumber(num);
        btn2_notPressYet = false;
      }
      if((unsigned long) millis() - timerOneSecond2 >= activationDelay){ // Jestli btn2 je drzeny vic jak 1 sekundu
        if((unsigned long) millis() - timerDelay2 >= periodicDelay){
          num = numManager.decreamentNumber(num);
          numManager.dislayNumber(num);
          timerDelay2 = millis();
        }
      }
    }else{
      btn2_notPressYet = true;
      timerOneSecond2 = millis();
    }
}

void loop() {
    btn1();
    btn2();
}
