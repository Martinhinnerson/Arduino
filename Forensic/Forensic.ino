
#include <Adafruit_NeoPixel.h>
#define PIN            2
#define potPin         A5
#define NUMPIXELS      3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin();
  int brightness = map(analogRead(potPin), 0, 30, 0, 255);
  pixels.setBrightness(brightness);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
}

void loop()
{ 
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.setPixelColor(1, 255, 255, 255);
  pixels.setPixelColor(2, 0, 255, 0);
  pixels.show();
  delay(2000);
  pixelsOff();
  delay(10000);

}

void pixelsOff()
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
  }
}

