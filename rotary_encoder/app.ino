/*
EncoderStepCounter lib
https://github.com/M-Reimer/EncoderStepCounter

CLK -> PIN 5
DT  -> PIN 6

*/

#include "EncoderStepCounter.h"

#define ENCODER_PIN1 5
#define ENCODER_PIN2 6

#define SWITCH_PIN 7
#define LED_PIN 13

signed char lastpos = 0;
volatile int last_led = LOW;

// HALF_STEP or FULL_STEP  dependent of type of encoder (single or two impulse)
EncoderStepCounter encoder(ENCODER_PIN1, ENCODER_PIN2, HALF_STEP);


void setup() {
    Serial.begin(115200);
    encoder.begin();

    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

}


void loop() {
    encoder.tick();

    signed char pos = encoder.getPosition();
    if (pos != lastpos) {
        lastpos = pos;
        Serial.println(pos);
    }

    int switch_pos = digitalRead(SWITCH_PIN);
    if (switch_pos != last_led) {
        last_led = switch_pos;
        digitalWrite(LED_PIN, last_led);
    }

}
