#include "funshield.h"

constexpr int buttonPins[] { button1_pin, button2_pin, button3_pin };
constexpr int buttonPinsCount = sizeof(buttonPins) / sizeof(buttonPins[0]);

constexpr int displayDigits = 4;

byte segmentMap[] = {
  0xC0, // 0  0b11000000
  0xF9, // 1  0b11111001
  0xA4, // 2  0b10100100
  0xB0, // 3  0b10110000
  0x99, // 4  0b10011001
  0x92, // 5  0b10010010
  0x82, // 6  0b10000010
  0xF8, // 7  0b11111000
  0x80, // 8  0b10000000
  0x90  // 9  0b10010000
};

constexpr byte pos_bitmask[] { 8, 4, 2, 1 }; // Pozice 4 znaku od prava (3, 2, 1, 0)
byte actualBitMaskPosition = 0;

int ourTotalNumber = 0;

//----------------------------------------------------------------------
int lastState1, lastState2, lastState3 = ON;  // the previous state from the input pin
int currentState1, currentState2, currentState3;     // the current reading from the input pin
//-----------------------------------------------------------------------

struct OurDisplay{
  
  void displaySetUp(){
    pinMode(latch_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);
    pinMode(data_pin, OUTPUT);
  }
  
  int exponent(int base, int exponent){
    int result = 1;
    for(int i = 0; i < exponent; i++){
      result *= base;
    }
    return result;
  }
  
  void increaseNumber(byte actualBitMaskPosition){
  ourTotalNumber += exponent(10, actualBitMaskPosition);
  if(ourTotalNumber > 9999) ourTotalNumber -= 10000;
  }
  
  void decreaseNumber(byte actualBitMaskPosition){
    ourTotalNumber -= exponent(10, actualBitMaskPosition);
    if(ourTotalNumber < 0) ourTotalNumber += 10000; 
  }
  
  void displayNumberCifer(){  
    byte i = 0;
    i = ourTotalNumber / exponent(10, actualBitMaskPosition) % 10;  
    writeGlyphBitmask(segmentMap[i], pos_bitmask[actualBitMaskPosition]);
  }

  void writeGlyphBitmask(byte glyph, byte pos_bitmask){
  digitalWrite(latch_pin, LOW);
  shiftOut( data_pin, clock_pin, MSBFIRST, glyph);
  shiftOut( data_pin, clock_pin, MSBFIRST, pos_bitmask);
  digitalWrite(latch_pin, HIGH);
}

}ourDisplay;
//-------------------------------------------------------------------------------
struct Buttons{
    void SetUp(){
      for (int i = 0; i < buttonPinsCount; ++i) {
        pinMode(buttonPins[i], INPUT);
      }
    }

    void btn1_Increment(){
    currentState1 = digitalRead(button1_pin);
    if(lastState1 == OFF && currentState1 == ON){
      ourDisplay.increaseNumber(actualBitMaskPosition);
    }
    lastState1 = currentState1;
    }
    
    void btn2_Decrement(){
      currentState2 = digitalRead(button2_pin);  
      if(lastState2 == OFF && currentState2 == ON){
         ourDisplay.decreaseNumber(actualBitMaskPosition);
      }
       
      lastState2 = currentState2;
    }

    void btn3_ChangePosition(){
    currentState3 = digitalRead(button3_pin);
    if(lastState3 == OFF && currentState3 == ON){
        actualBitMaskPosition++;
        actualBitMaskPosition %= displayDigits;
      }
      lastState3 = currentState3;
    }

    void Handler(){
       btn1_Increment(); 
       btn2_Decrement();
       btn3_ChangePosition();  
    }
}buttons;
//-------------------------------------------------------------------
void setup() {
  ourDisplay.displaySetUp();
  buttons.SetUp(); 
}

void loop() {
     ourDisplay.displayNumberCifer();
     buttons.Handler();   
}
