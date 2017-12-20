
#include <Adafruit_NeoPixel.h>
#define PIN            10
#define NUMPIXELS      26

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pixels.begin();
  pixels.setBrightness(100);
  pinMode(PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 14; i++)
    {
      switch (j) {
        case 0: pixels.setPixelColor(i, 255, 0, 0);
        break;
        case 2: pixels.setPixelColor(i, 0, 255, 0);
        break;
        case 1: pixels.setPixelColor(i, 0, 0, 255);
        break;
      }
      pixels.show();
      delay(30);
    }
    for (int i = 0; i < 7; i++)
    {
      switch (j) {
        case 0: pixels.setPixelColor(14 + i, 255, 0, 0);
          pixels.setPixelColor(NUMPIXELS - i, 255, 0, 0);
          break;
        case 2: pixels.setPixelColor(14 + i, 0, 255, 0);
          pixels.setPixelColor(NUMPIXELS - i, 0, 255, 0);
          break;
        case 1: pixels.setPixelColor(14 + i, 0, 0, 255);
          pixels.setPixelColor(NUMPIXELS - i, 0, 0, 255);
          break;
      }
      pixels.show();
      delay(30);
    }
    //delay(500);
  }

}
void pixelsOff()
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
  }
}

