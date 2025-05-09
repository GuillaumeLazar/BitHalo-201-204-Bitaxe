// v2 - Written by IamGPIO - BitHalo for the Bitaxe
#include <Arduino.h>
// #include <FastLED.h>

#include "LedAnimation.h"

#define BUTTON_PIN 6          // Button pin
#define MAX_INPUT_LENGTH 256  // Maximum length of input buffer
#define MAX_NUMBER 8          // Maximum number for LED colors

LedAnimation ledAnimation;
String inputString = "";        

// Button stuff
int currentNumber = 3;                      // Number to determine LED color
bool buttonPressed = false;                 // Flag to track button state
void handleButtonPress();
void processInput();

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);        // Set button pin as input with pull-up resistor
  Serial.begin(115200);
  inputString.reserve(MAX_INPUT_LENGTH);
  
  // BitHalo startup animation
  ledAnimation.trailSolid(CRGB::White, 1000, NUM_LEDS, true);
  ledAnimation.fadeOff(3000);
}

void loop() {
  // Check for button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!buttonPressed) { // Only act on the first button press
      buttonPressed = true;
      handleButtonPress();
    }
  } else {
    buttonPressed = false; // Reset flag when button is released
  }
  
  // Actively check for serial data
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    // Check for newline character or buffer overflow
    if (inChar == '\n' || inputString.length() >= MAX_INPUT_LENGTH) {
      processInput();
    }
  }
}

void processInput() {
  if (inputString.indexOf("Initializing serial") >= 0) {
    for (int i = 0; i < 250; i++) {
      ledAnimation.trailSolid(CRGB::Purple);
    }

  } else if (inputString.indexOf("mining.notify") >= 0) {
    ledAnimation.fadeInOut(CRGB::Blue, 1000);

  } else if  (inputString.indexOf("accepted") >= 0) {
    ledAnimation.fadeInOut(CRGB::Green, 1000);

  } else if (inputString.indexOf("rejected") >= 0) {
    ledAnimation.fadeInOut(CRGB::Red, 1000);

  } else if  (inputString.indexOf("BLOCK FOUND") >= 0) {
    ledAnimation.rainbowInfinite();

  } else if (inputString.indexOf("asic_result") >= 0) {
    // ledAnimation.fadeInOut(CRGB::Cyan, 50);
  }
  
  // Clear the input string for new data
  inputString = "";
}

void handleButtonPress() {
  // Increment the current number and wrap around if it exceeds MAX_NUMBER
  currentNumber++;
  if (currentNumber > MAX_NUMBER) {
    currentNumber = 0;
  }
  
  // Print the current number to Serial for debugging
  // Serial.print("Current Number: ");
  // Serial.println(currentNumber);
  
  // Pulse the LEDs to show the new color
  ledAnimation.fadeInOut(CRGB::Purple, 1000);
}

// Function to map numbers to colors
// CRGB getColorForNumber(int number) {
//   switch (number) {
//     case 0: return CRGB(50, 255, 0);   // Orange (GRB: G=165, R=255, B=0)
//     case 1: return CRGB(0, 255, 0);   // Red (GRB: G=255, R=0, B=0)
//     case 2: return CRGB(255, 0, 0);   // Green (GRB: G=0, R=255, B=0)
//     case 3: return CRGB(0, 0, 255);   // Blue (GRB: G=0, R=0, B=255)
//     case 4: return CRGB(255, 0, 255); // Cyan (GRB: G=255, R=0, B=255)
//     case 5: return CRGB(0, 255, 255); // Magenta (GRB: G=0, R=255, B=255)
//     case 6: return CRGB(255, 255, 0); // Yellow (GRB: G=255, R=255, B=0)
//     case 7: return CRGB(0, 128, 128); // Purple (GRB: G=128, R=0, B=128)
//     case 8: return CRGB(150, 150, 150); // White (GRB: G=255, R=255, B=255)
//     default: return CRGB(0, 0, 0);     // Black (off)
//   }
// }
