// Pins
#define BUTTON_A_PIN   5
#define BUTTON_B_PIN   6
#define BUTTON_RESET   2
#define LED_PIN        3

// LEDs
#define NUM_LEDS       2

// Button debounce
unsigned long lastDebounceTimeA = 0;
unsigned long lastDebounceTimeB = 0;
unsigned long lastDebounceTimeR = 0;
const unsigned long debounceDelay = 10;

// Key repeat suppression
unsigned long lastKeyTimeA = 0;
unsigned long lastKeyTimeB = 0;
const unsigned long keyRepeatDelay = 0;

int lastButtonStateA = HIGH;
int lastButtonStateB = HIGH;
int lastButtonStateR = HIGH;

bool buttonLatchA = false;
bool buttonLatchB = false;
bool buttonLatchR = false;

// Button IDs
uint8_t buttonA = 0;
uint8_t buttonB = 1;
uint8_t buttonR = 2;

// ---------------- COLORS ----------------
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
uint32_t off;

// ---------------- MODE CONFIG ----------------
struct ModeConfig {
  uint32_t colorA_default;
  uint32_t colorA_pressed;
  uint32_t colorB_default;
  uint32_t colorB_pressed;
};

// Allocate space - filled in setup()
ModeConfig modes[2];

int currentMode = 0;
const int totalModes = sizeof(modes) / sizeof(modes[0]);