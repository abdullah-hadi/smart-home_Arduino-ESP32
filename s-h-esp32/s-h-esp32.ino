#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
// #include <BlynkSimpleEsp32.h>
#include <Servo.h>    //door lock
#include <Stepper.h>  // Window and Garage
#include <NewPing.h>  //ultrasonic sensor
// #define BLYNK_TEMPLATE_ID "TMPL6Wl7Ap02Q"
// #define BLYNK_TEMPLATE_NAME "Quickstart Device"
// #define BLYNK_AUTH_TOKEN "Oly45LaZz6fkgBHSQhhzn5-Gf4U0-W44"
// #define BLYNK_PRINT Serial
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

int antiTheft = 0;
int smartWindow = 0;
//Blynk Start

// BLYNK_WRITE(V0) {
//   antiTheft = param.asInt();
//   Serial.print("antiTheft = ");
//   Serial.println(antiTheft);
// }
// BLYNK_WRITE(V1) {
//   smartWindow = param.asInt();
//   Serial.print("smartWindow = ");
//   Serial.println(smartWindow);
// }


//Blynk Stop




//callme START


String phoneNumber = "+8801761377885";
String apiKey = "4336380";

void sendMessage(String message) {

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Message sent successfully");
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}


//callme END

const char* ssid = "GALAXY A55";
const char* password = "suffixes";

// BlynkTimer timer;



// // This function is called every time the device is connected to the Blynk.Cloud
// BLYNK_CONNECTED() {
//   // Change Web Link Button message to "Congratulations!"
//   Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
//   Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
//   Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
// }







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
  WiFi.begin(ssid, password);
  Serial.println(WiFi.localIP());


  //flame sensor START
  pinMode(flameSensor, INPUT);
  //flame sensor END

  //door lock START

  // attaches the servo on pin 13 to the servo object

  //door lock END
  // Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  myservo.attach(13);



  // sendMessage("Hello from ESP32!");
}

void loop() {
  // a = Serial2.readString();
  // Serial.println(a);
  // Blynk.run();
  // timer.run();






  //door lock START
  //door lock START
  if (feature == 1) {
    a = Serial2.readString();
    Serial.println(a);


    if (a == o || smartWindow == 1) {


      for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(5);
        // waits 15ms for the servo to reach the position
      }
    }
    if (a == c || smartWindow == 0) {
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
  // if (feature == 2) {

  //   // Rotate CW slowly at 5 RPM
  //   garageStepper.setSpeed(15);
  //   garageStepper.step(stepsPerRevolution);
  //   delay(1000);

  //   // Rotate CCW quickly at 10 RPM
  //   garageStepper.setSpeed(15);
  //   garageStepper.step(-stepsPerRevolution);
  //   delay(1000);

  //   feature = 3;
  // }

  //Garage END
  //Garage END

  //Window START
  //Window START
  if (feature == 3) {

    // Rotate CW slowly at 5 RPM
    windowStepper.setSpeed(15);
    garageStepper.setSpeed(15);

    windowStepper.step(stepsPerRevolution);
    garageStepper.step(stepsPerRevolution);
    delay(1000);

    // Rotate CCW quickly at 10 RPM
    windowStepper.setSpeed(15);
    garageStepper.setSpeed(15);
    windowStepper.step(-stepsPerRevolution);
    garageStepper.step(-stepsPerRevolution);
    delay(1000);
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
      sendMessage("🚨Fire Alert🔥");
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
    if (front < 15 && front != 0) {
      sendMessage("Alert! Intruder at front door🚨");
      buzzer(1);
    }
    // if (front >= 15) {
    //   buzzer(0);
    // }
    Serial.println(back);
    if (back < 15 && back != 0) {
      sendMessage("Alert! Intruder is behind garage🚨");
      buzzer(1);
    }
    // if (back >= 15) {
    //   buzzer(0);
    // }


    Serial.println(left);
    if (left < 15 && left != 0) {
      sendMessage("Alert! Intruder is in the driveway🚨");
      buzzer(1);
    }
    // if (left >= 15) {
    //   buzzer(0);
    // }

    Serial.println(right);
    if (right < 15 && right != 0) {
      sendMessage("Alert! Intruder is beside the kitchen window🚨");
      buzzer(1);
    }
    // if (right >= 15) {
    //   buzzer(0);
    // }

    Serial.println("| |");
    Serial.println("| |");
    Serial.println("| |");

    delay(100);
    buzzer(0);
  }

  //sonar END
  //sonar END
}

//ESP32 Pin 13 for servo input window
//ESP32 Pin 21, 19, 18, 5 for garage stepper
//ESP32 Pin 12, 14, 27, 26 for windows stepper
//ESP32 Pin 15 to 33 Flame Sensor
//ESP32 Pin 2  Buzzer
//ESP32 Pin 4,35  22,34  23,39  25,36  front , back , left , right
//ESP32 Pin 16 , 17 Arduino comm