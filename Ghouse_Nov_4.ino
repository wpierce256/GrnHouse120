/* 
Sketch_Mar20A_Grn_Hou_RDuinoStarter Example: Temperature Sensor
 - Communicates with a DS18B20 temperature sensor, shows value read.
 - SEE the comments after "//" on each line below
 - CONNECTIONS: (Holding chip with pins down, label towards you)
 - Black  pin:  Ground
 - Red pin:  +5V
 - White pin: Arduino Pin 10 and ALSO "Pullup Resistor":
 - Center pin: to 4700 (4.7K) or 5K resistor * (other end goes to +5V) 
 * NOTE: Two 10K resistors connected in parallel can be used.
 
/*-----( Import needed libraries )-----*/
#include <OneWire.h>            // For many "1-wire" devices
#include <DallasTemperature.h>  // Specific for temperature sensors
#include <SoftwareSerial.h>
const int switchPin = 3;
const int ledPin    = 13;
const int K1Pin     = 5;
const int K2Pin     = 6;
const int SetPoint  = 72;  //Desired Temperature
SoftwareSerial mySerial(8,9); // RX, TX
/*-----( Declare Constants and Pin Numbers )-----*/
// Data wire is plugged into port 9 on the Arduino (can be changed)
#define ONE_WIRE_BUS 10    // NOTE: No ";" on #define  

/*-----( Declare objects )-----*/
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass address of our oneWire instance to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

/*-----( Declare Variables )-----*/
float  TempInF  ; //Floating Point variable for F Temperature
int switchState;  //Switch was HIGH=1 or LOW=0
void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);    // start serial port
  // while (!Serial) {
  //  ; 
  pinMode(ledPin, OUTPUT);   // This pin will be an output
  pinMode(K1Pin, OUTPUT);    // This pin will be an output
  pinMode(K2Pin, OUTPUT);    // This pin will be an output
  pinMode(switchPin, INPUT); // Not really needed: default
  Serial.begin(9600);        // Start up the Serial Monitor
  mySerial.println("YourDuinoStarterSet ITS ON OFF Test");
    
  // wait for serial port to connect. Needed for Leonardo only
  // } 
  Serial.println("Local Output");
  mySerial.begin(9600);
  mySerial.println("YourDuinoStarter Example: DS18B20 Temperature Sensor Reading");
  
  sensors.begin();    // Start up the temperature measurement library
}//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{ 
  delay(20000);
  // mySerial.println(); 
 // mySerial.print("Green House ...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  // mySerial.println("DONE");

  /*----( Here we will save values to use for other things)------*/
  TempInF = sensors.getTempFByIndex(0); // Get and save sensor value
  // mySerial.println("Here are our saved values");
 // mySerial.print("Temperature in F = ");
  mySerial.print(TempInF, 2);    // "2" sets the number of decimal places  
  mySerial.print(",");
  switchState = digitalRead(switchPin);
/*--(NOTE!!! "==" means "compare equal"  )--*/  
  if (switchState == HIGH)   // Switch was pushed
  {
  //  mySerial.println("ITS -ON - !");
    digitalWrite(ledPin, HIGH);
  }
  else
  {
   // mySerial.println("ITS -OFF- !");
    digitalWrite(ledPin, LOW);
  }

/*--(Compare TempInF to SetPoint and make decisions )--*/  
  if (TempInF >= (SetPoint + 5))
    {
     // mySerial.println("It's too warm. Fan on.");
      digitalWrite(K1Pin, LOW);
    }
    else
    {
      digitalWrite(K1Pin, HIGH);
    }
  if (TempInF <= (SetPoint - 5))
    {
     // mySerial.println("It's too cold. Heat on.");
      digitalWrite(K2Pin, LOW);
    }
    else
    {
      digitalWrite(K2Pin, HIGH);
    }
 // mySerial.println(); 
 
}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
//none
//*********( THE END )***********
