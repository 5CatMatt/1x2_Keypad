# Arduino Macro Keypad using Adafruit Neokey 2 Featherwing

This project turns an **Arduino Pro Micro** into a small programmable **macro keypad** with two functional buttons and a mode-switching button. Each button can send different **keyboard shortcuts** using `Keyboard.h`, with customizable **NeoPixel LED feedback** to indicate pressed states and current mode.  

---

## Features

- Two functional buttons (`A` and `B`) for sending keyboard shortcuts.  
- One reset button to **cycle through multiple modes**.  
- **NeoPixel LEDs** to indicate button status (default / pressed) and current mode.  
- Adjustable **key repeat suppression** to avoid accidental repeated inputs.  
- Easy-to-edit **macro table** and **LED color configuration**.  
- Expandable to **more modes** and **different keyboard shortcuts**.  

---

## Hardware

- **Arduino Pro Micro (ATmega32u4)** – needed for USB HID functionality.  
- **2x NeoPixel LEDs** (WS2812/NeoPixel compatible) for visual feedback.  
- **3x Mechanical Buttons** (A, B, Reset).  
- **Wires & Breadboard / Custom PCB**.  

### Pin Connections

| Component      | Arduino Pin |
|----------------|-------------|
| Button A       | 5           |
| Button B       | 6           |
| Button Reset   | 2           |
| NeoPixel Data  | 3           |

---

## Software

- Arduino IDE (1.8+ recommended)  
- Libraries:  
  - [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)  
  - Built-in `Keyboard.h` (no extra library required)  

---

## Usage

1. **Install libraries**: Open the Arduino IDE, go to *Sketch → Include Library → Manage Libraries…* and install **Adafruit NeoPixel**.  
2. **Upload the sketch** to the Arduino Pro Micro.  
3. **Connect the buttons and LEDs** as described above.  
4. Press **Button A** or **Button B** to trigger the current mode’s shortcut.  
5. Press **Reset** to cycle through modes. LEDs update automatically to reflect pressed states and defaults.  

---

## Configuration

### 1. Key Macros

Macros are defined in `performAction()` and can be easily expanded:

```cpp
switch (currentMode) {
  case 0: // Copy / Paste
    if (buttonID == buttonA) Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('c');
    if (buttonID == buttonB) Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('v');
    break;
  case 1: // Find / Save
    if (buttonID == buttonA) Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('f');
    if (buttonID == buttonB) Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('s');
    break;
}
