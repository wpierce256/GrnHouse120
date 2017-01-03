/*
Sketch Oct_17-16 Keyboard Relay Control.
 Wait for keyboard input:
    a = K1 ON
    b = K1 OFF
    c = K2 ON
    d = K2 OFF
 LED will be on when K1 is ON
Start up Serial Monitor and set to a Carriage return line ending at the 
bottom of the Serial Monitor window.  Type your character and press return.
*/
 const int ledPin = 13; // LED light on the Arduino
 const int K1Pin  = 8;  // K1 triggers on pin 8 LOW
 const int K2Pin  = 9;  // K2 triggers on pin 9 LOW
 char incomingByte = 'a';  // for incoming serial data
 
void setup() {
 pinMode (ledPin, OUTPUT);   // Set up the digital outputs
 pinMode (K1Pin, OUTPUT);
 pinMode (K2Pin, OUTPUT);
 digitalWrite (K1Pin, HIGH); // Start with relays turned off
 digitalWrite (K2Pin, HIGH);
 Serial.begin (9600);        // Set up the Serial port to 9600 baud
}

void loop() {
  while (Serial.available() > 0)  // if there's any serial available, read it
  {
  incomingByte = Serial.read();   // read the incoming byte
  Serial.print (incomingByte);    // report what character received
  
  switch (incomingByte)           // handle the input byte
    {
    case 'a':
      {
       digitalWrite (ledPin, HIGH); // Turn on the LED
       digitalWrite (K1Pin, LOW);   // Turn on the K1 Relay
      }
      break; 
    case 'b':
      {
       digitalWrite (ledPin, LOW);  // Turn off the LED
       digitalWrite (K1Pin, HIGH);  // Turn off the K1 Relay
      } 
      break; 
    case 'c':
      {
       digitalWrite (K2Pin, LOW);   // Turn on the K2 Relay
      } 
      break; 
    case 'd':
      {
       digitalWrite (K2Pin, HIGH);  // Turn off the K2 Relay
      } 
      break; 
    }
  }
}
