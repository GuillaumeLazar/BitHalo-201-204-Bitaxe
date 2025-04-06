#ifndef LED_ANIMATION_H
#define LED_ANIMATION_H

#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 8

class LedAnimation
{
public:
    void setup();
    void statupAnimation();

    void showLoops(int red, int green, int blue, int tail_length, int delay_duration, int interval, int direction);
    void pulseLeds(CRGB color);
    void buyLambo();

private:
    CRGB m_leds[NUM_LEDS];

    unsigned long previousMillis = 0;           // Stores last time LEDs were updated
    int count = 0;                              // Stores count for incrementing up to the NUM_LEDs
};

#endif // LED_ANIMATION_H