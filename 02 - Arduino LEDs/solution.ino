#include "funshield.h"

constexpr int ledPins[] { led1_pin, led2_pin, led3_pin, led4_pin };
constexpr int ledPinsCount = sizeof(ledPins) / sizeof(ledPins[0]);
constexpr unsigned long delayTime = 300;

unsigned long time0 = 0;
bool increaseNumber = true;
int ledNumber = 0;


void setup() {
//  Serial.begin(9600);
  for (int i = 0; i < ledPinsCount; ++i) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], OFF);
  }
}

// Rozsviti ledku na pozici "ledNumber", ostatni ledky zhasne
void LED_display(){ 
    for (int i = 0; i < ledPinsCount; ++i) {
    if(i == ledNumber){
      digitalWrite(ledPins[i], ON ); 
    }else{
       digitalWrite(ledPins[i], OFF );  
    }
  }
}

void updateLedNumber(){ // vygenerovava posloupnost 0123210.....
        if(increaseNumber){ 
           ledNumber++;
           if(ledNumber > 2){
            increaseNumber = false;
           }
        }else{
          ledNumber--;
          if(ledNumber < 1){
            increaseNumber = true;
          }
        } 
        //        Serial.println(ledNumber);
}

void zobraz_LED_posloupnost(){
    if ((unsigned long)(millis() - time0) == delayTime)
    {
        LED_display();
        time0 = millis();
        updateLedNumber(); 
    }
}

void loop() {
    zobraz_LED_posloupnost();
 }
