#include <Keypad.h>  //door lock


#define ROW_NUM 4     // four rows// door lock
#define COLUMN_NUM 4  // four columns// door lock

char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};  // door lock

byte pin_rows[ROW_NUM] = { 13, 12, 11, 10 };   // door lock
byte pin_column[COLUMN_NUM] = { 9, 8, 7, 6 };  // door lock

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);  // door lock

const String open_password = "1010A";   // // door lock
const String close_password = "1010B";  // // door lock
String input_password;                  // door lock

void setup() {
  Serial.begin(9600);
  
  input_password.reserve(32);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    //ARDIO COMM
  

  //ARDIO COMM
  //door lock START
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

//Arduino Pin 13,12,11,10,9,8,7,6 for 4x4
//Arduino Pin 1,0 for ESP-32 comm
