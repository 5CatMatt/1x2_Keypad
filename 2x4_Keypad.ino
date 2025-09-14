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

// Softer but visibly colored pastels
uint32_t pastelBlue    = 0; 
uint32_t pastelGreen   = 0;
uint32_t pastelRed     = 0;
uint32_t pastelPurple  = 0;
uint32_t pastelYellow  = 0;
uint32_t pastelOrange  = 0;
uint32_t pastelCyan    = 0;
uint32_t pastelMagenta = 0;
uint32_t pastelWhite   = 0;
uint32_t pastelOff     = 0;

void setup() {
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);

  strip.begin();
  strip.setBrightness(100); // Scale 0-255 (reduce glare, keep colors visible)

  // Better pastel definitions (not too white)
  pastelBlue    = strip.Color(80, 150, 255);   // pastel blue
  pastelGreen   = strip.Color(120, 255, 150);  // pastel green
  pastelRed     = strip.Color(255, 100, 120);  // pastel pink/red
  pastelPurple  = strip.Color(190, 90, 255);   // pastel purple
  pastelYellow  = strip.Color(255, 220, 120);  // soft yellow
  pastelOrange  = strip.Color(255, 170, 100);  // soft orange
  pastelCyan    = strip.Color(100, 255, 230);  // cyan
  pastelMagenta = strip.Color(255, 120, 200);  // magenta
  pastelWhite   = strip.Color(200, 200, 200);  // off-white
  pastelOff     = strip.Color(0, 0, 0);        // off

  // Initial colors
  strip.setPixelColor(0, pastelBlue);
  strip.setPixelColor(1, pastelGreen);
  strip.show();
}

void loop() {
  handleButton(BUTTON_A_PIN, lastButtonStateA, lastDebounceTimeA, 0);
  handleButton(BUTTON_B_PIN, lastButtonStateB, lastDebounceTimeB, 1);
  handleButton(BUTTON_RESET, lastButtonStateR, lastDebounceTimeR, 2);
}

void handleButton(int pin, int &lastState, unsigned long &lastTime, int buttonID) {
  int reading = digitalRead(pin);

  if (reading != lastState) {
    lastTime = millis();
  }

  if ((millis() - lastTime) > debounceDelay) {
    if (reading == LOW) {
      switch (buttonID) {
        case 0: // Button A pressed
          strip.setPixelColor(0, pastelRed);
          break;

        case 1: // Button B pressed
          strip.setPixelColor(1, pastelPurple);
          break;

        case 2: // Reset pressed -> ALL OFF
          strip.setPixelColor(0, pastelOff);
          strip.setPixelColor(1, pastelOff);
          break;
      }
      strip.show();
    } else {
      // Release actions (but not reset!)
      if (buttonID == 0) strip.setPixelColor(0, pastelBlue);
      if (buttonID == 1) strip.setPixelColor(1, pastelGreen);
      if (buttonID == 2) {
        // On reset release → restore defaults
        strip.setPixelColor(0, pastelBlue);
        strip.setPixelColor(1, pastelGreen);
      }
      strip.show();
    }
  }
  lastState = reading;
}
