#include "funshield.h"

class NumberGenius{
  public:
    NumberGenius () {}
    static int extract_LSfigure_at_pos_i(unsigned int decimal_num, int i){ //i = 2, decimal_num = 1234 --> returns 2
    //gets the i-th least significant number from a given decimal number, indexing from zero
    //decimal_num must be positive integer - as written explicitely in parameters
      int result = decimal_num;
      for (int j = 0; j < i; j++ ){ //we move the decimal point to the left by i positions and round it down
        result /= 10;
      }
      result %= 10; //this way we return only the right-most figure of the result
      return result;
    }
    static int digits_in_a_value(int value){ //returns number of digits in a value
      int pos = 1;
      while(value > 9){
        pos += 1;
        value /= 10;
      }
      return pos;
    }
};

//interval clock
class Clock{
  private:
    unsigned long last_time = 0;
  public:
    Clock(){}
    bool is_time_to_work(int interval){
      //input is interval=x in milliseconds. returns true every x milliseconds
      unsigned long cur_time = millis();
      if( cur_time >= last_time + interval){
        last_time = cur_time;
        return true;
      }
      else{
        return false;
      }
    }
};

const int diceTypes[] = {4, 6, 8, 10, 12, 20, 100};
const int diceTypesCount = sizeof(diceTypes)/sizeof(diceTypes[0]);
class Dice{
  private:
    int currTypeIndex = 0; //default set to diceTypes[0], which is d4
    static const int maxThrows = 9; //maximum allowed number of throws
    static const int minThrows = 1;
  public:
    Dice () {}
    int throwsToDo = 1; //number of throws that the user wants to do
    int resultRolls[maxThrows];
    enum state {normal, config};
    state currState = state::config;
    int getCurrType(){
      return diceTypes[currTypeIndex];
    }
    void changeType(){
      currTypeIndex += 1;
      currTypeIndex %= diceTypesCount;
    }
    void incrementThrowsToDo(){
      ++throwsToDo;
      if(throwsToDo > maxThrows){
        throwsToDo = minThrows;
      }
    }
    void rollDice(unsigned long int seed){
      //first, reset previous roll
      for(int i = 0; i < maxThrows - 1; i++){
        resultRolls[i] = 0;
      }
      //then generate new roll
      randomSeed(seed); //set given random seed
      for(int i = 0; i < throwsToDo; i++){ //simulate rolling the dice given times - this ensures binomial distribution of probability
        resultRolls[i] = random(1, diceTypes[currTypeIndex]+1); //the increment of the second parameter ensures the generation of a random number between 1 and dicetype[currTypeIndex]
      }
    }
    unsigned int getRollResult(){ //returns the sum of rolls stored in resultRolls
      int result = 0;
      for(int i = 0; i < maxThrows-1; i++){
        result += resultRolls[i];
      }
      return result;
    }
};

//BUTTONS
const int button[] = {button1_pin, button2_pin, button3_pin};
const int button_count = sizeof(button)/sizeof(button[0]);
class Buttons_controller{
  private:
    //BUTTONS' STATES ARE SAVED HERE
      bool last_button_state[button_count];
      unsigned long press_time[button_count];
      bool buttonHeldForLongEnough[button_count];
  public:
    Buttons_controller () {}
    //LOGIC
      static const bool pressed = true;
      static const bool notPressed = false;
    //SETTINGS
      void all_buttons_as_input(){
        for(int i = 0; i < button_count; ++i){
          pinMode(button[i], INPUT);
        }
      }
      void set_last_button_state(int i, bool state){
        last_button_state[i] = state;
      }
      void all_buttons_notPressed(){
        for(int i = 0; i < button_count; ++i){
          set_last_button_state(i, notPressed);
        }
      }
      void set_press_times_to_0(){
        for(int i=0; i < button_count; i++){
          press_time[i] = 0;
        }
      }
      void set_buttons_not_held_long_enough(){
        for(int i=0; i < button_count; i++){
          buttonHeldForLongEnough[i] = false;
        }
      }
    //FUNCTION FOR USING ALL SETTINGS FUCTIONS AT ONCE
    void default_settings(){
      all_buttons_as_input();
      all_buttons_notPressed();
      set_press_times_to_0();
      set_buttons_not_held_long_enough();
    }
    //USEFUL FUNCTIONS
      void set_last_button_state(bool state, int i){
        last_button_state[i] = state;
      }
      bool is_pressed(int button_index){ //returns true if button[button_index] is pressed at the moment
        bool isPressed = ! digitalRead(button[button_index]);
        return isPressed;
      }
      bool detect_button_state_change(int i, bool changeToDetect, bool currentState){
      /*basically returns true if button gets pressed or unpressed depending on changeToDetect.
        if changeToDetect == pressed, then detect unpressed -> pressed change, 
        else detect pressed -> unpressed change*/
        bool button_changed_state = (currentState == changeToDetect && currentState != last_button_state[i]);
        if(button_changed_state){
          return true;
        }
        return false;
      }
      bool pressed_for_longer_than_interval(int interval, unsigned long pressedAt){ //returns true if button has been held pressed for longer than interval. else returns false
        unsigned long current_time = millis();
        unsigned long has_been_pressed_for = current_time - pressedAt;
        bool result = has_been_pressed_for > (unsigned long) interval;
        return result;
      }
      bool is_button_held_pressed(int button_num, bool currentState){ //returns true if button is still pressed, else returns false
        bool buttonIsHeldPressed = (currentState == pressed && last_button_state[button_num] == pressed);
        return buttonIsHeldPressed;
      }
};

//DISPLAYS
const int display_pins[] = {latch_pin, clock_pin, data_pin};
const int display_pins_count = sizeof(display_pins)/sizeof(display_pins[0]);
class Display_controller{
  private:
    static const int display_count = 4;
    int viewing_display_ix = 0;
    int dotGlyph = 0x7F;
    int emptyGlyph = 0xFF;
  public:
    Display_controller () {}
  //LOGIC
    static const bool rightmost_first = true;
    static const bool leftmost_first = !rightmost_first;
  //GLYPHES THAT ARE TO BE VIEWED ARE SAVED HERE
      byte glyphsToView[display_count];
  //SETTINGS
    void all_display_pins_to_output(){
      for(int i=0; i< display_pins_count; ++i){
      pinMode(display_pins[i], OUTPUT);
      }
    }
    void set_glyphs_to_empty(){
      for(int i = 0; i < display_count; i++){
        glyphsToView[i] = emptyGlyph;
      }
      writeGlyphBitmask( emptyGlyph, 0x0F);
    }
    void default_settings(){
      all_display_pins_to_output();
      set_glyphs_to_empty();
    }
  //FUNCTIONS FOR GETTING PRIVATE DATA FROM THIS CLASS
    int get_display_count(){
      return display_count;
    }
    bool are_all_glyphs_empty(){
      for(int i = 0; i < display_count; i++){
        if(glyphsToView[i] != emptyGlyph){
          return false;
        }
      }
      return true;
    }
  //GLYPH OPERATIONS
    void set_glyphs_of_integer(unsigned int val){
      //we create a glyph from each single digit of val and save it
      int valueLength = NumberGenius::digits_in_a_value(val);
      for(int i = 0; i < valueLength; ++i){
        int extractedDigit = NumberGenius::extract_LSfigure_at_pos_i(val, i);
        glyphsToView[i] = digits[extractedDigit];
      }
      for(int i = valueLength; i < display_count; i++){
        glyphsToView[i] = emptyGlyph;
      }
    }
  //VIEWING GLYPHS
    void writeGlyphBitmask( byte glyph, byte pos_bitmask) {
      //basic low-level function for viewing a glyph on display
      digitalWrite( latch_pin, LOW);
      shiftOut( data_pin, clock_pin, MSBFIRST, glyph);
      shiftOut( data_pin, clock_pin, MSBFIRST, pos_bitmask);
      digitalWrite( latch_pin, HIGH);
    }
    //abstraction for viewing
    void x41_writeGlyphR(byte glyph, int pos){
      int base_pos = display_count*2;
      writeGlyphBitmask(glyph, base_pos>>pos);
    }
    void x41_writeGlyphL(byte glyph, int pos){
      writeGlyphBitmask(glyph, 1<<pos);
    }
    void x42_writeDigit(int n, int pos){
      x41_writeGlyphR(digits[n], pos);
    }
    void view_using_multiplex(bool rightmost_first){ //views glyphs on the displays
      int i = viewing_display_ix++;
      rightmost_first? x41_writeGlyphR(glyphsToView[i], i):x41_writeGlyphL(glyphsToView[i], i);
      viewing_display_ix %= display_count;
    }
};

//MAIN CLASS THAT CONTROLS EVERYTHING
class Shield_controller{
  private:
    //controllers of real components of the funshield
      Display_controller displayController;
      Buttons_controller buttonsCtrl;
    //simulating real world objects
      Clock timer;
      Dice dice;
    //logic for display
      bool rightmost_first = true;
      bool leftmost_first = !rightmost_first;
    //variables for implementation of a given problem
      int currButtonIx = 0; //current button index that we will work with
      int dispCount = displayController.get_display_count();
  public:
    Shield_controller () {}
    void default_settings(){
      displayController.default_settings(); //sets display to view empty glyphs and sets display's pins to output mode
      buttonsCtrl.default_settings();
    }
    void setDiceConfigModeGlyphs(){ //set according glyphs to view for dice's configuration mode
      displayController.set_glyphs_to_empty();
      byte glyphOfLetterD = 0b10100001;
      displayController.glyphsToView[0] = digits[dice.throwsToDo];
      displayController.glyphsToView[1] = glyphOfLetterD;
      int diceType = dice.getCurrType();
      if(diceType < 10){
        displayController.glyphsToView[2] = digits[diceType];
      }
      else if(diceType < 100){
        int numLen = 2;
        for(int i = 0; i < numLen; i++){
          displayController.glyphsToView[i+2] = digits[NumberGenius::extract_LSfigure_at_pos_i(diceType, numLen-i-1)];
        }
      }
      else if(diceType == 100){
        int beginningPos = 2;
        for(int i = beginningPos; i < beginningPos+2; i++){
          displayController.glyphsToView[i] = digits[0];
        }
      }
    }
    void settings_for_dice_simulator(){
      setDiceConfigModeGlyphs();
    }
    void controlDiceWithButtonI(int i, Dice::state currDiceState){
      //int i as in button[i]
      switch(i){
          case 0:
            dice.currState = Dice::state::normal;
            break;
          case 1:
            if(currDiceState == Dice::state::normal) dice.currState = Dice::state::config;
            else dice.incrementThrowsToDo();
            setDiceConfigModeGlyphs();
            break;
          case 2:
            if(currDiceState == Dice::state::normal) dice.currState = Dice::state::config;
            else dice.changeType();
            setDiceConfigModeGlyphs();
            break;
        }
    }
    void diceSimulator(){
      Dice::state currDiceState = dice.currState;
      currDiceState == Dice::state::config ? displayController.view_using_multiplex(leftmost_first):displayController.view_using_multiplex(rightmost_first);
      int i = currButtonIx; //for making code more readable (lines don't get too long)
      bool buttonCurrState = buttonsCtrl.is_pressed(i);
      bool button_i_GotPressed = buttonsCtrl.detect_button_state_change(i, buttonsCtrl.pressed, buttonCurrState);
      bool button_i_IsHeldPressed = buttonsCtrl.is_button_held_pressed(i, buttonCurrState);
      if(button_i_IsHeldPressed){ //this if branch is placed on the first place, because we don't want to able the user to go to config mode whilst generating a random number
        if(i == 0){
          if(timer.is_time_to_work(50)){ //every 50 milliseconds
            dice.rollDice(millis());
            displayController.set_glyphs_of_integer(dice.getRollResult());
          }
        }
      }
      else if(button_i_GotPressed){
        controlDiceWithButtonI(i, currDiceState);
      }
      buttonsCtrl.set_last_button_state(buttonCurrState, i); //VERY IMPORTANT update last button state for further detecting state changes
      currButtonIx++;
      currButtonIx %= button_count;
    }
};


Shield_controller shieldController;
void setup() {
  shieldController.default_settings();
  shieldController.settings_for_dice_simulator();
}

void loop() {
  shieldController.diceSimulator();
}
