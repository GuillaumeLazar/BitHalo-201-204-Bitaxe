#ifndef LED_ANIMATION_H
#define LED_ANIMATION_H

#include <FastLED.h>

#define NUM_LEDS 30
#define NUM_RAINBOW 7
#define DATA_PIN 8

class LedAnimation
{
public:
    LedAnimation();

    // fadings
    void fadeIn(CRGB color, uint32_t duration=1000, uint32_t step=3);
    void fadeOut(CRGB color, uint32_t duration=1000, uint32_t step=3);
    void fadeInOut(CRGB color, uint32_t duration=1000, uint32_t step=3);
    void fadeOff(uint32_t duration=1000, uint32_t step=3);
    void fadeAll(uint8_t brightness=128);

    // animations
    void rainbow(uint32_t duration=3000, uint32_t speed=5, uint32_t step=1);
    void rainbowInfinite(uint32_t duration=3000, uint32_t speed=5, uint32_t step=1);
    void trailSolid(CRGB color, uint32_t duration=1000, uint8_t distance=NUM_LEDS, bool isReversed=false, uint8_t tailFading=50);

private:
    CRGB m_leds[NUM_LEDS];
    CRGB m_rainbow[NUM_RAINBOW];

    uint32_t m_previousMillis = 0;           // Stores last time LEDs were updated
    uint32_t m_count = 0;                    // Stores count for incrementing up to the NUM_LEDs
};

#endif // LED_ANIMATION_H