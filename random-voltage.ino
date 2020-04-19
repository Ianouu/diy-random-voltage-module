
#define MIN_SPEED 255
#define MAX_SPEED 2000


int line1 = 3;
int line2 = 4;
int col1 = 5;
int col2 = 6;
int col3 = 7;
int col4 = 8;

int save1_pin = 11;
int save1_led = 12;
int save1_old = LOW;
int save1_value =1;

int speed_pin = A0;
int speed;

int MAX_VOLT_pin = A1;
int MAX_VOLT;

int MIN_VOLT_pin = A2;
int MIN_VOLT;

int output_volt_pin = 9;

int number_of_steps = 8;
int current_step = 1;

void (*stepsArr[])(void) = {
    step1,
    step2,
    step3,
    step4,
    step5,
    step6,
    step7,
    step8
};

void setup(){ 
	pinMode(line1, OUTPUT);
	pinMode(line2, OUTPUT);
	pinMode(col1, OUTPUT);
	pinMode(col2, OUTPUT);
	pinMode(col3, OUTPUT);
	pinMode(col4, OUTPUT);
	off();

    pinMode(save1_pin, INPUT);
    pinMode(save1_led, OUTPUT);
    digitalWrite(save1_pin, save1_old);

    randomSeed(analogRead(0));
    Serial.begin(9600);
}


void loop(){

    acquireSave1();
    acquireVoltParameter();
    randomVoltage();
    (*stepsArr[ current_step])();
    current_step = current_step +1;
    if ( current_step >= number_of_steps ) current_step = 0;
    delay(1000);
    
}

void acquireVoltParameter() {
    MIN_VOLT = map(analogRead(MIN_VOLT_pin), 0, 1023, 0, 255);
    MAX_VOLT = map(analogRead(MAX_VOLT_pin), 0, 1023, 0, 255);
}

void acquireSave1() {
    int newButtonState = digitalRead(save1_pin);
    if (newButtonState == HIGH && save1_old == LOW) {

        if (save1_value == 0) {
            digitalWrite(save1_led, HIGH);
            save1_value = 1;

        } else {
            digitalWrite(save1_led, LOW);
            save1_value = 0;
        }
    }

    // Store the button's state so we can tell if it's changed next time round
    save1_old = newButtonState;
}

void randomVoltage() {
    int randNumber = random(MIN_VOLT, MAX_VOLT);
    analogWrite(output_volt_pin, randNumber);
}

void readSpeed() {
    speed = map(analogRead(speed_pin), 0, 1023, MIN_SPEED, MAX_SPEED);
}


void off(){
	digitalWrite(line1, LOW);
	digitalWrite(line2, LOW);

	digitalWrite(col1, LOW);
	digitalWrite(col2, LOW);
	digitalWrite(col3, LOW);
	digitalWrite(col4, LOW);

	digitalWrite(save1_led, LOW);
}

void step1(){
	digitalWrite(line1, HIGH);
	digitalWrite(line2, LOW);

	digitalWrite(col1, HIGH);
	digitalWrite(col2, HIGH);
	digitalWrite(col3, HIGH);
	digitalWrite(col4, LOW);
}

void step2(){
	digitalWrite(line1, HIGH);
	digitalWrite(line2, LOW);

	digitalWrite(col1, HIGH);
	digitalWrite(col2, HIGH);
	digitalWrite(col3, LOW);
	digitalWrite(col4, HIGH);
}
void step3(){
	digitalWrite(line1, HIGH);
	digitalWrite(line2, LOW);

	digitalWrite(col1, HIGH);
	digitalWrite(col2, LOW);
	digitalWrite(col3, HIGH);
	digitalWrite(col4, HIGH);
}

void step4(){
	digitalWrite(line1, HIGH);
	digitalWrite(line2, LOW);

	digitalWrite(col1, LOW);
	digitalWrite(col2, HIGH);
    digitalWrite(col3, HIGH);
	digitalWrite(col4, HIGH);
}

void step5(){
	digitalWrite(line1, LOW);
	digitalWrite(line2, HIGH);

	digitalWrite(col1, HIGH);
	digitalWrite(col2, HIGH);
	digitalWrite(col3, HIGH);
	digitalWrite(col4, LOW);
}

void step6(){
	digitalWrite(line1, LOW);
	digitalWrite(line2, HIGH);

	digitalWrite(col1, HIGH);
	digitalWrite(col2, HIGH);
	digitalWrite(col3, LOW);
	digitalWrite(col4, HIGH);
}
void step7(){
	digitalWrite(line1, LOW);
	digitalWrite(line2, HIGH);

	digitalWrite(col1, HIGH);
	digitalWrite(col2, LOW);
	digitalWrite(col3, HIGH);
	digitalWrite(col4, HIGH);
}

void step8(){
	digitalWrite(line1, LOW);
	digitalWrite(line2, HIGH);

	digitalWrite(col1, LOW);
	digitalWrite(col2, HIGH);
    digitalWrite(col3, HIGH);
	digitalWrite(col4, HIGH);
}