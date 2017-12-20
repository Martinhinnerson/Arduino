/*
Skrikkammare
Martin Hinnerson
2015-08-05
*/

/////////////////////LIBRARIES
#include <Adafruit_NeoPixel.h>

//////////////////PINS
#define ledPin1 10 //pin till neopixel
#define buttonPin 5
#define micPin A0 // select the input pin for the mic

////////////////Global Variables
int numPixels = 120;

int record = 0;
unsigned int currentPixels; // nuvarande ljudnivå

unsigned int decibel;
unsigned int modifiedDecibel;

//Measuring
const int sampleWindow = 50; //sample window width in mS (50 mS = 20Hz)
int micVal = 0; // variable to store the value coming from the mic
unsigned int sample;

//Map
const int numReadings = 6; //Ändrar hur många läsningar medelvärdet tas på
int readings[numReadings];      // list of last voltages
int index = 0;                  // the index of the current reading
int totalVolts = 0;                  // the running totalPixels
int averageVolts = 0;                // the averagePixels
int modifiedAverage = 0;


////////////NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, ledPin1, NEO_GRB + NEO_KHZ800);

///////////Färger
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t purple = strip.Color(200, 0, 200);
uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t off = strip.Color(0, 0, 0);


//////////////////////// Setup som körs när du startar Arduino eller trycker på reset:
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  // initiera neoPixel
  strip.begin();
  strip.setBrightness(32);
  strip.show();

  Serial.begin(9600); // initialize serial communication with computer
}


//////////////////// Huvudloop som körs i väntan på knapptryck:
void loop() {
  simpleWave(0.1, 100, 10); //Loopar tills knapptryck
  delay(5);
}

////////////////// Skrikloopen
void start() {
  twinkleRand(5,strip.Color(255,0,255),strip.Color(0, 255, 0),90);
  delay(10);
  stripSet(off, 10);

  for(int i=0; i<10000; i++){
  readDecibel();  //Läs av micken
  mapToPixels();  //Mappa om mätvärden till pixlar på ledslinga
  paintLeds(modifiedAverage, record); //Rita ut 
  }
  delay(10); //För stabilitet
}
















