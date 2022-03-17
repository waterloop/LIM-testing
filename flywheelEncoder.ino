/* Read Quadrature Encoder
   Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.

   Sketch by max wolf / www.meso.net
   v. 0.1 - very basic functions - mw 20061220

*/

int val;
int encoder0PinA = 3;
int encoder0PinB = 2;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
const int clicksPerRev = 400;
unsigned long startMillis = 0;  
unsigned long currentMillis = 0;
unsigned long rotationTime = 0;
int period = 0;
double revCount = 0;
double rpm = 0;
int n = LOW;

void setup() {
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  Serial.begin (9600);
}

void loop() {
  // Increments position
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--; //CCW
    } else {
      encoder0Pos++; //CW
    }
    //Uncomment to print position of every click
    //Serial.print (encoder0Pos);
    //Serial.print ("/");
  }

  // Gives decimal vlue for #rotations
  //revCount = encoder0Pos / clicksPerRev;

  // After 1 minute print the number of revolutions in the serial panel
  currentMillis = millis();  //get time since program started
  if (abs(encoder0Pos) == clicksPerRev) {  //test whether the rotation has elapsed
    
    rotationTime = millis() - startMillis;
    rpm = 60000/rotationTime;
    Serial.println (rpm);
    
    encoder0Pos = 0;
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
  encoder0PinALast = n;
}
