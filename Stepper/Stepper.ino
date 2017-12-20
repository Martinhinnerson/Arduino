/* Fritt fall
   Martin Hinnerson
   Fenomenmagasinet
   2017-12-11
*/

#include <Adafruit_NeoPixel.h>

int delayVal = 9; // Lower = faster motor

// PIXEL SETUP
#define PIXEL_PIN 0
#define NUMPIXELS 16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//BUTTON SETUP
#define UP_BUTTON 4
#define DOWN_BUTTON 5
#define MAGNET_BUTTON 6
#define RELAY_PIN1 7
#define RELAY_PIN2 10
#define CALIBRATE_PIN 2
#define POT_PIN A0

boolean magnetState = true;

//DEBOUNCE
bool magnetButtonState;
bool lastMagnetButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

//GLOBALS

#define stepMax 1000
unsigned int stepIndex = stepMax;

void setup()
{
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(MAGNET_BUTTON, INPUT_PULLUP);
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);

  pinMode(CALIBRATE_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CALIBRATE_PIN), calibrate, CHANGE);

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);


  digitalWrite(RELAY_PIN1, LOW);
  digitalWrite(RELAY_PIN2, LOW);

  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(100);
  setPixels();
}

void loop()
{
  //Step the motor depending on the buttons up and down
  if (!digitalRead(UP_BUTTON) && stepIndex < stepMax) {
    stepIndex++;
    moveMotor(0);
  } else if (!digitalRead(DOWN_BUTTON) && stepIndex > 0) {
    stepIndex--;
    moveMotor(1);
  }

  //*******************************************************
  //Change magnet state when button is pressed, uses debounce
  int reading = digitalRead(MAGNET_BUTTON);
  if (reading != lastMagnetButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != magnetButtonState) {
      magnetButtonState = reading;
      if (magnetButtonState == HIGH) {
        Serial.println("change state");
        toggleMagnets();
      }
    }
  }
  lastMagnetButtonState = reading;
  //*******************************************************
/*
  int val = analogRead(POT_PIN);
  if(val > 50){
    val = 50;
  }
  delayVal = map(val, 7, 50, 2, 40);
  Serial.println(val);
  Serial.println(delayVal);
  delay(500);*/
}

void setPixels() {
  if (magnetState) {
    Serial.println("on");
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      pixels.setPixelColor(i + (NUMPIXELS / 2), pixels.Color(255, 0, 0));
    }
  } else {
    Serial.println("off");
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.setPixelColor(i + (NUMPIXELS / 2), pixels.Color(255, 255, 255));
    }
  }
  pixels.show();
}

void moveMotor(int dir)
{
  if (dir == 0)
  {
    digitalWrite(9, LOW);  //ENABLE CH A
    digitalWrite(8, HIGH); //DISABLE CH B

    digitalWrite(12, HIGH);   //Sets direction of CH A
    analogWrite(3, 255);   //Moves CH A

    delay(delayVal);

    digitalWrite(9, HIGH);  //DISABLE CH A
    digitalWrite(8, LOW); //ENABLE CH B

    digitalWrite(13, LOW);   //Sets direction of CH B
    analogWrite(11, 255);   //Moves CH B

    delay(delayVal);

    digitalWrite(9, LOW);  //ENABLE CH A
    digitalWrite(8, HIGH); //DISABLE CH B

    digitalWrite(12, LOW);   //Sets direction of CH A
    analogWrite(3, 255);   //Moves CH A

    delay(delayVal);

    digitalWrite(9, HIGH);  //DISABLE CH A
    digitalWrite(8, LOW); //ENABLE CH B

    digitalWrite(13, HIGH);   //Sets direction of CH B
    analogWrite(11, 255);   //Moves CH B

    delay(delayVal);
  }
  else
  {
    digitalWrite(9, LOW);  //ENABLE CH A
    digitalWrite(8, HIGH); //DISABLE CH B

    digitalWrite(12, HIGH);   //Sets direction of CH A
    analogWrite(3, 255);   //Moves CH A

    delay(delayVal);

    digitalWrite(9, HIGH);  //DISABLE CH A
    digitalWrite(8, LOW); //ENABLE CH B

    digitalWrite(13, HIGH);   //Sets direction of CH B
    analogWrite(11, 255);   //Moves CH B

    delay(delayVal);

    digitalWrite(9, LOW);  //ENABLE CH A
    digitalWrite(8, HIGH); //DISABLE CH B

    digitalWrite(12, LOW);   //Sets direction of CH A
    analogWrite(3, 255);   //Moves CH A

    delay(delayVal);

    digitalWrite(9, HIGH);  //DISABLE CH A
    digitalWrite(8, LOW); //ENABLE CH B

    digitalWrite(13, LOW);   //Sets direction of CH B
    analogWrite(11, 255);   //Moves CH B

    delay(delayVal);

  }
}

void calibrate()
{
  stepIndex = stepMax;
}

void toggleMagnets()
{
  magnetState = !magnetState;
  if (magnetState)
  {
    digitalWrite(RELAY_PIN1, HIGH);
    digitalWrite(RELAY_PIN2, HIGH);
  }
  else
  {
    digitalWrite(RELAY_PIN2, LOW);
    digitalWrite(RELAY_PIN1, LOW);
  }
  setPixels();
}

