#include "LedAnimation.h"

#define FADE_SPEED 5

void LedAnimation::setup()
{
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(m_leds, NUM_LEDS);
}

void LedAnimation::statupAnimation()
{
    CRGB startupColor = CRGB(255, 255, 255);
    for (int i = 0; i < 70; i++) {
        showLoops(startupColor.r, startupColor.g, startupColor.b, 30, 30, 1000, 1);
    }
    for (int brightness = 255; brightness >= 0; brightness -= FADE_SPEED) {
        CRGB fadedColor = startupColor;
        fadedColor.nscale8(brightness);
        fill_solid(m_leds, NUM_LEDS, fadedColor);
        FastLED.show();
        delay(20);
    }
}

void LedAnimation::showLoops(int red, int green, int blue, int tail_length, int delay_duration, int interval, int direction) {
    unsigned long currentMillis = millis();   // Get the time
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;         // Save the last time the LEDs were updated
        count = 0;                              // Reset the count to 0 after each interval
    }
    if (direction == -1) {        // Reverse direction option for LEDs
        if (count < NUM_LEDS) {
            m_leds[NUM_LEDS - (count % (NUM_LEDS + 1))].setRGB(red, green, blue);    // Set LEDs with the color value
            count++;
        }
    } else {
        if (count < NUM_LEDS) {     // Forward direction option for LEDs
            m_leds[count % (NUM_LEDS + 1)].setRGB(red, green, blue);    // Set LEDs with the color value
            count++;
        }
    }
    fadeToBlackBy(m_leds, NUM_LEDS, tail_length);                 // Fade the tail LEDs to black
    FastLED.show();
    delay(delay_duration);                                      // Delay to set the speed of the animation
}

void LedAnimation::pulseLeds(CRGB color) 
{
    // Set all LEDs to the color and then show them
    fill_solid(m_leds, NUM_LEDS, color);
    FastLED.show();
    delay(200); // Wait for a short period
    
    // Gradually fade out all LEDs while maintaining the color
    for (int brightness = 255; brightness >= 0; brightness -= FADE_SPEED) {
        CRGB fadedColor = color;
        fadedColor.nscale8(brightness);
        fill_solid(m_leds, NUM_LEDS, fadedColor);
        
        FastLED.show();
        delay(20); // Delay to control the speed of the fade out
    }
}

void LedAnimation::buyLambo()
{
    CRGB WHITE = CRGB(255, 255, 255);
    int flashCount = 0;
    
    while (flashCount < 1000000000) {
        // Turn on all LEDs to white
        fill_solid(m_leds, NUM_LEDS, WHITE);
        FastLED.show();
        delay(100); // Wait for a short period
        
        // Turn off all LEDs
        fill_solid(m_leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100); // Wait for a short period
        
        flashCount++;
    }
}