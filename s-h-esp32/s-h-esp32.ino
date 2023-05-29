#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
#include <Servo.h>  
#include <Stepper.h> 
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

int antiTheft = 0;
int smartWindow = 0;

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

const char* ssid = "Galaxy A55";
const char* password = "suffixes";

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
Servo doorServo;
Servo windowServo;
int pos = 0;
int stepDelay = 1;
//door lock END

//Garage START
//const int stepsPerRevolution = 2038;
//Stepper garageStepper = Stepper(stepsPerRevolution, 21, 18, 19, 5);
//Garage END

//Window START
//Stepper windowStepper = Stepper(stepsPerRevolution, 12, 27, 14, 26);
//Window END
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
int feature = 1;
void setup() {

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println(WiFi.localIP());
  
  //flame sensor START
  pinMode(flameSensor, INPUT);
  //flame sensor END
  
  //laser sensor START
  pinMode(14, OUTPUT);
  pinMode(12, INPUT);
  //laser sensor END
  doorServo.attach(32);
  windowServo.attach(13);
  // sendMessage("Initiated");
}

void loop() {
  //door and Window START
  //door and Window START
  if (feature == 1) {
    a = Serial2.readString();
    Serial.println(a);
    
    if (a == "o")
      for (int pos = 1000; pos <= 2000; pos += 5) {
        doorServo.writeMicroseconds(pos);
        delay(stepDelay);
      }
    if (a == "w")
      for (int pos = 900; pos <= 2000; pos += 5) {
        windowServo.writeMicroseconds(pos);
        delay(stepDelay);
      }
    if (a == "c")
      for (int pos = 2000; pos >= 1000; pos -= 2) {
        doorServo.writeMicroseconds(pos);
        delay(stepDelay);
      }
    if (a == "x")
      for (int pos = 2000; pos >= 900; pos -= 2) {
        windowServo.writeMicroseconds(pos);
        delay(stepDelay);
      }
  }
  //door and Window END
  //door and Window END
 
  //Laser Receiver Start
  //Laser Receiver Start
  if (feature == 1) {
    digitalWrite(14,1);
    
    if (digitalRead(12) == 1) {
      buzzer(1);
      sendMessage("Car Stolen");
    } else {
      buzzer(0);
    }
  }
  //Laser Receiver END
  //Laser Receiver END

  //flame sensor START
  //flame sensor START

  if (feature == 1) {
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
  if (feature == 1) {

    int front = sonarFront.ping_cm();
    int back = sonarBack.ping_cm();
    int left = sonarLeft.ping_cm();
    int right = sonarRight.ping_cm();

    Serial.println(front);
    if (front < 15 && front != 0) {
      sendMessage("Alert! Intruder at front door🚨");
      buzzer(1);
    }

    Serial.println(back);
    if (back < 15 && back != 0) {
      sendMessage("Alert! Intruder is behind garage🚨");
      buzzer(1);
    }
    
    Serial.println(left);
    if (left < 15 && left != 0) {
      sendMessage("Alert! Intruder is in the driveway🚨");
      buzzer(1);
    }
    
    Serial.println(right);
    if (right < 15 && right != 0) {
      sendMessage("Alert! Intruder is beside the kitchen window🚨");
      buzzer(1);
    }
    
    Serial.println("| |");
    Serial.println("| |");
    Serial.println("| |");
    delay(100);
    buzzer(0);
  }

  //sonar END
  //sonar END
}

//ESP32 Pin 13 for servo door
//ESP32 Pin 32 for servo window
//ESP32 Pin 21, 19, 18, 5 for garage stepper
//ESP32 Pin 14, 27, 26 for windows stepper
//ESP32 Pin 15 to 33 Flame Sensor
//ESP32 Pin 2  Buzzer
//ESP32 Pin 4,35  22,34  23,39  25,36  front , back , left , right
//ESP32 Pin 16 , 17 Arduino comm
//ESP32 Pin 12 Laser Receiver
