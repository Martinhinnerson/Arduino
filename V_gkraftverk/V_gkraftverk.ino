/*
    Vågkraftverk
    Martin Hinnerson
    Fenomenmagasinet
    2017-06-12
*/
//--------- DEBUG -------------
//#define DEBUG 1
//#define DEBUG_SENSOR 1
//--------- SETUP -------------
#define SENSORPIN A0
#define PIXELPIN 6
#define NUMPIXELS 27
#define NUMREADINGS 10 //Hur många gamla läsningar som sparas i listan
#define MAXREADING 1023 //Största tillåtna läsningen, för att ta bort spikar
#define measurementSpeed 5 //Hur ofta en mätning tas
#define pixelUpdateSpeed 1000 //Hur ofta pixlarna uppdateras
#define pixelDelay 40
//-----------------------------
#include <Adafruit_NeoPixel.h>
//#include <RGBConverter.h> 
//-----------------------------5
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);
//-----------------------------
unsigned int mappedPixels = 0; //mätningen mappad till hur många pixlar det finns

unsigned long lastMeasurement = 0L; //timer
unsigned long lastPixelUpdate = 0L; //timer

int voltageMean = 0; //medelvärdet av voltageArray
int voltageArray[NUMREADINGS]; //lista med gamla märvärden
int voltageArrayPtr = 0; //pekare som visar vart i listan vi är
byte rgbColors[3];
int r[] = {0,0,31,66,102,138,173,204};
int g[] = {71,83,105,129,153,177,201,221};
int b[] = {214,250,255,255,255,255,255,255};
//-------- Setup --------------
void setup() {
  pinMode(SENSORPIN, INPUT);
  pinMode(6, OUTPUT);
  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
}
//--------- Main --------------
void loop() {
#ifdef DEBUG_SENSOR
  Serial.println(analogRead(SENSORPIN));
  delay(200);
#endif

#ifndef DEBUG_SENSOR

  //Take measurement
  /*  if (millis() - lastMeasurement > measurementSpeed) {
      lastMeasurement = millis();

      int reading = analogRead(SENSORPIN);

      if (reading > MAXREADING) {
        reading = MAXREADING;
      }

      voltageArray[voltageArrayPtr] = reading;
      voltageArrayPtr++;

      if (voltageArrayPtr >= NUMREADINGS) {
        voltageArrayPtr = 0;
      }
    }*/

  //Update pixels
  if (millis() - lastPixelUpdate > pixelUpdateSpeed) {
    lastPixelUpdate = millis();

    //voltageMean = meanNoZeros(voltageArray, NUMREADINGS);

    int reading = analogRead(SENSORPIN);
    mappedPixels = map(reading, 0, MAXREADING, 1, 18);
    for (int i = 0; i <= NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    for (int i = 0; i < mappedPixels; i++) {
      if (i < 8)
      {
        pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(0, 60, 180));
      }
      else
      {
        pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(0, 60, 180));
      }
      pixels.show();
      delay(pixelDelay);
    }
    if (mappedPixels == 18)
    {
      for (int i = mappedPixels; i < NUMPIXELS; i++)
      {
        pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(0, 60, 180));
        pixels.show();
        delay(pixelDelay);
      }
      for (int i = 0; i < NUMPIXELS; i++)
      {
        pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(0, 0, 0));
        pixels.show();
        delay(pixelDelay);
      }
    }
    else
    {
      for (int i = mappedPixels - 1; i > 0; i--)
      {
        pixels.setPixelColor(NUMPIXELS - i - 1, pixels.Color(0, 0, 0));
        pixels.show();
        delay(pixelDelay);
      }
    }
#ifdef DEBUG
    Serial.print("[");
    for (int i = 0; i < NUMREADINGS; i++)
    {
      Serial.print(" ");
      Serial.print(voltageArray[i]);
      Serial.print(" ");
    }
    Serial.print("] - ");

    Serial.print(voltageMean);
    Serial.print(" - ");
    Serial.println(mappedPixels);
#endif
  }

#endif
}

//Find the mean of an array
float mean(int * array, int lengthOfArray) {
  long sum = 0L;
  for (int i = 0; i < lengthOfArray; i++) {
    sum += array[i];
  }
  return ((float) sum) / lengthOfArray;
}

float meanNoZeros(int * array, int lengthOfArray) {
  long sum = 0L;
  int len = 0;
  for (int i = 0; i < lengthOfArray; i++) {
    int temp = array[i];
    if (temp != 0) {
      sum += temp;
      len += 1;
    }
  }
  if (len == 0) {
    return 0;
  } else {
    return ((float) sum) / len;
  }
}

void hslToRgb(double h, double s, double l) {
    double r, g, b;

    if (s == 0) {
        r = g = b = l; // achromatic
    } else {
        double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        double p = 2 * l - q;
        r = hue2rgb(p, q, h + 1/3.0);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1/3.0);
    }

    rgbColors[0] = r * 255;
    rgbColors[1] = g * 255;
    rgbColors[2] = b * 255;
}

double hue2rgb(double p, double q, double t) {
    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < 1/6.0) return p + (q - p) * 6 * t;
    if(t < 1/2.0) return q;
    if(t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
    return p;
}


