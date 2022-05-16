// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
void setup(void) 
{ 
 // start serial port 
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
} 
void loop(void) 
{  
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 Serial.print(" Requesting temperatures..."); 
 sensors.begin(); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperature is: ");  
 int temp = sensors.getTempCByIndex(0);
 if (temp != 21){ //21 degrees = room temperature
  analogWrite(5,(3*temp*temp - 126*temp + 1376)); //fan curve equation
 } else {
  analogWrite(5,0);
 }
 if (temp < 21) {
  analogWrite(6,(255 - 6*temp)); //supposed to be for resistance wire
 }
 else {
  analogWrite(6, 0);
 }
 //Serial.print(sensors.getTempCByIndex(0)); 
 Serial.print(temp);
   // 0 refers to the first IC on the wire 
   delay(1000); 

} 
