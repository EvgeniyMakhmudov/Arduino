/*
Two examples of using buzzer;
First it with external library, witch no so good for real use
Second very simple
*/

#include "EasyBuzzer.h"

#define BUZZER_1_PIN 10
#define BUZZER_2_PIN 4  // really not worked, because set in Config.h
#define POT_PIN A0

void setup() {
	Serial.begin(115200);
    pinMode(BUZZER_1_PIN, OUTPUT);
    pinMode(POT_PIN, INPUT);
}

int counter = 0;

void loop() {
    /*
    Example 1
    Try to make single short beep in per second
    */
    // if (counter >= 1000) {
    //     int value = analogRead(POT_PIN);
    //     int freq = map(value,0, 1023, 50, 5000);
    //     EasyBuzzer.singleBeep(freq, 250);
    //     counter = 0;
    // } else {
    //     counter++;
    // }

    // EasyBuzzer.update();
    // delay(1);


    /*
    Example 2
    It is a very basic metod - just use PWM of Arduino digital output
    */
    int value = analogRead(POT_PIN);

    analogWrite(BUZZER_1_PIN, value);
    delay(1000);

    analogWrite(BUZZER_1_PIN, LOW);
    delay(1000);


}
