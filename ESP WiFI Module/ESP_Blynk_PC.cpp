
/*New blynk app project
   Blynk Verision 1.0.1
   Home Page
*/

//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_AUTH_TOKEN "TumtYWqT-qkP8UykAQLaXfCMAHD7Fr2o" //Enter your blynk auth token
//V0 Forward
//V1 Backward
//V2 Left
//V3 Right

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SMVDU.";//Enter your WIFI name
char pass[] = "123456789";//Enter your WIFI password

//Get the button value
BLYNK_WRITE(V0) {
  digitalWrite(D0, param.asInt());
}
BLYNK_WRITE(V1) {
  digitalWrite(D1, param.asInt());
}
BLYNK_WRITE(V2) {
  digitalWrite(D2, param.asInt());
}
BLYNK_WRITE(V3) {
  digitalWrite(D3, param.asInt());
}
// BLYNK_WRITE(V4) {
//   digitalWrite(D4, param.asInt());
// }

void setup() {
  //Set the LED pin as an output pin
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  // pinMode(D4, OUTPUT);
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
  delay(50);
}
