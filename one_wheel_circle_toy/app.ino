#define BARRIER_RIGHT_PIN 3
#define BARRIER_LEFT_PIN 4
#define MOTOR_A_PIN 5
#define MOTOR_B_PIN 6

#define NONE 0
#define LEFT 1
#define RIGHT 2


void setup(){
    pinMode(BARRIER_RIGHT_PIN, INPUT);
    pinMode(BARRIER_LEFT_PIN, INPUT);

    pinMode(MOTOR_A_PIN, OUTPUT);
    pinMode(MOTOR_B_PIN, OUTPUT);

    Serial.begin(115200);
}


void _software_reset_wheel(){
    // software "reset" to solve problem with chaos with wheel
    digitalWrite(MOTOR_A_PIN, LOW);
    digitalWrite(MOTOR_B_PIN, LOW);
}


void move(byte direction){
    if (direction == LEFT) {
        _software_reset_wheel();

        // move left
        digitalWrite(MOTOR_A_PIN, HIGH);
        digitalWrite(MOTOR_B_PIN, LOW);
    } else if (direction == RIGHT) {
        _software_reset_wheel();

        // mode right
        digitalWrite(MOTOR_A_PIN, LOW);
        digitalWrite(MOTOR_B_PIN, HIGH);
    } else if (direction == NONE) {
        // stop all
        digitalWrite(MOTOR_A_PIN, LOW);
        digitalWrite(MOTOR_B_PIN, LOW);
    }
}

int c = 0;
byte m = NONE;
void loop(){
    int barrierRightAlert = digitalRead(BARRIER_RIGHT_PIN);
    int barrierLeftAlert = digitalRead(BARRIER_LEFT_PIN);

    if (barrierLeftAlert == HIGH && barrierRightAlert == HIGH) {
        move(NONE);
        m = NONE;
    } else if (barrierLeftAlert == LOW && barrierRightAlert == LOW) {
        move(NONE);
        m = NONE;
    } else if (barrierLeftAlert == HIGH) {
        move(RIGHT);
        m = RIGHT;
    } else if (barrierRightAlert == HIGH) {
        move(LEFT);
        m = LEFT;
    }

    delay(1);
    c++;

    if (c % 1000 == 0 ){
        Serial.print(barrierLeftAlert);
        Serial.print(" ");
        Serial.print(barrierRightAlert);
        Serial.print(" ");
        Serial.println(m);
    }
}
