/*
   created by ArduinoLucian

    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
*/

int trigPin = 11;     // Trigger
int echoPin = 12;     // Echo
int speaker = 10;     // Speaker
long duration;
long cm;
long inches;
const int threshold_cm = 100;    // Distance to set off the alarm (in cm)
const int threshold_inches = 78; // Distance to set off the alarm (in inches)
int i = 0;                    // Counter used in sound alarm

void setup() {
  //Setup Baud Rate for serial port
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT); // Sensor output
  pinMode(echoPin, INPUT);  // Sensor input
  pinMode(speaker, OUTPUT); // Speaker Output
}

void loop() {

  digitalWrite(trigPin, LOW);   // Set sensor trigger LOW
  delayMicroseconds(5);         // Time to settle
  digitalWrite(trigPin, HIGH);  // Start sensor
  delayMicroseconds(20);        // Wait
  digitalWrite(trigPin, LOW);   // Turn off sensor

  // Duration is the time in useconds between the ping was sent
  // until the echo is received
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(250);

  if ( cm < threshold_cm) {                 // || inches < threshold_inches
    for ( i = 100; i < 1500; i++) {
      tone(speaker, i);
    }
  }
    else
      noTone(speaker);
  }
