#include "HomeSpan.h" 
#include "DEV_AirPurification.h" 

// Define pins for the rotary switch
const int switchPin0 = 23;  // Pin for position 1
const int switchPin1 = 22;  // Pin for position 2
const int switchPin2 = 18;  // Pin for position 3
const int switchPin3 = 19;  // Pin for position 4

// Define pins to control the circuits
const int circuitPin0 = 14;  // Pin for closing circuit on position 1
const int circuitPin1 = 27;  // Pin for closing circuit on position 2
const int circuitPin2 = 26;  // Pin for closing circuit on position 3
const int circuitPin3 = 25;  // Pin for closing circuit on position 4

int currentSwitchPosition = -1;  // Variable to store the current switch position, initialized to an invalid value
int newSwitchPosition = 0;  //storing the newly detected switch position
int position = -1; //current fan position set
int newPosition = 0;
int autoMode = 0;  //enabling or not homekit control

void setup() {

  pinMode(switchPin0, INPUT_PULLUP);
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);

  // Set circuit pins as outputs
  pinMode(circuitPin0, OUTPUT);
  pinMode(circuitPin1, OUTPUT);
  pinMode(circuitPin2, OUTPUT);
  pinMode(circuitPin3, OUTPUT);

  Serial.begin(115200);

  readSwitchPosition();
  setOutputPosition();


  homeSpan.begin(Category::AirPurifiers,"IKEA Purifier");

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify(); 
      new Characteristic::Name("Air Purifier");
      new Characteristic::Manufacturer("IKEA");  
      new Characteristic::Name("Model");
      new Characteristic::FirmwareRevision("0.1");

    new DEV_AirPurification();

} // end of setup()

//////////////////////////////////////

void loop(){
  
  homeSpan.poll();

  readSwitchPosition();
  setOutputPosition();

  
} // end of loop()

//////////////////////////////////////