#define ANALOG_IN_PIN 33

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Solar Project"
#define BLYNK_AUTH_TOKEN ""

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "";
char pass[] = "";

int chargePercent; 

float adc_voltage = 0.0;
float in_voltage = 0.0;
 
float R1 = 30000.0;
float R2 = 7500.0; 
float ref_voltage = 3.3;
int adc_value = 0;

BlynkTimer timer; 

void myTimer() 
{
  Blynk.virtualWrite(V1, chargePercent);
  Blynk.virtualWrite(V0, in_voltage);
}

void setup(){
  Serial.begin(9600);
  Serial.println("Starting...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); 
  timer.setInterval(1000L, myTimer); 
}
 
void loop(){
  adc_value = analogRead(ANALOG_IN_PIN);
  adc_voltage  = (adc_value * ref_voltage) / 4096.0;
  in_voltage = adc_voltage*(R1+R2)/R2;
  chargePercent = (in_voltage/14)*100;
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 2);
  Serial.println(chargePercent);


  Blynk.run(); 
  timer.run(); 

  delay(1000);
}
