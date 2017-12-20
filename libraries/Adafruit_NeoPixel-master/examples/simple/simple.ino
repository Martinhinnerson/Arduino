
#include <Adafruit_NeoPixel.h>
#define PIN            2
#define NUMPIXELS      21

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second

void setup()
{
  pixels.begin();
  pixels.setBrightness(150);
}

void loop()
{
  /*
  }
  for (int i = 0; i < 7; i++)
    {
      pixels.setPixelColor(i, 40, 170, 170);
      pixels.show();
      delay(10);
    }
    delay(50);
  for (int i = 7; i < 14; i++)
    {
      pixels.setPixelColor(i, 80, 200, 200);
      pixels.show();
      delay(10);
    }
    delay(50);
  for (int i = 14; i < 21; i++)
    {
      pixels.setPixelColor(i, 120, 240, 240);
      pixels.show();
      delay(10);
    }
    delay(50);
    */
  simpleWave(0.03, 100, 10);
}

void pixelsOff()
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
  }
}

void simpleWave(float rate, int cycles, int wait) {
  float pos = 0.0;
  // cycle through x times
  for (int x = 0; x < (pixels.numPixels()*cycles); x++)
  {
    pos = pos + rate;
    for (int i = 0; i < NUMPIXELS; i++) {
      // sine wave, 3 offset waves make a rainbow!
      float level = sin(i + pos) * 127 + 128;
      // set color level
      if (level < 70)
      {
        level = 70;
      }
      pixels.setPixelColor(i, 50, (int)level, (int)level);
    }
    pixels.show();
    delay(wait);
  }
}
