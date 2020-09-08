int PinOut[4] {6, 5, 4, 3};
int PinIn[4] {10, 9, 8, 7};

const char value[4][4] {
    {'1', '4', '7', '*'},
    {'2', '5', '8', '0'},
    {'3', '6', '9', '#'},
    {'A', 'B', 'C', 'D'}
};

volatile unsigned int delayValue = 1000;
volatile bool ledOn = true;

void setup(){
    Serial.begin(115200);
    pinMode(13, OUTPUT);

    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    pinMode(7, INPUT_PULLUP);
    digitalWrite(7, HIGH);
    pinMode(8, INPUT_PULLUP);
    digitalWrite(8, HIGH);
    pinMode(9, INPUT_PULLUP);
    digitalWrite(9, HIGH);
    pinMode(10, INPUT_PULLUP);
    digitalWrite(10, HIGH);

    attachInterrupt(0, matrix, RISING);
}


void matrix(){
    for (int i = 1; i <= 4; i++) {
        digitalWrite(PinOut[i - 1], LOW);
        for (int j = 1; j <= 4; j++) {
            if (digitalRead(PinIn[j - 1]) == LOW) {
                char key =  value[i - 1][j - 1];
                Serial.println(key);

                switch (key) {
                    case ('A'): {
                        ledOn = true;
                        break;
                    };
                    case ('B'): {
                        ledOn = false;
                        break;
                    };
                    case ('C'): {
                        delayValue /= 2;
                        break;
                    };
                    case ('D'): {
                        delayValue *= 2;
                        break;
                    };

                    default:
                        break;
                }

                delay(175);
            }
        }
        digitalWrite(PinOut[i - 1], HIGH);
    }
}


void led(){
    if (ledOn){
        digitalWrite(13, HIGH);
        delay(delayValue);
        digitalWrite(13, LOW);
        delay(delayValue);
    }
}


void loop(){
  led();
}
