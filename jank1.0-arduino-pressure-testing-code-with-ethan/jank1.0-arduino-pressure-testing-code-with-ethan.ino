/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

float pressure[3];
float current;
uint16_t ADC2ConvertedValues[256];

uint32_t sum = 0;
uint16_t mean = 0;


#define ADC_VOLTAGE_CONVERSION 0.0008058608F
#define RSHUNT 0.5F
#define V2LP 62.5F
#define V2HP 580.151F
//#define VGain_1  ADC_VOLTAGE_CONVERSION*V2LP*3/2
#define VGain_1  1.8518518519
#define VGain_2 ADC_VOLTAGE_CONVERSION*V2HP
#define IGain ADC_VOLTAGE_CONVERSION/RSHUNT/50.0

//float offset[4] = {-31.25, -31.25, 0, 0};
float offset[4] = {-13,-15, 0, 0};

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int sensorValue1 = 0;        // value read from the pot
int outputValue1= 0; 

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  sensorValue1 = analogRead(analogInPin1);
  // map it to the range of the analog out:
  outputValue1 = map(sensorValue1, 0, 1023, 0, 255);
  // change the analog out value:
  //analogWrite(analogOutPin, outputValue);


  for (uint8_t i=0; i < 4; i++) {
    //sum = 0;
    //mean = (outputValue+outputValue1)*0.5;

  
//    for(uint8_t j=0; j < 64; j++) {
//      sum += ADC2ConvertedValues[i + 4*j];
//    }

    //mean = sum/64;
    mean=0;

    //i = 0, 1 psi250 max. i=2 psi5805.51 max
    switch (i)
    {
      case 0:
        pressure[0] = (((float)outputValue)*VGain_1) + offset[i];
      break;

      case 1:
        pressure[1] = (((float)outputValue1)*VGain_1) + offset[i];
      break;

      case 2:
        pressure[2] = (((float)mean)*VGain_2) + offset[i];
      break;

//      case 3:
//        current = (((float)mean)*IGain) + offset[i];
//      break;

      default:
      break;
        }
  }

   // print the results to the Serial Monitor:
  Serial.print(pressure[0]);
  Serial.print("\t");
  Serial.println(pressure[1]);

  


  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(20);
}
