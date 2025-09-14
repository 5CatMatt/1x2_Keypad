#include <Adafruit_NeoPixel.h>

// Pins
#define BUTTON_A_PIN   5
#define BUTTON_B_PIN   6
#define BUTTON_RESET   2
#define LED_PIN        3

// LEDs
#define NUM_LEDS       2
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Button debounce
unsigned long lastDebounceTimeA = 0;
unsigned long lastDebounceTimeB = 0;
unsigned long lastDebounceTimeR = 0;
const unsigned long debounceDelay = 50;

int lastButtonStateA = HIGH;
int lastButtonStateB = HIGH;
int lastButtonStateR = HIGH;

// Colors (now using strip.Color)
uint32_t blueMid;
uint32_t greenBright;
uint32_t greenMid;
uint32_t grey;
uint32_t lightGrey;
uint32_t mintLight;
uint32_t red;
uint32_t green;
uint32_t blue;
uint32_t lightPurple;
uint32_t yellow;
uint32_t darkYellow;
uint32_t teal;
uint32_t orange;
uint32_t dullRed;
uint32_t FOLDER;
uint32_t FOX;
uint32_t EDIT;
uint32_t CALC;
uint32_t colorOff;

uint32_t defaultColorA;
uint32_t defaultColorB;

uint32_t pressedColorA;
uint32_t pressedColorB;

uint8_t brightness = 176; // 0-255

uint8_t buttonA = 0;
uint8_t buttonB = 1;
uint8_t buttonR = 2;

void setup() {
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);

  strip.begin();
  strip.setBrightness(brightness);

  // Define colors
  blueMid      = strip.Color(0, 17, 65);
  greenBright  = strip.Color(0, 128, 0);
  greenMid     = strip.Color(0, 42, 5);
  grey         = strip.Color(5, 5, 5);
  lightGrey    = strip.Color(12, 20, 20);
  mintLight    = strip.Color(28, 74, 44);
  red          = strip.Color(75, 5, 5);
  green        = strip.Color(5, 75, 5);
  blue         = strip.Color(5, 5, 75);
  lightPurple  = strip.Color(35, 35, 95);
  yellow       = strip.Color(45, 45, 5);
  darkYellow   = strip.Color(15, 15, 5);
  teal         = strip.Color(5, 35, 25);
  orange       = strip.Color(100, 50, 0);
  dullRed      = strip.Color(26, 0, 0);
  FOLDER       = strip.Color(95, 77, 28);
  FOX          = strip.Color(200, 54, 8);
  EDIT         = strip.Color(50, 115, 25);
  CALC         = strip.Color(53, 56, 59);
  colorOff     = strip.Color(0, 0, 0);

  // Assign defaults
  defaultColorA = blueMid;
  defaultColorB = green;

  pressedColorA = red;
  pressedColorB = orange;

  // Initial state
  strip.setPixelColor(buttonA, defaultColorA);
  strip.setPixelColor(buttonB, defaultColorB);
  strip.show();
}

void loop() {
  handleButton(BUTTON_A_PIN, lastButtonStateA, lastDebounceTimeA, buttonA);
  handleButton(BUTTON_B_PIN, lastButtonStateB, lastDebounceTimeB, buttonB);
  handleButton(BUTTON_RESET, lastButtonStateR, lastDebounceTimeR, buttonR);
}

void handleButton(int pin, int &lastState, unsigned long &lastTime, int buttonID) {
  int reading = digitalRead(pin);

  if (reading != lastState) {
    lastTime = millis();
  }

  if ((millis() - lastTime) > debounceDelay) {
    if (reading == LOW) {
      // Button pressed
      if (buttonID == buttonA) {
        strip.setPixelColor(buttonA, pressedColorA);
      } else if (buttonID == buttonB) {
        strip.setPixelColor(buttonB, pressedColorB);
      } else if (buttonID == buttonR) {
        strip.setPixelColor(buttonA, colorOff);
        strip.setPixelColor(buttonB, colorOff);
      }
      strip.show();
    } else {
      // Button released
      if (buttonID == buttonA) {
        strip.setPixelColor(buttonA, defaultColorA);
      } else if (buttonID == buttonB) {
        strip.setPixelColor(buttonB, defaultColorB);
      } else if (buttonID == buttonR) {
        strip.setPixelColor(buttonA, defaultColorA);
        strip.setPixelColor(buttonB, defaultColorB);
      }
      strip.show();
    }
  }
  lastState = reading;
}
