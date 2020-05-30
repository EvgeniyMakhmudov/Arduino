/*
Simply use LCD for print values of analog input from
potentiometrer between Vcc and GND.
*/

#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
    lcd.begin(16,2);

    pinMode(A0, INPUT);
    Serial.begin(115200);
}

char bufferFirstLine [16];
char bufferSecondLine [16];

void loop()
{
    lcd.clear();

    int value = analogRead(A0);
    int mVolts = map(value, 0, 1023, 0, 5000);

    sprintf(bufferFirstLine, "Values: %d", value);
    lcd.write(bufferFirstLine);

    lcd.setCursor(0, 1);
    sprintf(bufferSecondLine, "mV: %d", mVolts);
    lcd.write(bufferSecondLine);

    delay(100);
}
