/////////////////////////////////////////////////FUNKTIONER/////////////////////////////////////////////////////////


//////////////////////////////////Konvertera HSV till RGB

void HSVtoRGB(int hue, int sat, int val, int *colors) {
  int r, g, b, base;

  // hue: 0-359, sat: 0-255, val (lightness): 0-255


  if (sat == 0) { // Achromatic color (gray).
    colors[0] = val;
    colors[1] = val;
    colors[2] = val;
  } else  {
    base = ((255 - sat) * val) >> 8;
    switch (hue / 60) {
      case 0:
        colors[0] = val;
        colors[1] = (((val - base) * hue) / 60) + base;
        colors[2] = base;
        break;
      case 1:
        colors[0] = (((val - base) * (60 - (hue % 60))) / 60) + base;
        colors[1] = val;
        colors[2] = base;
        break;
      case 2:
        colors[0] = base;
        colors[1] = val;
        colors[2] = (((val - base) * (hue % 60)) / 60) + base;
        break;
      case 3:
        colors[0] = base;
        colors[1] = (((val - base) * (60 - (hue % 60))) / 60) + base;
        colors[2] = val;
        break;
      case 4:
        colors[0] = (((val - base) * (hue % 60)) / 60) + base;
        colors[1] = base;
        colors[2] = val;
        break;
      case 5:
        colors[0] = val;
        colors[1] = base;
        colors[2] = (((val - base) * (60 - (hue % 60))) / 60) + base;
        break;
    }

  }
}

///////////////////////////////////////////ENKEL VÅG

// very simple wave: velocity, cycles,delay between frames
// simpleWave(0.03,5,10);
void simpleWave(float rate, int cycles, int wait) {
  float pos = 0.0;
  // cycle through x times
  for (int x = 0; x < (strip.numPixels()*cycles); x++)
  {
    pos = pos + rate;
    for (int i = 0; i < numPixels; i++) {
      if (buttonPin == HIGH) {
        start();
      }
      // sine wave, 3 offset waves make a rainbow!
      float level = sin(i + pos) * 127 + 128;
      // set color level
      strip.setPixelColor(i, (int)level, 0, (int)level);
    }
    strip.show();
    delay(wait);
  }
}

////////////////////////// SÄTT HELA SLINGAN I EN FÄRG

void stripSet(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < numPixels; i++) {
    strip.setPixelColor(i, c);
  }

  // move the show outside the loop
  strip.show();
  delay(wait);
}

////////////////////////////////////////RANDOM

// number, twinkle color, background color, delay
// twinkleRand(5,strip.Color(255,255,255),strip.Color(255, 0, 100),90);

// twinkle random number of pixels
void twinkleRand(int num, uint32_t c, uint32_t bg, int wait) {
  // set background
  stripSet(bg, 0);
  // for each num
  for (int i = 0; i < num; i++) {
    strip.setPixelColor(random(strip.numPixels()), c);
  }
  strip.show();
  delay(wait);
}

//////////////////////////////// Map med decimaltal
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

////////////////////////////////Största värdet i en lista
int getIndexOfMaximumValue(int* array, int size) {
  int maxIndex = 0;
  int max = array[maxIndex];
  for (int i = 1; i < size; i++) {
    if (max < array[i]) {
      max = array[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}


