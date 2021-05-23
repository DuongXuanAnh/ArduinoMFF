#include "funshield.h"
#include "input.h"
#include <ctype.h>
// map of letter glyphs
constexpr byte LETTER_GLYPH[] {
  0b10001000,   // A
  0b10000011,   // b
  0b11000110,   // C
  0b10100001,   // d
  0b10000110,   // E
  0b10001110,   // F
  0b10000010,   // G
  0b10001001,   // H
  0b11111001,   // I
  0b11100001,   // J
  0b10000101,   // K
  0b11000111,   // L
  0b11001000,   // M
  0b10101011,   // n
  0b10100011,   // o
  0b10001100,   // P
  0b10011000,   // q
  0b10101111,   // r
  0b10010010,   // S
  0b10000111,   // t
  0b11000001,   // U
  0b11100011,   // v
  0b10000001,   // W
  0b10110110,   // ksi
  0b10010001,   // Y
  0b10100100,   // Z
};
constexpr byte EMPTY_GLYPH = 0b11111111;

constexpr int positionsCount = 4;
constexpr unsigned int scrollingInterval = 300;

/** 
 * Show chararcter on given position. If character is not letter, empty glyph is displayed instead.
 * @param ch character to be displayed
 * @param pos position (0 = leftmost)
 */
SerialInputHandler input;
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

//DISPLAYS
const int display_pins[] = {latch_pin, clock_pin, data_pin};
const int display_pins_count = sizeof(display_pins)/sizeof(display_pins[0]);
class Display_controller{
  private:
    static const int display_count = 4;
    byte glyphsToView[display_count];
    //for viewing a decimal number (x52)
    int firstNonzeroIndex; //index of the first nonzero number following the leading zeros of a number we're viewing on display
    int displaysNeededToViewOn = display_count;
    int dotGlyph = 0x7F;
    int emptyGlyph = 0xFF;
  public:
    Display_controller () {}
    void writeGlyphBitmask( byte glyph, byte pos_bitmask) {
      digitalWrite( latch_pin, LOW);
      shiftOut( data_pin, clock_pin, MSBFIRST, glyph);
      shiftOut( data_pin, clock_pin, MSBFIRST, pos_bitmask);
      digitalWrite( latch_pin, HIGH);
    }
  //SETTINGS
    void all_display_pins_to_output(){
      for(int i=0; i< display_pins_count; ++i){
      pinMode(display_pins[i], OUTPUT);
      }
    }
    void display_off(){
      for(int i = 0; i < display_count; i++){
        glyphsToView[i] = emptyGlyph;
      }
      writeGlyphBitmask( emptyGlyph, 0x0F);
    }
    void default_settings(){
      all_display_pins_to_output();
      display_off();
    }
  //FUNCTIONS FOR GETTING PRIVATE DATA FROM THIS CLASS
    byte get_glyphToView_i(int i){
      return glyphsToView[i];
    }
    int get_display_count(){
      return display_count;
    }
    bool all_glyphs_empty(){
      for(int i = 0; i < display_count; i++){
        if(glyphsToView[i] != emptyGlyph){
          return false;
        }
      }
      return true;
    }
  //FUNCTIONS FOR GLYPH OPERATIONS
    void shift_glyphs_left(){
      for(int i = 0; i < display_count - 2; i++){
        glyphsToView[i] = glyphsToView[i+1];
      }
      glyphsToView[display_count-1] = emptyGlyph;
    }
    void shift_glyphs_right(){
      for(int i = display_count - 1; i > 0; i--){
        glyphsToView[i] = glyphsToView[i-1];
      }
      glyphsToView[0] = emptyGlyph;
    }
    void add_dot_to_glyph_i(int i){
      glyphsToView[i] = glyphsToView[i] & dotGlyph;
    }
    byte convert_char2glyph(char ch){
      byte glyph = EMPTY_GLYPH;
      if (isAlpha(ch)) {
        glyph = LETTER_GLYPH[ ch - (isUpperCase(ch) ? 'A' : 'a') ];
      }
      else if(isDigit(ch)){
        glyph = digits[ch - '0'];
      }
      return glyph;
    }
  //FUNCTIONS THAT SET GLYPHS CORRESPONDINGLY
    void set_glyph_of_char(int character, int pos){
      byte glyph_of_char = convert_char2glyph(character);
      glyphsToView[pos] = glyph_of_char;
    }
    void set_glyphs_of_string(const char* str){
      for(int i = 0; i < display_count; i++){
        set_glyph_of_char(*str++, i);
      }
    }
  //VIEWING GLYPHS
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
    void view(bool rightmost_first){ //views glyphs on the displays
      for(int i = 0; i < displaysNeededToViewOn; ++i){
          rightmost_first? x41_writeGlyphR(glyphsToView[i], i):x41_writeGlyphL(glyphsToView[i], i);
      }
    }
};

class StringManager{
  public:
  static int get_length( const char *str) {
    size_t i = 0;
    while( *str++) ++i;
    //*str -= i; //while loop changed the pointer - we want to reset it as not to change the given string pointer
    return i;
}
};

class Shield_controller{
  private:
    //components of funshield
    Display_controller displayController;
    Clock timer;
    //logic and info for display
    bool rightmost_first = true;
    bool leftmost_first = !rightmost_first;
    int display_ix = 0;
    //for viewing string on display
    const char* str; //FOR USING IN x63, SET IT TO A STRING THAT YOU WANT TO VIEW ON DISPLAY
    const char* str_copy = str; //for x63
    bool reset_string_enabled = true;
    bool need_to_get_message = true;
  public:
    Shield_controller () {}
    void default_settings(){
      displayController.default_settings();
    }
    void setCharToViewOnDisplay(int character, int pos){
      displayController.set_glyph_of_char(character, pos);
    }
    void viewGlyphsOnDisplay(bool rightmost_first){ //if rightmost_first == true, then displayContoller.glyphToView[0] is viewed at rightmost display. else it is viewed at leftmost display
      displayController.view(rightmost_first);
    }
    void x61_viewCharOnDispPos(int ch, int pos){
      setCharToViewOnDisplay(ch, pos);
      viewGlyphsOnDisplay(leftmost_first);
    }
    void x62_viewStaticText(const char* str){
      displayController.set_glyphs_of_string(str);
      viewGlyphsOnDisplay(leftmost_first);
    }
    void x63_viewRunningText(int shift_delay, bool load_str_from_input){ 
      //FOR CHANGING INPUT TEXT, SET VARIABLE str TO SOME TEXT - THE VARIABLE IS IN PRIVATE MEMBERS OF THIS CLASS
      byte glyph_to_view = displayController.get_glyphToView_i(display_ix);
      if(!reset_string_enabled){
        displayController.x41_writeGlyphR(glyph_to_view, display_ix);
      }
      display_ix = (display_ix + 1) % displayController.get_display_count(); //increment the index of the display we want to view on
      if(displayController.all_glyphs_empty()){ //if the display is cleared (doesn't view anything), communicate that we need to load a new message
        reset_string_enabled = true;
      }
      if(reset_string_enabled){ //if we need to get a message, load it, and then communicate that a message was loaded and it is not needed to load anymore
        load_str_from_input ? str = input.getMessage():str = str_copy; //reset str according to parameter
        reset_string_enabled = false;
      }
      if(*str){ //if the pointer isn't at the end of the string
        if(timer.is_time_to_work(shift_delay)){ //if a given interval has passed
          //the two lines of code below cause the string's glyphs to be stored in reversed order.
          //given a string "HELLO", the storing of glyphs would proceed like this ("_" is empty glyph):
          //[H,_,_,_] -> [E,H,_,_] -> [L,E,H,_] -> [L,L,E,H] -> [O,L,L,E]
          displayController.shift_glyphs_right();
          displayController.set_glyph_of_char(*str++, 0);
        }
      }
      else if (!displayController.all_glyphs_empty()){ 
        //in this branch, the pointer is at the end of the string, but there are still some remaining glyphs on the display
        //we need to shift the remaining glyphs to clear the display
        if(timer.is_time_to_work(shift_delay)){ //every time the given interval passes, shift the glyphs right
          displayController.shift_glyphs_right(); //this shift works just like bit shifting
        }
        //once the display is cleared, the code doesn't get to this branch - it gets to the "if the display is cleared" branch
      }
    }
    void x65_viewTextFromInput(int shift_delay){
      x63_viewRunningText(shift_delay, true);
    }
};

Shield_controller shieldController;
void setup() {
  input.initialize();
  shieldController.default_settings();
}


void loop() {
  //x62
  //shieldController.x62_viewStaticText("Arduino");
  //x65
  shieldController.x65_viewTextFromInput(scrollingInterval);
  input.updateInLoop();
}
