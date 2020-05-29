/*

Bits of segment (count of bit shift <<)

      7
    +----+
    |    |
  2 |  1 | 6
    +----+
    |    |
  3 |    | 5
    +----+
      4

shift 8 is dot
*/


#include "LedControl.h"

#define DN_PIN 4
#define CLK_PIN 3
#define CS_PIN 2

#define DEVICE_NUMBER 0

LedControl lc = LedControl(DN_PIN, CLK_PIN, CS_PIN, 1);
volatile int digit = 0;
volatile byte mask = 0b00000001;
volatile byte marker = 0;
volatile int marker_direction = +1;


void setup() {
  // The MAX72XX is in power-saving mode on startup, wakeup it
  lc.shutdown(DEVICE_NUMBER, false);
  // Set the brightness to a medium values
  lc.setIntensity(DEVICE_NUMBER, 7);
  // Always clear the display on startup
  lc.clearDisplay(DEVICE_NUMBER);

  Serial.begin(115200);
}


void runShiftsMasksByRow() {
    for (byte j = 0; j < 64; j++) {
      lc.clearDisplay(DEVICE_NUMBER);

      if (mask == 0b10000000) {
        mask = 0b00000001;
        if (digit == 7) {
            digit = 0;
        } else {
          digit++;
        }
      } else mask = mask << 1;

      lc.setRow(DEVICE_NUMBER, digit, mask);

      Serial.print(digit);
      Serial.print(" ");
      Serial.println(mask);

      delay(100);
    }
}

void runShiftsMasksByColumn() {
    for (byte j = 0; j < 64; j++) {
      lc.clearDisplay(DEVICE_NUMBER);

      if (mask == 0b10000000) {
        mask = 0b00000001;
        if (digit == 7) {
            digit = 0;
        } else {
          digit++;
        }
      } else mask = mask << 1;

      lc.setColumn(DEVICE_NUMBER, digit, mask);

      Serial.print(digit);
      Serial.print(" ");
      Serial.println(mask);

      delay(100);
    }
}


void runSlash(){
  lc.clearDisplay(DEVICE_NUMBER);
  for (byte j = 0; j < (8 * 4 - 1); j++) {
    for (byte b = 0; b < 8; b++) {
      if (b == 0) {
        if (marker == 0) {
          lc.setRow(DEVICE_NUMBER, 0, 0b01111001);
        } else {
          lc.setRow(DEVICE_NUMBER, 0, 0b01111000);
        }
      } else if (b == 7) {
        if (marker == 7) {
          lc.setRow(DEVICE_NUMBER, 7, 0b01001111);
        } else {
          lc.setRow(DEVICE_NUMBER, 7, 0b01001110);
        }
      } else if (marker == b) {
        lc.setRow(DEVICE_NUMBER, b, 0b01001001);
      } else {
        lc.setRow(DEVICE_NUMBER, b, 0b01001000);
      }
    }

    if (marker == 0) marker_direction = +1;
    if (marker == 7) marker_direction = -1;
    marker += marker_direction;

    Serial.print(marker);
    Serial.print(" ");
    Serial.println(marker_direction);

    delay(250);
  }
}

void setOp(char op){
  lc.clearDisplay(DEVICE_NUMBER);

  lc.setChar(DEVICE_NUMBER, 3, '0', false);
  lc.setChar(DEVICE_NUMBER, 2, 'P', false);
  lc.setChar(DEVICE_NUMBER, 0, op, false);

  delay(2000);
}

void setShifts(){
  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '1', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b00000001);
  delay(2000);

  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '2', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b00000010);
  delay(2000);

  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '3', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b00000100);
  delay(2000);

  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '4', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b00001000);
  delay(2000);

  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '5', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b00010000);
  delay(2000);

  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '6', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b00100000);
  delay(2000);

  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '7', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b01000000);
  delay(2000);

  lc.clearDisplay(DEVICE_NUMBER);
  lc.setChar(DEVICE_NUMBER, 1, '8', false);
  lc.setRow(DEVICE_NUMBER, 0, 0b10000000);
  delay(2000);
}


void loop() {
  setOp('1');
  runShiftsMasksByRow();

  setOp('2');
  runShiftsMasksByColumn();

  setOp('3');
  runSlash();

  // setShifts();
}
