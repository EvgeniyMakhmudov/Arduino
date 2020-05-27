/*
Use 3 potentiometrers to control intensetive of each part pf RGB led
*/

#define RED_LED_PIN 3
#define BLUE_LED_PIN 5
#define GREEN_LED_PIN 6
#define BLUE_LEVEL_PIN A0
#define RED_LEVEL_PIN A1
#define GREEN_LEVEL_PIN A2
#define MAX_LED_LEVEL 75

void setup(){
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
}


void loop(){
    int blue_value = analogRead(BLUE_LEVEL_PIN);
    int blue_led_value = map(blue_value, 0, 1023, MAX_LED_LEVEL, 0);
    int red_value = analogRead(RED_LEVEL_PIN);
    int red_led_value = map(red_value, 0, 1023, MAX_LED_LEVEL, 0);
    int green_value = analogRead(GREEN_LEVEL_PIN);
    int green_led_value = map(green_value, 0, 1023, MAX_LED_LEVEL, 0);

    analogWrite(BLUE_LED_PIN, blue_led_value);
    analogWrite(RED_LED_PIN, red_led_value);
    analogWrite(GREEN_LED_PIN, green_led_value);

    delay(10);
}
