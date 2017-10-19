/*  UltrasonicDistance
*   Arduino firmware for measuring distance with ultrasonic distance sensor.
*   Device has buzzer, which changes beep frequency according to measured distance.
*   Author: Drago Trebežnik
*   
*   Wiring
*   ======
*   Ultrasonic sensor - Arduino Nano:
*   VCC --- 5V
*   Trig --- D10
*   Echo --- D9
*   GND --- GND
*   
*   Buzzer is connected to D3
*/ 

const int trigger_pin = 10;   // trigger pin from ultrasonic sensor
const int echo_pin = 9;       // echo pin from ultrasonic sensor
const int buzzer_pin = 3;     // buzzer pin

// Define duration and distance variables:
long duration;
int distance;

void setup() {
  pinMode(trigger_pin, OUTPUT);     // set the trigger_pin as an output
  pinMode(echo_pin, INPUT);         // set the echo_pin as an input
  Serial.begin(9600);               // start the serial communication
}

void loop() {
  digitalWrite(trigger_pin, LOW);   // clear the trigger_pin
  delayMicroseconds(2);
  
  // Set the trigger_pin on HIGH state for 10 micro seconds:
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  
  // Read the echo_pin and return the sound wave travel time in microseconds:
  duration = pulseIn(echo_pin, HIGH);
  // Calculate the distance:
  distance = duration*0.034/2;
  
  // Print the measured distance and sound frequency to the serial console:
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(", sound frequency: ");
  // Map distance to frequency (distribute sound frequency (from 1000 to 20 Hz) to distance (from 0 do 50 cm))
  int frequency = map(distance, 0, 50, 1000, 20);
  Serial.println(frequency);
  
  if (distance>50) // beep only if distance is less than 0.5 m
  {
    noTone(buzzer_pin);
  }
  else
  {
    tone(buzzer_pin,frequency);
    }
    
  delay(100);
}
