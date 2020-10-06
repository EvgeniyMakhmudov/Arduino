#include "LedControl.h"
#include "chars.h"

#define DN_PIN 4
#define CLK_PIN 3
#define CS_PIN 2

// #define DEVICE_NUMBER 0

LedControl lc = LedControl(DN_PIN, CLK_PIN, CS_PIN, 4);


struct Coordinates {
    int device;
    int col;
    int row;
};


byte mirror(byte b){
    byte r = 0;
    for (byte i = 0; i < 8; i++) {
        byte orig_byte = ((1 << i) & b) >> i;
        byte mirror_byte = orig_byte << (7 - i);
        r = r | mirror_byte;
    }
    return r;
}


Coordinates getCoordinates(int col, int row) {
    int deviceNumber = (col - 1) / 8;
    int diff = col - deviceNumber * 8;
    int r_col = abs(diff - 8) ;
    // int r_row = abs(row - 8) - 1;
    int r_row = row - 1;
    Coordinates result {deviceNumber, r_col, r_row};
    return result;
}


void setColumn(LedControl &lc, int col, byte value) {
    int deviceNumber = (col - 1) / 8;
    int diff = col - deviceNumber * 8;
    int r_col = abs(diff - 8);
    lc.setColumn(deviceNumber, r_col, value);
}


void setPixel(LedControl &lc, int col, int row, bool state) {
    Coordinates cood = getCoordinates(col, row);
    lc.setLed(cood.device, cood.row, cood.col, true);
}


void setPixelOn(LedControl &lc, int col, int row) {
    setPixel(lc, col, row, true);
}


void setPixelOff(LedControl &lc, int col, int row) {
    setPixel(lc, col, row, false);
}



void setChar(LedControl &lc, int col, char value){
    byte *ptr_values;

    switch (value) {
        case '0':
            ptr_values = CHAR_0; break;
        case '1':
            ptr_values = CHAR_1; break;
        case '2':
            ptr_values = CHAR_2; break;
        case '3':
            ptr_values = CHAR_3; break;
        case '4':
            ptr_values = CHAR_4; break;
        case '5':
            ptr_values = CHAR_5; break;
        case '6':
            ptr_values = CHAR_6; break;
        case '7':
            ptr_values = CHAR_7; break;
        case '8':
            ptr_values = CHAR_8; break;
        case '9':
            ptr_values = CHAR_9; break;
        case '+':
            ptr_values = CHAR_PLUS; break;
        case '-':
            ptr_values = CHAR_MINUS; break;
        default:
            break;
    }

    for (byte b=0; b<8; b++) {
        int deviceNumber = (col + b - 1) / 8;
        int diff = col + b - deviceNumber * 8;
        int r_col = abs(diff - 8);

        lc.setColumn(deviceNumber, r_col, *(ptr_values + b));
    }
}


void setString(LedControl &lc, char *str) {
    for (byte b=0; b<4; b++) {
        setChar(lc, 8 * b + 1, *(str + b));
    }
}

void setup() {
    Serial.begin(115200);
    Serial.print("Devices count: ");
    Serial.println(lc.getDeviceCount());

    for (int deviceNumber=0; deviceNumber < lc.getDeviceCount(); deviceNumber++) {
        // The MAX72XX is in power-saving mode on startup, wakeup it
        lc.shutdown(deviceNumber, false);
        // Set the brightness to a medium values
        lc.setIntensity(deviceNumber, 1);
        // Always clear the display on startup
        lc.clearDisplay(deviceNumber);
    }

}


void loop()
{
    for (int deviceNumber=0; deviceNumber < lc.getDeviceCount(); deviceNumber++) {
        lc.clearDisplay(deviceNumber);
    }
    // setChar(lc, 1, '2');
    // setChar(lc, 9, '-');
    // setChar(lc, 17, '1');
    // setChar(lc, 17+8, '+');
    setString(lc, "01234");
    delay(1000);
}
