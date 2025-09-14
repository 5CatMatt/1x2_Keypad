#include "defines.h"

#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ---------------- SETUP ----------------
void setup() {
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);

  strip.begin();
  strip.setBrightness(176);

  // Define colors
  blueMid       = strip.Color(0, 17, 65);
  greenBright   = strip.Color(0, 128, 0);
  greenMid      = strip.Color(0, 42, 5);
  grey          = strip.Color(5, 5, 5);
  lightGrey     = strip.Color(12, 20, 20);
  mintLight     = strip.Color(28, 74, 44);
  red           = strip.Color(75, 5, 5);
  green         = strip.Color(5, 75, 5);
  blue          = strip.Color(5, 5, 75);
  lightPurple   = strip.Color(35, 35, 95);
  yellow        = strip.Color(45, 45, 5);
  darkYellow    = strip.Color(15, 15, 5);
  teal          = strip.Color(5, 35, 25);
  orange        = strip.Color(100, 50, 0);
  dullRed       = strip.Color(26, 0, 0);
  FOLDER        = strip.Color(95, 77, 28);
  FOX           = strip.Color(200, 54, 8);
  EDIT          = strip.Color(50, 115, 25);
  CALC          = strip.Color(53, 56, 59);
  off           = strip.Color(0, 0, 0);

  // Now that colors exist, configure modes
  modes[0] = { blueMid, red, green, orange };   // Mode 0: Copy / Paste
  modes[1] = { yellow, teal, lightPurple, red };     // Mode 1: Find / Save

  // Set initial mode colors
  applyModeColors();

  Keyboard.begin();
}

// ---------------- LOOP ----------------
void loop() {
  handleButton(BUTTON_A_PIN, lastButtonStateA, lastDebounceTimeA, buttonA);
  handleButton(BUTTON_B_PIN, lastButtonStateB, lastDebounceTimeB, buttonB);
  handleButton(BUTTON_RESET, lastButtonStateR, lastDebounceTimeR, buttonR);
}

// ---------------- BUTTON HANDLER ----------------
void handleButton(int pin, int &lastState, unsigned long &lastTime, int buttonID) {
  int reading = digitalRead(pin);

  if (reading != lastState) {
    lastTime = millis();
  }

  if ((millis() - lastTime) > debounceDelay) {
    if (reading == LOW) {
      // Button pressed
      if (buttonID == buttonA) {
        strip.setPixelColor(buttonA, modes[currentMode].colorA_pressed);
        if (millis() - lastKeyTimeA > keyRepeatDelay) {
          performAction(buttonA);
          lastKeyTimeA = millis();
        }
      } 
      else if (buttonID == buttonB) {
        strip.setPixelColor(buttonB, modes[currentMode].colorB_pressed);
        if (millis() - lastKeyTimeB > keyRepeatDelay) {
          performAction(buttonB);
          lastKeyTimeB = millis();
        }
      } 
      else if (buttonID == buttonR) {
        // Cycle mode
        currentMode = (currentMode + 1) % totalModes;
        applyModeColors();
      }
      strip.show();
    } else {
      // Button released → restore defaults
      if (buttonID == buttonA) {
        strip.setPixelColor(buttonA, modes[currentMode].colorA_default);
      } else if (buttonID == buttonB) {
        strip.setPixelColor(buttonB, modes[currentMode].colorB_default);
      }
      strip.show();
    }
  }
  lastState = reading;
}

// ---------------- ACTIONS ----------------
void performAction(int buttonID) {
  switch (currentMode) {
    case 0: // Copy / Paste
      if (buttonID == buttonA) {
        Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('c');
        delay(10); Keyboard.releaseAll();
      } else if (buttonID == buttonB) {
        Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('v');
        delay(10); Keyboard.releaseAll();
      }
      break;

    case 1: // Find / Save
      if (buttonID == buttonA) {
        Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('f');
        delay(10); Keyboard.releaseAll();
      } else if (buttonID == buttonB) {
        Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('s');
        delay(10); Keyboard.releaseAll();
      }
      break;
  }
}

// ---------------- HELPERS ----------------
void applyModeColors() {
  strip.setPixelColor(buttonA, modes[currentMode].colorA_default);
  strip.setPixelColor(buttonB, modes[currentMode].colorB_default);
  strip.show();
}
