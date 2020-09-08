#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "LiquidCrystal.h"


Adafruit_BMP085 bmp180;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// #define DEBUG

#define PUMP_PIN 2

#ifdef DEBUG
#define POT_PIN A1
#endif

#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 3
#define BTN_RIGHT 4
#define BTN_SELECT 5
#define BTN_NONE 10

#define LOW_PRESSURE_LEVEL 320
#define HIGH_PRESSURE_LEVEL 370

unsigned int sec, halfCyclesCounter, lastCycleTimer = 0;

int pressure, max_pressure = 0;
int min_pressure = __INT_MAX__;

byte currentPumpState = LOW;
byte MENU_ACTIVE = 0;
byte previousButton = BTN_NONE;


void rotateMenu(byte button) {
    if (button == BTN_UP) {
        if (MENU_ACTIVE > 0) {
            MENU_ACTIVE--;
        }
    }
    else if (button == BTN_DOWN) {
        if (MENU_ACTIVE < 2) {
            MENU_ACTIVE++;
        }
    }
    else if (button == BTN_SELECT && MENU_ACTIVE == 1) {
        // reset min and max values
        max_pressure = 0;
        min_pressure = __INT_MAX__;
    }
}


byte getButtonPush(){
    int keyAnalog =  analogRead(A0);
    if (keyAnalog < 100) {
        return BTN_RIGHT;
    } else if (keyAnalog < 200) {
        return BTN_UP;
    } else if (keyAnalog < 400) {
        return BTN_DOWN;
    } else if (keyAnalog < 600) {
        return BTN_LEFT;
    } else if (keyAnalog < 800) {
        return BTN_SELECT;
    } else {
        return BTN_NONE;
    }
}


void findMinMax(){
    if (pressure > max_pressure) {
        max_pressure = pressure;
    }
    if (pressure < min_pressure) {
        min_pressure = pressure;
    }
}


void setup()
{
    Serial.begin(115200);
    lcd.begin(16, 2);

    pinMode(PUMP_PIN, OUTPUT);

    #ifdef DEBUG
    pinMode(POT_PIN, INPUT);
    #else
    if (!bmp180.begin()) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.println("Could not find a");
        lcd.setCursor(0, 1);
        lcd.println("valid BMP180");
        while (true) delay(100);
    }
    #endif
}


void readPressure(){
    #ifdef DEBUG
    int raw_value = analogRead(POT_PIN);
    pressure = int(map(raw_value, 0, 1023, LOW_PRESSURE_LEVEL - 20, 760));
    #else
    pressure = int(bmp180.readPressure() / 133.3224);
    #endif
}


void drawMenuCurrentPressure(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Seconds: ");
    lcd.print(sec);
    lcd.setCursor(0, 1);
    lcd.print("Pressure: ");
    lcd.print(pressure);
}


void drawMenuMinMaxPressure(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Min: ");
    lcd.print(min_pressure);
    lcd.setCursor(0, 1);
    lcd.print("Max: ");
    lcd.print(max_pressure);
}

void drawMenuCycles(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cycles: ");
    lcd.print(halfCyclesCounter / 2);
    lcd.setCursor(0, 1);
    lcd.print("Last ago:");
    lcd.print(lastCycleTimer);
}


void drawMenu(){
    if (MENU_ACTIVE == 0) {
        drawMenuCurrentPressure();
    } else if (MENU_ACTIVE == 1) {
        drawMenuMinMaxPressure();
    } else if (MENU_ACTIVE == 2) {
        drawMenuCycles();
    }
}


void processButtons(){
    byte currentButton = getButtonPush();
    if (currentButton == previousButton) return;

    rotateMenu(currentButton);

    previousButton = currentButton;
}


void processPump() {
    if (pressure > HIGH_PRESSURE_LEVEL) {
        digitalWrite(PUMP_PIN, HIGH);
        if (currentPumpState != HIGH) {
            halfCyclesCounter++;
            currentPumpState = HIGH;
        }
    }
    if (pressure < LOW_PRESSURE_LEVEL) {
        digitalWrite(PUMP_PIN, LOW);
        if (currentPumpState != LOW) {
            halfCyclesCounter++;
            currentPumpState = LOW;
            lastCycleTimer = -1;  // very next step is increment, but value must be zero
        }
    }
}


unsigned int LOOP_COUNTER = 0;

void loop()
{
    if (LOOP_COUNTER % 1000 == 0){
        readPressure();
        findMinMax();
        sec++;

        processPump();

        if (currentPumpState == LOW) {
            lastCycleTimer++;
        }
    }

    if (LOOP_COUNTER % 100 == 0){
        processButtons();
    }

    if (LOOP_COUNTER % 500 == 0) {
        drawMenu();
    }

    delay(1);

    if (LOOP_COUNTER == 10000) {
        LOOP_COUNTER = 0;
    }

    LOOP_COUNTER++;
}
