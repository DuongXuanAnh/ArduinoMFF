#include "funshield.h"

constexpr int buttonPins[] { button1_pin, button2_pin, button3_pin };
constexpr int buttonPinsCount = sizeof(buttonPins) / sizeof(buttonPins[0]);

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
//----------------------------------------------------------------------------------------
constexpr byte pos_bitmask[] { 0x08, 0x04, 0x02, 0x01 }; // Pozice 4 znaku od prava (3, 2, 1, 0)

bool button1_status_IsTrue = false;

bool running_status = false;
bool freeze_status = false;
bool stopped_status = true;

int ourNumber = 0;

constexpr unsigned long interval = 100; 

//------------------------------------------------------------
int lastState1, lastState2, lastState3 = ON;  // the previous state from the input pin
int currentState1, currentState2, currentState3;     // the current reading from the input pin
//-------------------------------------------------------------------------

int numberOfLedActive = 2;
int ledPosition = 0; // the most right digit on display
unsigned long increaseTimer, start_time;

void setup() {
  for (int i = 0; i < buttonPinsCount; ++i) {
    pinMode(buttonPins[i], INPUT);
  }

  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
}

void multiplexing() {
  if (ourNumber < 100) numberOfLedActive = 2;
  else if (ourNumber < 1000)numberOfLedActive = 3;
  else if (ourNumber < 10000)numberOfLedActive = 4;
  ledPosition++;
  ledPosition = ledPosition % numberOfLedActive;
}

void writeGlyphBitmask(byte glyph, byte pos_bitmask, int dot){
  
  if(dot) glyph &= 0x7f; // Jestli chceme tecku tak dot=1 jinak dot=0
  
  digitalWrite(latch_pin, LOW);
  shiftOut( data_pin, clock_pin, MSBFIRST, glyph);
  shiftOut( data_pin, clock_pin, MSBFIRST, pos_bitmask);
  digitalWrite(latch_pin, HIGH);
}

 int exponent(int base, int exponent){
    int result = 1;
    for(int i = 0; i < exponent; i++){
      result *= base;
    }
    return result;
  }

void DisplayNumber(){
  
   unsigned long num_to_show = ourNumber % exponent(10, ledPosition+1) / exponent(10, ledPosition);
  
   if(ledPosition == 1){
     writeGlyphBitmask(segmentMap[num_to_show], pos_bitmask[ledPosition], 1); // nase tecka
   }else{
     writeGlyphBitmask(segmentMap[num_to_show], pos_bitmask[ledPosition], 0); 
   }
      
}

void btn1_Start_Stop(){
  currentState1 = digitalRead(button1_pin);
  if(lastState1 == OFF && currentState1 == ON &&  !freeze_status){      
      button1_status_IsTrue = !button1_status_IsTrue;
      if(button1_status_IsTrue){
         start_time = (millis() - increaseTimer);
           running_status = true;
           stopped_status = false;
      }else{
           stopped_status = true;
           running_status = false;
      }     
  }
  lastState1 = currentState1;
}

void btn2_Zmazit_Obnovit(){
  currentState2 = digitalRead(button2_pin);
  if(lastState2 == OFF && currentState2 == ON){    
      if(running_status){
          freeze_status = true;
          running_status = false;
        
      } else if (freeze_status){
          running_status = true;
          freeze_status = false;
      }
  }
  
  lastState2 = currentState2;
}

void btn3_Reset(){
  currentState3 = digitalRead(button3_pin);
  if(lastState3 == OFF && currentState3 == ON && stopped_status){    
      increaseTimer = 0;
      ourNumber = 0;
  }
  lastState3 = currentState3;
}

void incrementOurNumber(){
  if(running_status){
    start_time = (millis() - increaseTimer);
  }
}

void buttons_functional(){
  btn1_Start_Stop();
  btn2_Zmazit_Obnovit();
  btn3_Reset();
}

void ThingWeSeeOnDisplay(){
  
    if (running_status) {
      increaseTimer = (millis() - start_time);
      ourNumber = increaseTimer / interval;
    }
    
    if (freeze_status) {
       increaseTimer = (millis() - start_time);   
    }
    
    DisplayNumber();
}
 
void loop() {
  multiplexing();
  buttons_functional();
  ThingWeSeeOnDisplay();      
}
