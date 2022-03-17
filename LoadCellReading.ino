/* The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.
 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND

 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.

*/

#include "HX711.h"

#define calibration_factor 75.0 //This value is obtained using the SparkFun_HX711_Calibration sketch


#define DOUT1  3
#define CLK1  2

#define DOUT2  5
#define CLK2  4

HX711 scale1;
HX711 scale2;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");

  scale1.begin(DOUT1, CLK1);
  scale1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale1.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale2.begin(DOUT2, CLK2);
  scale2.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale2.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
}

void loop() {
  Serial.print("Reading: ");
  Serial.print((scale1.get_units() + scale2.get_units()), 1); //scale.get_units() returns a float
  Serial.print(" g"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
}
