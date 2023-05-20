#include <Servo.h>    //door lock
#include <Stepper.h>  // Window and Garage
#include <NewPing.h>  //ultrasonic sensor
#define RXp2 16
#define TXp2 17
#define flameSensor 33
#define TRIGGER_PIN_Front 4
#define ECHO_PIN_Front 35
#define TRIGGER_PIN_Back 22
#define ECHO_PIN_Back 34
#define TRIGGER_PIN_Left 23
#define ECHO_PIN_Left 39
#define TRIGGER_PIN_Right 25
#define ECHO_PIN_Right 36
#define MAX_DISTANCE 400



//sonar START
NewPing sonarFront(TRIGGER_PIN_Front, ECHO_PIN_Front, MAX_DISTANCE);
NewPing sonarBack(TRIGGER_PIN_Back, ECHO_PIN_Back, MAX_DISTANCE);
NewPing sonarLeft(TRIGGER_PIN_Left, ECHO_PIN_Left, MAX_DISTANCE);
NewPing sonarRight(TRIGGER_PIN_Right, ECHO_PIN_Right, MAX_DISTANCE);
//sonar END

void buzzer(int x) {
  digitalWrite(2, x);
}

//door lock START
String a;
String o = "o";
String c = "c";
Servo myservo;
int pos = 0;
//door lock END
//flame sensor START

//flame sensor END

//Garage START
const int stepsPerRevolution = 2038;
Stepper garageStepper = Stepper(stepsPerRevolution, 21, 18, 19, 5);
//Garage END

//Window START
Stepper windowStepper = Stepper(stepsPerRevolution, 12, 27, 14, 26);
//Window END
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
int feature = 5;
void setup() {

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  pinMode(2, OUTPUT);


  //flame sensor START
  pinMode(flameSensor, INPUT);
  //flame sensor END

  //door lock START

  myservo.attach(13);  // attaches the servo on pin 13 to the servo object

  //door lock END
}

void loop() {






  //door lock START
  //door lock START
  if (feature == 1) {
    a = Serial2.readString();
    Serial.println(a);


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

  //flame sensor START
  //flame sensor START
  if (feature == 4) {
    int fire = digitalRead(flameSensor);
    if (fire == 0) {
      Serial.println("fire");
      buzzer(1);
    }
    if (fire == 1) {
      Serial.println("No fire");
      buzzer(0);
    }
  }
  //flame sensor END
  //flame sensor END
  //sonar START
  //sonar START
  if (feature == 5) {



    // Serial.print("Front = ");
    // Serial.print(sonarFront.ping_cm());
    // Serial.println(" cm");
    int front = sonarFront.ping_cm();
    int back = sonarBack.ping_cm();
    int left = sonarLeft.ping_cm();
    int right = sonarRight.ping_cm();

    Serial.println(front);
    Serial.println(back);
    Serial.println(left);
    Serial.println(right);

    Serial.println("| |");
    Serial.println("| |");
    Serial.println("| |");

    delay(500);
  }

  //sonar END
  //sonar END
}

//ESP32 Pin 13 for servo input door lock
//ESP32 Pin 21, 19, 18, 5 for garage stepper
//ESP32 Pin 12, 14, 27, 26 for windows stepper
//ESP32 Pin 15 to 33 Flame Sensor
//ESP32 Pin 2  Buzzer
//ESP32 Pin 4,35  22,34  23,39  25,36  front , back , left , right
//ESP32 Pin 16 , 17 Arduino comm