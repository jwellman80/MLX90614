#include <i2cmaster.h>
#include <MLX90614.h>

MLX90614* sensor;

void setup() 
{
  Serial.begin(9600);
  // initialize the sensor
  sensor = new MLX90614();
}

void loop() 
{
  // get the temp and output in Celsius
  Serial.print("Ambient:\t");
  Serial.print(sensor->GetTempAmbient(), 2);
  Serial.print("C\t");
  Serial.print("IR:\t");
  Serial.print(sensor->GetTempIR(), 2);
  Serial.println("C");
  
  // get the temp and output in Fahrenheit
  Serial.print("Ambient:\t");
  Serial.print(sensor->GetTempAmbient('F'), 2);
  Serial.print("F\t");
  Serial.print("IR:\t");
  Serial.print(sensor->GetTempIR('F'), 2);
  Serial.println("F");
  
  delay(1000);  
}
