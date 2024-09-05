#include <esp_now.h>
#include <WiFi.h>

// right Joy Stick
#define rightJoyX     32
#define rightJoyY     35
#define rightJoySW    12

// left Joy Stick
// [Delete if only using 1 Joystick]
// #define leftJoyX     26
// #define leftJoyY     27
// #define leftJoySW    25


int rightJoyXstate;
int rightJoyYstate;
int rightJoySWstate;

// int leftJoyXstate;
// int leftJoyYstate;
// int leftJoySWstate;


// REPLACE WITH YOUR RECEIVER MAC Address
// If the address in lowercase change it to uppercase!!!
uint8_t broadcastAddress[] = {0xA8, 0x42, 0xE3, 0xC8, 0x2d, 0x84};




// Structure example to send data
// Must match the receiver structure****
typedef struct struct_message {
  // defines the data type you are sending
  // Right Data
  int rightJoyXvalue;
  int rightJoyYvalue;
  int rightJoySWvalue;

  // Left Data 
  // [Delete if only using 1 Joystick]
  // int leftJoyXvalue;
  // int leftJoyYvalue;
  // int leftJoySWvalue;


} struct_message;



// Create a struct_message called myData
struct_message handControllerData;

// Don't ask me idk what this is 
esp_now_peer_info_t peerInfo;



// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Right Joystick Configuration
  pinMode(rightJoyX, INPUT);
  pinMode(rightJoyY, INPUT);
  pinMode(rightJoySW, INPUT);

  // Left Joystick Configuration
  // [Delete if only using 1 Joystick]
  // pinMode(leftJoyX, INPUT);
  // pinMode(leftJoyY, INPUT);
  // pinMode(leftJoySW, INPUT);



  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);



  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }



  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);



  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;


  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send

  // Right Data Send
  rightJoyXstate = analogRead(rightJoyX);
  handControllerData.rightJoyXvalue = rightJoyXstate;
  rightJoyYstate = analogRead(rightJoyY);
  handControllerData.rightJoyYvalue = rightJoyYstate;
  rightJoySWstate = digitalRead(rightJoySW);
  handControllerData.rightJoySWvalue = rightJoySWstate;

  // Left Data Send
  // [Delete if only using 1 Joystick]
  // leftJoyXstate = analogRead(leftJoyX);
  // handControllerData.leftJoyXvalue = leftJoyXstate;
  // leftJoyYstate = analogRead(leftJoyY);
  // handControllerData.leftJoyYvalue = leftJoyYstate;
  // leftJoySWstate = digitalRead(leftJoySW);
  // handControllerData.leftJoySWvalue = leftJoySWstate;
  


  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &handControllerData, sizeof(handControllerData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(50);
}
