#include <Keypad.h> 
#define ROW_NUM 4     // door lock
#define COLUMN_NUM 4  // door lock

int UVOUT = A0;       
int REF_3V3 = A1;     

int averageAnalogRead(int pinToRead) {
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;
  for (int x = 0; x < numberOfReadings; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return (runningValue);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};  // door lock

byte pin_rows[ROW_NUM] = { 5, 6, 7, 8 };   // door lock
byte pin_column[COLUMN_NUM] = { 9, 10, 11, 12 };  // door lock
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);  // door lock
const String open_password = "1010A";   // // door lock
const String close_password = "1010B";  // // door lock
String input_password;                  // door lock

int feat = 0;
int window = 0;
void setup() {
  Serial.begin(9600);
  input_password.reserve(32);
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
}

void loop() {

  if (feat == 0) {

    int uvLevel = averageAnalogRead(UVOUT);
    int refLevel = averageAnalogRead(REF_3V3);
    float outputVoltage = 3.3 / refLevel * uvLevel;
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);  //Convert the voltage to a UV intensity level
    int fv = 100 * uvIntensity;
    
    // Serial.println(uvIntensity);
    if (uvIntensity > 0 && window == 1 ) {
      Serial.print("w");
      window = 0;
       delay(1000);
    }
    if (uvIntensity < 0 && window ==0 ) {
      Serial.print("x");
      window = 1;
      delay(1000);
    }
  }

  if (feat == 0) {
    //door lock START
    
    char key = keypad.getKey();

    if (key) { 
      if (key == '*') {
        input_password = "";  // clear input password
      } else if (key == '#') {
        if (open_password == input_password) {
          Serial.print("o");
        }
        if (close_password == input_password) {
          Serial.print("c");
        }
        else {
        }
        input_password = "";  // clear input password
      } else {
        input_password += key;  // append new character to input password string
      }
    }
  }
}
//Arduino Pin 13,12,11,10,9,8,7,6 for 4x4
//Arduino Pin 1,0 for ESP-32 comm
