/*
Optical Sensor     Arduino
--------------------------
VCC (Red)          5V
Signal (Yellow)    Pin 7/8
GND (Blue)         GND
*/

// constant that won't change
#define MOSFET 6
const int sensorOne = 5; // left optical sensor, single
const int sensorTwo = 4; // right optical sensor
const int dryLED = 13; // onboard LED
const int slideSwitch = 3; // power switch
const int powerLED = 2; // power LED
const int errorLED = 8; // error LED

// variables that will change
int switchState = 0;

int sensorOneState = 0;
int sensorTwoState = 0;

// millis() stuff
unsigned long startMillis;
const unsigned long period = 80000; // period for time out (80 seconds)

bool enableMotor = true;

void setup() {
  //initialize INPUTS/OUTPUTS
  pinMode(slideSwitch, INPUT);
  pinMode(sensorOne, INPUT);
  pinMode(sensorTwo, INPUT);
  pinMode(dryLED, OUTPUT);
  pinMode(powerLED, OUTPUT);
  pinMode(MOSFET, OUTPUT);
  pinMode(errorLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read state of the switch
  switchState = digitalRead(slideSwitch);
  
  if (switchState == HIGH && enableMotor == true) {
    digitalWrite(powerLED, HIGH);
    sense();
  }
  if (switchState == HIGH && enableMotor == false) {
    digitalWrite(errorLED, HIGH);
  } else {
    digitalWrite(powerLED, LOW);
    digitalWrite(dryLED, LOW);
    digitalWrite(errorLED, LOW);
    digitalWrite(MOSFET, LOW);
  }
}

void sense() {
  do {
    // read state of sensor(s)
    sensorOneState = digitalRead(sensorOne);
    sensorTwoState = digitalRead(sensorTwo);
    Serial.println(sensorOneState, DEC);
    Serial.println(sensorTwoState, DEC);
    Serial.println("---------------");
    switchState = digitalRead(slideSwitch);
    delay(100);
  } while(switchState == HIGH && enableMotor == true && sensorOneState == LOW/* && sensorTwoState == LOW*/);
  
    startMillis = millis();
    digitalWrite(dryLED, HIGH);
    digitalWrite(MOSFET, HIGH);
    Serial.println("----- Motor: ON -----");

  do {
    // read state of both sensors again to see if state changes
    sensorOneState = digitalRead(sensorOne);
    sensorTwoState = digitalRead(sensorTwo);
    Serial.println(sensorOneState, DEC);
    Serial.println(sensorTwoState, DEC);
    Serial.println("---------------");
    switchState = digitalRead(slideSwitch);

    if (millis() - startMillis >= period) {
      Serial.println("----- Motor: OFF DUE TO TIME OUT -----");
      digitalWrite(errorLED, HIGH);
      digitalWrite(MOSFET, LOW);
      enableMotor = false;
    }
    
    delay(100);
  } while(switchState == HIGH && enableMotor == true && sensorOneState == HIGH/* || sensorTwoState == HIGH*/);
  
  digitalWrite(powerLED, LOW);
  digitalWrite(dryLED, LOW);
  digitalWrite(MOSFET, LOW);
  Serial.println("----- Motor: OFF -----");
  // delay(1000);
}
