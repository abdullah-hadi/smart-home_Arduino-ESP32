#include <Servo.h>    //door lock
#include <Stepper.h>  // Window and Garage

#define RXp2 16
#define TXp2 17

//door lock START
//door lock START

String a;
String o = "o";
String c = "c";


Servo myservo;  // door lock



int pos = 0;  // door lock
// int feature = 1;
int feature = 2;

//door lock END
//door lock END


//Garage START
const int stepsPerRevolution = 2038;
Stepper garageStepper = Stepper(stepsPerRevolution, 21, 18, 19, 5);
//Garage END

//Window START
Stepper windowStepper = Stepper(stepsPerRevolution, 21, 18, 19, 5);

//Window END


void setup() {

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  //door lock START

  myservo.attach(13);  // attaches the servo on pin 13 to the servo object

  //door lock END
}

void loop() {




  a = Serial2.readString();
  Serial.println(a);
  
  //door lock START
  //door lock START
  if (feature == 1) {


    if (a == o) {
      

      for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(5);
         // waits 15ms for the servo to reach the position
       
      }
    }
    if (a == c) {
      for (pos = 90; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
        myservo.write(pos);                 // tell servo to go to position in variable 'pos'
        delay(5);
         // waits 15ms for the servo to reach the position
      }
    }
  }
  //door lock END
  //door lock END




  // Garage START
  // Garage START
  if (feature == 2) {

    // Rotate CW slowly at 5 RPM
    garageStepper.setSpeed(15);
    garageStepper.step(stepsPerRevolution);
    delay(1000);

    // Rotate CCW quickly at 10 RPM
    garageStepper.setSpeed(15);
    garageStepper.step(-stepsPerRevolution);
    delay(1000);

    feature = 3;
  }

  //Garage END
  //Garage END

  //Window START 
  //Window START
  if (feature == 3) {

    // Rotate CW slowly at 5 RPM
    windowStepper.setSpeed(15);
    windowStepper.step(stepsPerRevolution);
    delay(1000);

    // Rotate CCW quickly at 10 RPM
    windowStepper.setSpeed(15);
    windowStepper.step(-stepsPerRevolution);
    delay(1000);

    feature = 2;
  }


  //Window END
  //Window END
}

//ESP32 Pin 13 for servo input door lock
//ESP32 Pin 21, 19, 18, 5
