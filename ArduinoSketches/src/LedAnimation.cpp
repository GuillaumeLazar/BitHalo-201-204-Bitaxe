#include "LedAnimation.h"

LedAnimation::LedAnimation()
{
    // setup FastLED
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(m_leds, NUM_LEDS);

    // build rainbow array
    m_rainbow[0] = CRGB::Violet;
    m_rainbow[1] = CRGB::Indigo;
    m_rainbow[2] = CRGB::Blue;
    m_rainbow[3] = CRGB::Green;
    m_rainbow[4] = CRGB::Yellow;
    m_rainbow[5] = CRGB::Orange;
    m_rainbow[6] = CRGB::Red;
}

void LedAnimation::fadeIn(CRGB color, uint32_t duration, uint32_t step)
{
    int delayValue = duration / (256 / step);
    for (int brightness = 0; brightness < 256; brightness += step) {
        CRGB fadedColor = color;
        fadedColor.nscale8(brightness);
        fill_solid(m_leds, NUM_LEDS, fadedColor);
        FastLED.show();
        delay(delayValue);
    } 
}

void LedAnimation::fadeOut(CRGB color, uint32_t duration, uint32_t step)
{
    int delayValue = duration / (256 / step);
    for (int brightness = 255; brightness >= 0; brightness -= step) {
        CRGB fadedColor = color;
        fadedColor.nscale8(brightness);
        fill_solid(m_leds, NUM_LEDS, fadedColor);
        FastLED.show();
        delay(delayValue);
    }
}

void LedAnimation::fadeInOut(CRGB color, uint32_t duration, uint32_t step)
{
    fadeIn(color, duration / 2, step);
    fadeOut(color, duration / 2, step);
}

void LedAnimation::fadeOff(uint32_t duration=1000, uint32_t step=3)
{
    int delayValue = duration / (256 / step);
    for (int brightness = 255; brightness >= 0; brightness -= step) {
        for(int i = 0; i < NUM_LEDS; i++) { 
            m_leds[i].nscale8(brightness);
        }
        FastLED.show();
        delay(delayValue);
    }
}

void LedAnimation::fadeAll(uint8_t brightness)
{
    for(int i = 0; i < NUM_LEDS; i++) { 
        m_leds[i].nscale8(brightness);
    }
}

void LedAnimation::rainbow(uint32_t duration, uint32_t speed, uint32_t step)
{
    uint32_t elapsedTime = 0;
    int delayValue = duration / (100 / step);
    for (uint8_t hue = 0; hue < 100; hue += step) {
        fill_rainbow(m_leds, NUM_LEDS, hue * speed, 15); 
        FastLED.show();
        delay(delayValue);
        elapsedTime += delayValue;
    }
}

// direction :
// -1: clockwise
//  1: counterclockwise
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