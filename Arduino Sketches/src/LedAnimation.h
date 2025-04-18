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

    void fadeIn(CRGB color, uint32_t duration=1000, uint32_t step=3);
    void fadeOut(CRGB color, uint32_t duration=1000, uint32_t step=3);
    void fadeInOut(CRGB color, uint32_t duration=1000, uint32_t step=3);
    void fadeOff(uint32_t duration=1000, uint32_t step=3);
    void fadeAll(uint8_t brightness=250);
    void rainbow(uint32_t duration=3000, uint32_t speed=5, uint32_t step=1);
    void showLoops(int red, int green, int blue, int tail_length, int delay_duration, int interval, int direction);
    void buyLambo();

private:
    CRGB m_leds[NUM_LEDS];
    CRGB m_rainbow[NUM_RAINBOW];

    unsigned long previousMillis = 0;           // Stores last time LEDs were updated
    int count = 0;                              // Stores count for incrementing up to the NUM_LEDs
};

#endif // LED_ANIMATION_H