

#include <ESP8266WiFi.h>
void upload();
unsigned int i=0;
String apiWritekey = "KM7HGS2UCG2GEHKJ"; // replace with your THINGSPEAK WRITEAPI key here
const char* ssid = "Tirth"; // your wifi SSID name
const char* password = "123456710" ;// wifi pasword
 
const char* server = "api.thingspeak.com";
WiFiClient client;

void setup() {
  pinMode(D5,INPUT);
   pinMode(D1,INPUT);
    pinMode(D4,OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
  // print out the value you read:
   int s1 = digitalRead(D1);
 int s2 = digitalRead(D5);
  if(sensorValue>500)
  { 
    digitalWrite(D4,LOW);
    if(s1==LOW)
    { 
       i=++i;
        
      Serial.println(i);
      delay(100);
    
    }
    
    if(s2==LOW)
    {
      i=--i;
        
      Serial.println(i);
      delay(100);
       
     
      }
      if(i==0)
      {
       digitalWrite(D4,HIGH);
       
      }
      }
    
  
if(sensorValue<500)
  {
     digitalWrite(D4,HIGH);
  }


 
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(sensorValue);
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
    // Serial.print("Temperature: ");
     Serial.println(sensorValue);
    Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
 Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);
  
  
 
  delay(1);        // delay in between reads for stability
}
