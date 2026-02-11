weatherstation code.txt
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <AsyncTCP.h>
#endif
#include "config.h"

#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <Callmebot_ESP8266.h>

#define DHTPIN D2        // Pin where the DHT21 is connected
#define DHTTYPE DHT21    // DHT 21 (AM2301)
#define RAIN_SENSOR_PIN A0 // Analog pin for the rain sensor

#define HighTempThreshold 45
#define LowTempThreshold 20
#define HumidityThreshold 90
#define RainSensorThreshold 30
#define RainSensorThresholdlimit 55
#define RainSensorThreshold_fall 60

DHT dht(DHTPIN, DHTTYPE);
//Variables
double h, t;

#include <AsyncElegantOTA.h>



int rainSensorValue;



const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
String phoneNumber = WHATSAPP_PHONE;
String apiKey = WHATSAPP_API_KEY;
const String writeAPIKey = THINGSPEAK_API_KEY;


String messsage;

WiFiClient client;
//=========ThingSpeak
//20 min set
const uint32_t ThingSpkPostInt = 15000; 
uint32_t previousMillisThingSpeakUpdt = 15000; 

const uint32_t alertInterval_1 = 1200000; 
uint32_t previousMillisalertreport_1 = 1200000; 

const uint32_t alertInterval_2 = 1200000; 
uint32_t previousMillisalertreport_2 = 1200000; 

const uint32_t alertInterval_3 = 1200000; 
uint32_t previousMillisalertreport_3 = 1200000; 

const uint32_t alertInterval_4 = 1200000; 
uint32_t previousMillisalertreport_4 = 1200000; 

const uint32_t alertInterval_5 = 1200000; 
uint32_t previousMillisalertreport_5 = 1200000; 

uint32_t prevMillisMeasure = 0;

AsyncWebServer server(80);

void setup() {
Serial.begin(115200);
dht.begin();
pinMode(RAIN_SENSOR_PIN, INPUT);

WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
Serial.println("");

  // Wait for connection
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
request->send(200, "text/plain", "Hi! This is a sample response.");
});

AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
server.begin();
Serial.println("HTTP server started");

Callmebot.begin();

// Whatsapp Message
messsage = "Alert: Weather Station is powered on and successfully connected to the internet.";
Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
Serial.println(Callmebot.debug());


}

void loop() {

if (millis() > prevMillisMeasure + 5000) {

// Read temperature and humidity
h = dht.readHumidity();
t = dht.readTemperature();


  // Check if any reads failed
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

// Reading the rain sensor (analog value)
rainSensorValue = analogRead(RAIN_SENSOR_PIN);
rainSensorValue = map(rainSensorValue,300,1024,100,0);

// Print the results to the Serial Monitor
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" °C, Humidity: ");
Serial.print(h);
Serial.println(" % ");

Serial.print("rain Sensor intensity: ");
Serial.println(rainSensorValue);        
Serial.print("  ");
Serial.println("Waiting...");

prevMillisMeasure =  millis();
}



// ============== Alert texts
    if(t > HighTempThreshold && millis() - previousMillisalertreport_1 >= alertInterval_1){
    // Whatsapp Message
    messsage = "Alert: Temperature exceeds 45°C! Take precautions.";
    Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
    Serial.println(Callmebot.debug());
    previousMillisalertreport_1 =  millis();
    }

    if(t < LowTempThreshold && millis() - previousMillisalertreport_2 >= alertInterval_2){
      // Whatsapp Message
    messsage = "Alert: Temperature drops below 20°C!";
    Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
    Serial.println(Callmebot.debug());
    previousMillisalertreport_2 =  millis();
}

if(h > HumidityThreshold && millis() - previousMillisalertreport_3 >= alertInterval_3){
    // Whatsapp Message
    messsage = "Alert: Humidity exceeds 90%!";
    Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
    Serial.println(Callmebot.debug());
    previousMillisalertreport_3 =  millis();
}

    if(rainSensorValue >= RainSensorThreshold && rainSensorValue <= RainSensorThresholdlimit && millis() - previousMillisalertreport_4 >= alertInterval_4){
    // Whatsapp Message
    messsage = "Alert: Rain intensity exceeds threshold! Prepare for rain.";
    Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
        Serial.println(Callmebot.debug());
    previousMillisalertreport_4 =  millis();
    }

    if(rainSensorValue > RainSensorThreshold_fall && millis() - previousMillisalertreport_5 >= alertInterval_5){
    // Whatsapp Message
    messsage = "Alert: Rain is currently falling!!";
    Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
        Serial.println(Callmebot.debug());
    previousMillisalertreport_5 =  millis();
    }





  // Cloud CHANNEL //
if (millis() - previousMillisThingSpeakUpdt >= ThingSpkPostInt) {
    // save the last time was report to thingSpeak
    previousMillisThingSpeakUpdt = millis();


    // thingSpeak
    HTTPClient http;

    http.begin(client, "http://api.thingspeak.com/update");
    http.addHeader("X-THINGSPEAKAPIKEY", writeAPIKey);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Construct API request body
    String body = "";
if (!isnan(t)) {
    body += "field1=";
    body += String(t);
}

if (!isnan(h)) {
    body += "&field2=";
    body += String(h);
}
if (!isnan(rainSensorValue)){
    body += "&field3=";
    body += String(rainSensorValue);
}
// if starts with "&" then remove it
if (body.startsWith("&")) {
    body.remove(0, 1);
}


    int httpCode = http.POST(body);
    http.end();

    delay(5);
    Serial.print("HTTP Code: ");
Serial.println(httpCode);
    http.end();
}

}
