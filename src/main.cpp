#include <Arduino.h>
#include<WiFi.h>
#include<HTTPClient.h>
#include<ArduinoJson.h>
#include<DallasTemperature.h>
#include<OneWire.h>
#include"env.h"


OneWire oneWire(temp_sensor);
DallasTemperature sensors(&oneWire);

void putTemp (float temp){
  HTTPClient http;
  JsonDocument doc;

  doc["temp"] = temp;
  doc.shrinkToFit();

  String requestBody;
  serializeJson(doc, requestBody);

  // Establish a connection to the server
 http.begin(tempendpoint);
    // Specify content-type header
    http.addHeader("Content-Type", "application/json");
    http.addHeader("api-key",api_key);
    int httpResponseCode = http.PUT(requestBody);
 
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println("Temperature sent successfully");
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
}
}


void setup() {
  Serial.begin(9600);
	sensors.begin();
  sensors.setWaitForConversion(true);
  delay(1000);
	// WiFi_SSID and WIFI_PASS should be stored in the env.h
  WiFi.begin(ssid,password);

	// Connect to wifi
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(led_pin, OUTPUT);
}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){

    HTTPClient http;
    String requestBody;
  
    // Establish a connection to the server
    http.begin(lightendpoint);
    
    // Specify content-type header
    http.addHeader("api-key",api_key);
  

int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    String response = http.getString();
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc,response);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    bool lightStatus = doc["light"];
    // Control your light circuit based on lightStatus value (true/false)
    digitalWrite(led_pin,lightStatus); 

    Serial.print("Light Status: ");
    Serial.println(lightStatus);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
   http.end();
 
 
   sensors.requestTemperatures();
   float temp = sensors.getTempCByIndex(0);
   putTemp(temp);
   Serial.println(temp);
  
}
  else {
    Serial.println("WiFi Disconnected");
  
  }
}

  
   
   