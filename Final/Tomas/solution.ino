#include "funshield.h"

class Clock {
  private:
    unsigned long last_time = 0;

  public:
    Clock() {}
    bool is_time(int interval) {
      //input is interval=x in milliseconds. returns true every x milliseconds
      unsigned long cur_time = millis();
      if (cur_time >= last_time + interval) {
        last_time = cur_time;
        return true;
      } else {
        return false;
      }
    }
};

const int button_pins[] { button1_pin, button2_pin, button3_pin };
const int button_pins_count = sizeof(button_pins) / sizeof(button_pins[0]);
class Button {
  private:
    const bool pressed = true;
    const bool notPressed = false;
    int button;

  public:
    Button(int b) {
      button = b;
    }
    Button(){}
    //SETTINGS
    bool last_state = false;
    void button_to_input() {
      for (int i = 0; i < button_pins_count; i++) pinMode(button_pins[i], INPUT);
    }
    void default_settings() {
      button_to_input();
    }
    bool is_button_pressed() {
      int state = digitalRead(button);
      if (!state) {
        return true;
      } else {
        return false;
      }
    }
    bool button_state_change_press(bool curr_state) {
      if (last_state == notPressed && curr_state == pressed) return true;
      else
        return false;
    }
    bool is_button_held(bool cur_state) {
      if (last_state == pressed && cur_state == pressed) return true;
      else
        return false;
    }
    bool button_state_change_release(bool curr_state) {
      if (last_state == pressed && curr_state == notPressed) return true;
      else
        return false;
    }
};

Button button1{ button1_pin };
Button button2{ button2_pin };
Button button3{ button3_pin };
constexpr int ledPins[] { led1_pin, led2_pin, led3_pin, led4_pin };
constexpr int ledPinsCount = sizeof(ledPins) / sizeof(ledPins[0]);
const int two_bytes = 16;
const int max_display_pos = 3;
class LED {
  private:
    unsigned long press_time = 0;
    const int periodicDelay = 300;  // delay between consecutive periodic updates [ms]
    Clock timer;

  public:
    //SETTINGS
    void default_settings() {
      for (int i = 0; i < ledPinsCount; ++i) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], OFF);
      }
    }
    void bitValueOnLed(int value) {
      int rest, i = 0;
      int bin[4] = { 0, 0, 0, 0 };

      while (value < 0) {  //if our value is a negative integer
        value = value + two_bytes;
      }

      value = value % two_bytes;

      while (value != 0) {
        rest = value % 2;
        value = value / 2;
        bin[3 - i] = rest;
        i++;
      }

      for (int j = 0; j <= max_display_pos; j++) { // @tom: :(
        if (bin[j] == 1) {
          digitalWrite(ledPins[j], ON);
        } else {
          digitalWrite(ledPins[j], OFF);
        }
      }
    }
    void animation(int number) {
      bitValueOnLed(number);
    }
};

constexpr byte LETTER_GLYPH[] {
  0b10001000,  // A
  0b10000011,  // b
  0b11000110,  // C
  0b10100001,  // d
  0b10000110,  // E
  0b10001110,  // F
  0b10000010,  // G
  0b10001001,  // H
  0b11111001,  // I
  0b11100001,  // J
  0b10000101,  // K
  0b11000111,  // L
  0b11001000,  // M
  0b10101011,  // n
  0b10100011,  // o
  0b10001100,  // P
  0b10011000,  // q
  0b10101111,  // r
  0b10010010,  // S
  0b10000111,  // t
  0b11000001,  // U
  0b11100011,  // v
  0b10000001,  // W
  0b10110110,  // ksi
  0b10010001,  // Y
  0b10100100,  // Z
};
byte numbers_glyph[] = {
  0xC0,  // 0  0b11000000
  0xF9,  // 1  0b11111001
  0xA4,  // 2  0b10100100
  0xB0,  // 3  0b10110000
  0x99,  // 4  0b10011001
  0x92,  // 5  0b10010010
  0x82,  // 6  0b10000010
  0xF8,  // 7  0b11111000
  0x80,  // 8  0b10000000
  0x90   // 9  0b10010000
};

byte Position[] = {
  8,  // 1. pos
  4,  // 2. pos
  2,  // 3. pos
  1   // 4. pos

};
int EMPTY_GLYPH = 0xFF;
const int display_pins[] = { latch_pin, clock_pin, data_pin };
const int display_pins_count = sizeof(display_pins) / sizeof(display_pins[0]);
class Display {
  private:
    static const int display_count = 4;
    byte glyphsToView[display_count];
    int dotGlyph = 0x7F;
    int emptyGlyph = 0xFF;
    int idx_of_pos = 0;  // the most right digit on display
    int count_of_display = 1;

  public:
    Display() {}
    int extract(int number, int pos) {
      for (int _ = 0; _ < pos; _++) {
        number = number / 10;
      }

      number = number % 10;
      return number;
    }
    void write_glyph(byte glyph, byte pos_bitmask) {
      digitalWrite(latch_pin, LOW);
      shiftOut(data_pin, clock_pin, MSBFIRST, glyph);
      shiftOut(data_pin, clock_pin, MSBFIRST, pos_bitmask);
      digitalWrite(latch_pin, HIGH);
    }
    //SETTINGS
    void all_display_pins_to_output() {
      for (int i = 0; i < display_pins_count; ++i) {
        pinMode(display_pins[i], OUTPUT);
      }
    }
    void display_off() {
      for (int i = 0; i < display_count; i++) {
        glyphsToView[i] = emptyGlyph;
      }
    }
    void default_settings() {
      all_display_pins_to_output();
      display_off();
    }

    byte char2glyph(char ch) {
      byte glyph = EMPTY_GLYPH;
      if (isAlpha(ch)) {
        glyph = LETTER_GLYPH[ch - (isUpperCase(ch) ? 'A' : 'a')];
      } else if (isDigit(ch)) {
        glyph = digits[ch - '0'];
      }
      return glyph;
    }
      int counts_of_display_of_number(double number) {  // Kolikaciferne je dane cislo
        int pos = 1;
        while(number > 9){
          pos += 1;
          number /= 10;
        }
        return pos;
      }
    void multiplexing(double number) {
      count_of_display = counts_of_display_of_number(number);
      idx_of_pos++;
      idx_of_pos = idx_of_pos % count_of_display;
    }
    void show_number(int number) {
      multiplexing(number);
      unsigned long num_to_show = extract(number, idx_of_pos);
      write_glyph(numbers_glyph[num_to_show], Position[idx_of_pos]);
    }
};

Display display;
LED led;
const int dices[] = { 4, 6, 8, 10, 12, 20, 100 };
const int dices_count = sizeof(dices) / sizeof(dices[0]);
const int count_of_throws[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int number_of_throws = 9;
const long periodic_delay = 30;
class Dice {
  private:
    enum state {
      normal,
      configuration
    };
    int type_of_dice = dices[0];
    byte letter_d = display.char2glyph('d');
    state curr_state = normal;
    int idx = 0;  // idx of dices[]
    int idy = 0;  // idx of count_of_throws[]
    int count_throws = count_of_throws[0];
    unsigned long press_time;  // Time since pressing button 1
    int generated_number = 0;
    unsigned long how_long_held;
    bool can_show;
    Clock timer;


  public:
    long sum = 0;
    void configuration_show() {
      //E.g 1d04
      int first_digit_of_dicetype = display.extract(type_of_dice, 0);
      int second_digit_of_dicetype = display.extract(type_of_dice, 1);
      display.write_glyph(numbers_glyph[first_digit_of_dicetype], Position[0]);  //Type of dice
      display.write_glyph(numbers_glyph[second_digit_of_dicetype], Position[1]);
      display.write_glyph(letter_d, Position[2]);                     // letter d
      display.write_glyph(numbers_glyph[count_throws], Position[3]);  // Count of throws
    }
    void show_result() {
      display.show_number(sum);
    }
    void count_of_throws_settings() {
      bool currentState = button2.is_button_pressed();
      bool buttonIsPressed = button2.button_state_change_press(currentState);

      if (buttonIsPressed) {
        if (curr_state == state::normal) curr_state = configuration;
        else {
          idy++;            // idy is index of array count_of_throws[]
          idy = (idy % number_of_throws);  // 1-9 throws
          count_throws = count_of_throws[idy];
        }
      }
      if (curr_state == state::configuration) configuration_show();
      button2.last_state = currentState;
    }
    void type_of_dice_settings() {
      bool currentState = button3.is_button_pressed();
      bool buttonIsPressed = button3.button_state_change_press(currentState);

      if (buttonIsPressed) {
        if (curr_state == state::normal) curr_state = configuration;
        else {
          idx++;
          idx = (idx % dices_count);
          type_of_dice = dices[idx];
        }
      }
      if (curr_state == state::configuration) configuration_show();
      button3.last_state = currentState;
    }
    void gen_of_number() {
      bool currentState = button1.is_button_pressed();
      bool buttonIsPressed = button1.button_state_change_press(currentState);
      bool isBeingHeld = button1.is_button_held(currentState);
      bool isReleased = button1.button_state_change_release(currentState);

      if (buttonIsPressed) {
        press_time = millis();
        if (curr_state == state::configuration) curr_state = normal;
      } else if (isBeingHeld) {
        if (curr_state == state::configuration) curr_state = normal;
        else {
          can_show = false;
          unsigned long current_time = millis();
          how_long_held = current_time - press_time;

          srandom(how_long_held);  // Seed depending on how long we pressed the button
          sum = 0;
          // Binomial distribution, each time we throw a dice and then we add to our sum
          for (int throws = 0; throws < count_throws; throws++) {
            sum += random(1, type_of_dice + 1);
            if (timer.is_time(periodic_delay)) {
              show_result();  // How fast should our result update on display [30ms], while generating
              led.animation(sum);
            }
          }
        }
      }

      else if (isReleased) {
        can_show = true;
      }
      if (curr_state == state::normal && can_show) show_result();
      button1.last_state = currentState;
    }
};

Button button_settings;
Dice dice;
void setup() {
  button_settings.default_settings();
  led.default_settings();
  display.default_settings();
}

void loop() {
  dice.count_of_throws_settings();
  dice.type_of_dice_settings();
  dice.gen_of_number();
}
