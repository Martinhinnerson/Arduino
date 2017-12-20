/* Luktoalett
 * 2016-08-08
 * Martin Hinnerson
 * Fenomenmagasinet
 */

#include <MP3Trigger.h>
#include <Adafruit_NeoPixel.h>

//#define DEBUGMODE
#define ledPin1 13 //pin till neopixel

MP3Trigger trigger;

const byte numMotors = 5;

byte relayPins[numMotors] = {9, 10, 11, 12, 7};
byte buttonPins[numMotors] = {2, 3, 4, 5, 6};
byte fanPin = 8;

bool buttonState[] = {LOW, LOW, LOW, LOW, LOW};
bool buttonState_old[] = {LOW, LOW, LOW, LOW, LOW};
bool buttonPressed[] = {LOW, LOW, LOW, LOW, LOW};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, ledPin1, NEO_GRB + NEO_KHZ800);

uint32_t green = strip.Color(0, 255, 0);
uint32_t red = strip.Color(255, 0, 0);

void setup()
{
  for (int i = 0; i < numMotors; i++)
  {
    pinMode(relayPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  pinMode(fanPin, OUTPUT);

  trigger.setup(&Serial);
  Serial.begin(MP3Trigger::serialRate());

  strip.begin();
  strip.setBrightness(255);
  strip.show();

  delay(2000);
}

void loop()
{

  strip.setPixelColor(0, green);
  strip.show();
  trigger.update();
  digitalWrite(fanPin, LOW);

#ifdef DEBUGMODE
  Serial.println("-----------------------------------");
#endif
  for (int i = 0; i < numMotors; i++)
  {
    /*  buttonState_old[i] = buttonState[i];
      buttonState[i] = digitalRead(buttonPins[i]);

      if (buttonState[i] == HIGH && buttonState_old[i] == LOW)
      {
        buttonPressed[i] = HIGH;
      }
    */

    buttonPressed[i] = digitalRead(buttonPins[i]);

#ifdef DEBUGMODE
    Serial.println(buttonState[i]);
    delay(100);
#endif
  }
#ifdef DEBUGMODE
  Serial.println("-----------------------------------");
#endif

#ifndef DEBUGMODE
  for (int i = 0; i < numMotors; i++)
  {
    if (buttonPressed[i])
    {
      strip.setPixelColor(0, red);
      strip.show();
      digitalWrite(relayPins[i], HIGH);
      digitalWrite(fanPin, HIGH);
      delay(7000);
      digitalWrite(relayPins[i], LOW);
      delay(12000);
      digitalWrite(fanPin, LOW);
      delay(1000);
    }
  }
#endif
  delay(10); //<---------------------------------------
  int temp = random(0, 9000);
  switch (temp)
  {
    case 2000:
      trigger.trigger(1);
      break;
    case 4000:
      trigger.trigger(2);
      break;
    case 6000:
      trigger.trigger(3);
      break;
    case 8000:
      trigger.trigger(4);
      break;
  }
}
