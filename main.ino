// Include the Libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Wifi Credentials
const char* ssid = "Your Wifi SSID";
const char* password =  "Your Wifi Password";

// Teleclaw Login
const char* apiUsername = "Please Contact Teleclaw";
const char* apiPassword =  "Please Contact Teleclaw";

// Variables and Tokens
String userToken;
String userId;
String appId;
String did;
String token;

// Define Pin
const int blinkPin = 16;
const int switchPin = 32;
const int button1Pin = 25;
const int xPin = 33;
const int yPin = 34;

// Define Pin Readings
int buttonState;
int button1State;
int xVal;
int yVal;

void setup() {
  pinMode(blinkPin,switchPin,xPin,yPin,button1Pin);
  Serial.begin(115200);
  wifi();
  if(WiFi.status() == WL_CONNECTED){
    login();
  }
}

void loop() {
  // Readings from the Pin
  buttonState = digitalRead(switchPin);
  button1State = digitalRead(button1Pin);
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);

  if(WiFi.status() == WL_CONNECTED){
    switchState(buttonState);
    joyStickControl(xVal,yVal);
    catchGift(button1State);
  }
} 
