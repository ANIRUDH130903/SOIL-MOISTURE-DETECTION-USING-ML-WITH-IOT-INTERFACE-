#define BLYNK_TEMPLATE_ID "TMPL3BUbRCSIY"
#define BLYNK_TEMPLATE_NAME "Smart irrigation IOT2"
#define BLYNK_AUTH_TOKEN "" //enter your generated token using the blynk app.


#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//Initialize the LCD display
//LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "-Vjcc4Yz3i5MIZtrd3lN57fyT9YsYnwd";//Enter your Auth token
char ssid[] = "";//Enter your WIFI name
char pass[] = "";//Enter your WIFI password

DHT dht(D4, DHT11);//(DHT sensor pin,sensor type)  D4 DHT11 Temperature Sensor


BlynkTimer timer;
bool Relay = 0;


//Define component pins
#define sensor A0

#define waterPump D3


void DHT11sensor() { 
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V2, t);
 
  Blynk.virtualWrite(V3, h);

 
  //Serial.println(t);

  
  //Serial.println(h);

}

void soilMoistureSensor() {
  int sensorValue = analogRead(A0);
  //value = map(value, 0, 1023, 0, 100);
  //sensorValue = map(sensorValue, 0, 1024, 0, 100);
  //sensorValue = (sensorValue - 100) * -1;

  Blynk.virtualWrite(V0, sensorValue);
 
  //Serial.print(sensorValue);
}

 

 

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  timer.setInterval(100L, soilMoistureSensor);
  timer.setInterval(100L, DHT11sensor);
}

//Get the button value
BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {

    Blynk.logEvent( "water_pump_alert_" , "The Pump has started");
    //Blynk.email("anirudhsharma130903@gmail.com","water_pump_alert_","The Pump has started")
    
    digitalWrite(waterPump, LOW);
   
  } else {
    digitalWrite(waterPump, HIGH);
    
    Blynk.logEvent("water_pump_alert_","The Pump has not started");
    
  }
}



void loop() {
  

 if (Relay == 1) {
    Blynk.logEvent("water_pump_alert_","The Pump has started");
    //Blynk.email("anirudhsharma130903@gmail.com","water_pump_alert_","The Pump has started")
    
    digitalWrite(waterPump, LOW);
   
  } 
  
  else {
    digitalWrite(waterPump, HIGH);
    
    //Blynk.logEvent("water_pump_alert_","The Pump has not started");
    
  }



  




   
  
  int sensorValue = analogRead(A0);
  delay(1000);
  //value = map(value, 0, 1023, 0, 100);
 // sensorValue = map(sensorValue, 0, 1024, 0, 100);
  //sensorValue = (sensorValue - 100) * -1;

  //Blynk.virtualWrite(V0, sensorValue);
 
  Serial.println(sensorValue);
  delay(1000);



  
  
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer

  

}