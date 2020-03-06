/*
    ADXL345 Testing 
    (c) MyCaptain 2020 , Aman Malhotra
*/

#include <Wire.h>
#include <ADXL345.h>

ADXL345 accelerometer;

void setup(void) 
{
  Serial.begin(9600);

  // Initialize ADXL345
  Serial.println("Initialize ADXL345");

  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }

  
  accelerometer.setRange(ADXL345_RANGE_16G);
}

void loop(void) 
{
  // Read normalized values
  Vector norm = accelerometer.readNormalize();

  // Low Pass Filter to smooth out data. 0.1 - 0.9
  Vector filtered = accelerometer.lowPassFilter(norm, 0.5);

  // Calculate Pitch & Roll
  int pitch = -(atan2(norm.XAxis, sqrt(norm.YAxis*norm.YAxis + norm.ZAxis*norm.ZAxis))*180.0)/M_PI;
  int roll  = (atan2(norm.YAxis, norm.ZAxis)*180.0)/M_PI;

  // Calculate Pitch & Roll (Low Pass Filter)
  int fpitch = -(atan2(filtered.XAxis, sqrt(filtered.YAxis*filtered.YAxis + filtered.ZAxis*filtered.ZAxis))*180.0)/M_PI;
  int froll  = (atan2(filtered.YAxis, filtered.ZAxis)*180.0)/M_PI;

  // Output (filtered)
  Serial.print(" (filter)Pitch = ");
  Serial.print(fpitch);
  Serial.print(" (filter)Roll = ");
  Serial.print(froll);
  Serial.println();

  delay(100);
}
