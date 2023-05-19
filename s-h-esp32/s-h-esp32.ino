#include <Servo.h>    //door lock
#include <Keypad.h>   //door lock
#include <Stepper.h>  // Window and Garage

//door lock START
//door lock START




Servo myservo;        // door lock
#define ROW_NUM 4     // four rows// door lock
#define COLUMN_NUM 4  // four columns// door lock

char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};  // door lock

byte pin_rows[ROW_NUM] = { 12, 14, 27, 26 };       // door lock
byte pin_column[COLUMN_NUM] = { 25, 33, 32, 15 };  // door lock

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);  // door lock

const String open_password = "1010A";   // // door lock
const String close_password = "1010B";  // // door lock
String input_password;                  // door lock


int pos = 0;  // door lock
// int feature = 1;
int feature = 2;

//door lock END
//door lock END


//Garage START
const int stepsPerRevolution = 2038;
Stepper myStepper = Stepper(stepsPerRevolution, 21, 18, 19, 5);
//Garage END


void setup() {

  //door lock START

  myservo.attach(13);  // attaches the servo on pin 13 to the servo object
  Serial.begin(9600);
  input_password.reserve(32);
  //door lock END
}

void loop() {
    //door lock START
  //door lock START
if(feature==1){


  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = "";  // clear input password
    } else if (key == '#') {
      if (open_password == input_password) {
        Serial.println("The password is correct, ACCESS GRANTED!");
        // DO YOUR WORK HERE
        for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);  // tell servo to go to position in variable 'pos'
          delay(5);            // waits 15ms for the servo to reach the position
        }
      }
      if (close_password == input_password) {
        for (pos = 90; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
          myservo.write(pos);                 // tell servo to go to position in variable 'pos'
          delay(5);                           // waits 15ms for the servo to reach the position
        }
        feature = 2;
      }


      else {
        Serial.println("The password is incorrect, ACCESS DENIED!");
      }

      input_password = "";  // clear input password
    } else {
      input_password += key;  // append new character to input password string
    }
  }
  
}
  //door lock END
  //door lock END




  // Garage START
  // Garage START
  if(feature==2){

  // Rotate CW slowly at 5 RPM
  myStepper.setSpeed(15);
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // Rotate CCW quickly at 10 RPM
  myStepper.setSpeed(15);
  myStepper.step(-stepsPerRevolution);
  delay(1000);

  // feature = 1;
  }

  //Garage END
  //Garage END



}

//ESP32 Pin 13 for servo input door lock
//ESP32 Pin 12, 14, 27, 26, 25, 33, 32, 15 for 4x4
//ESP32 Pin 21, 19, 18, 5
