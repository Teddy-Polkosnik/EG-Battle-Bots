
// Created by Teddy Polkosnik

#include <esp_now.h>
#include <WiFi.h>

// MOTOR 1 Pins
int motor1Pin1 = 27; // in1 = pin 27
int motor1Pin2 = 26; // in2 = pin 26
int enable1Pin = 14; // ena = pin 14

const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 255; // sets pwm cycle


// Structure example to receive data
// Must match the sender structure****
typedef struct struct_message {
  int rightJoyXvalue;
  int rightJoyYvalue;
  int rightJoySWvalue;
  int leftJoyXvalue;
  int leftJoyYvalue;
  int leftJoySWvalue;
} struct_message;

int moveForward;
int moveBackward;
int rotateLeft;
int rotateRight;
int moveSidewaysRight;
int moveSidewaysLeft;

// Create a struct_message called myData
struct_message readingData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&readingData, incomingData, sizeof(readingData));
  Serial.print("Bytes received: ");
  Serial.println(len);

  // Testing the right joystick values
  // Serial.print("Right Joystick X Value: ");
  // Serial.println(readingData.rightJoyXvalue);
  // Serial.print("Right Joystick Y Value: ");
  // Serial.println(readingData.rightJoyYvalue);
  // Serial.print("Right Switch Value: ");
  // Serial.println(readingData.rightJoySWvalue);
  // Serial.println();



//Right Joystick Forward/Backward/Left/Right
if (readingData.rightJoyXvalue > 2000){
  Serial.print(readingData.rightJoyXvalue);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  ledcWrite(enable1Pin, dutyCycle);
  Serial.println("Forward");
  delay(20);
}

if (readingData.rightJoyXvalue < 1000){
  Serial.print(readingData.rightJoyXvalue);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  ledcWrite(enable1Pin, dutyCycle);
  Serial.println("Backward");
}

if (readingData.rightJoyYvalue > 2000){
  Serial.print(readingData.rightJoyXvalue);
  Serial.println("Right");
}

if (readingData.rightJoyYvalue < 1000){
  Serial.print(readingData.rightJoyXvalue);
  Serial.println("Left");
}


  // Testing the left joystick values
  // Serial.print("Left Joystick X Value: ");
  // Serial.println(readingData.leftJoyXvalue);
  // Serial.print("left Joystick Y Value: ");
  // Serial.println(readingData.leftJoyYvalue);
  // Serial.print("Left Switch Value: ");
  // Serial.println(readingData.leftJoySWvalue);
  // Serial.println();


// // Left Joystick Forward/Backward/Left/Right
// if (readingData.leftJoyXvalue > 2000){
//   Serial.println("Forward");
// }

// if (readingData.leftJoyXvalue < 1000){
//   Serial.println("Backward");
// }

// if (readingData.leftJoyYvalue > 2000){
//   Serial.println("Right");
// }

// if (readingData.leftJoyYvalue < 1000){
//   Serial.println("Left");

// }
  // moveForward = readingData.rightJoyXvalue;
  // Serial.print("Right Joystick X Value: ");
  // Serial.println(readingData.rightJoyXvalue);
  // Serial.println();
  // Serial.println(readingData.rightJoySWvalue);
  // Serial.println();
  // digitalWrite(RightFrontFWD, moveForward);
  // digitalWrite(RightBackFWD, moveForward);
  // digitalWrite(LeftFrontFWD, moveForward);
  // digitalWrite(LeftBackFWD, moveForward);

  // moveBackward = readingData.leftJoyXvalue;
  // Serial.print("Left Joystick X Value: ");
  // Serial.println(readingData.leftJoyXvalue);
  // Serial.println();
  // digitalWrite(RightFrontBWD, moveBackward);
  // digitalWrite(RightBackBWD, moveBackward);
  // digitalWrite(LeftFrontBWD, moveBackward);
  // digitalWrite(LeftBackBWD, moveBackward);

  // rotateLeft = readingData.leftJoyYvalue;
  // Serial.print("Left Joystick Y Value: ");
  // Serial.println(readingData.leftJoyYvalue);
  // Serial.println();
  // digitalWrite(RightFrontFWD, rotateLeft);
  // digitalWrite(RightBackFWD, rotateLeft);
  // digitalWrite(LeftFrontBWD, rotateLeft);
  // digitalWrite(LeftBackBWD, rotateLeft);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Motors are Output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // configures the LEDC PWM
  ledcAttachChannel(enable1Pin, freq, resolution, pwmChannel);

  // pinMode(RightFrontFWD, OUTPUT);
  // pinMode(RightBackFWD, OUTPUT);
  // pinMode(RightBackBWD, OUTPUT);
  // pinMode(LeftFrontFWD, OUTPUT);
  // pinMode(LeftFrontBWD, OUTPUT);
  // pinMode(LeftBackFWD, OUTPUT);
  // pinMode(LeftBackBWD, OUTPUT);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {



 

}