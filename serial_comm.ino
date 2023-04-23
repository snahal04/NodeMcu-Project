#include <ESP8266WiFi.h>


// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[ ] = "SMVDU.";
char pass[ ] = "123456789";

void setup()
{
  Serial.begin(115200);
  // Connect to WiFi 
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
  pinMode(5, OUTPUT);
}


//In the loop function include Blynk.run() command.
void loop() 
{
  if (Serial.available())
  {
    char point = Serial.read();
    switch (point)
    {
      case '1':
        digitalWrite(5,HIGH); // Not !5 use High and Low
        break;
//      case '2':
//        digitalWrite(4,HIGH);
//        break;
      case '3':
        digitalWrite(5,LOW); // Not !5 use High and Low
        break;
//      case '4':
//        digitalWrite(5,LOW); // Not !5 use High and Low
//        break;
    }  // End of switch
  }  // End of if
  delay(50);  // I have no idea why, but most programs of this sort have a delay in.  (Hope someone explains to me too)
}  // End of function

