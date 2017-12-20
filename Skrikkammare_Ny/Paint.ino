////////////////////////////////////////////////////////////Paint//////////////////////////////////////////////

//Ritfunktion
void paintLeds(int current, int top) {
  if (current < 5) {
    current = 5;
  }
  //Stäng av alla leds över nuvarande
  for (int i = numPixels; i > current; i--) {
    strip.setPixelColor(i, off);
  }

  if (current > 80) {
    //Ruta ut leds upp till nuvarande
    for (int i = 80; i < current; i++) {
      strip.setPixelColor(i, red);
    }
    for (int i = 40; i < 80; i++) {
      strip.setPixelColor(i, yellow);
    }
    for (int i = 0; i < 40; i++) {
      strip.setPixelColor(i, green);
    }
  } else if (current > 40) {
    //Ruta ut leds upp till nuvarande
    for (int i = 40; i < current; i++) {
      strip.setPixelColor(i, yellow);
    }
    for (int i = 0; i < 40; i++) {
      strip.setPixelColor(i, green);
    }
  } else {
    //Ruta ut leds upp till nuvarande
    for (int i = 0; i < current; i++) {
      strip.setPixelColor(i, green);
    }
  }

  strip.setPixelColor(record, purple);
  strip.show();
}
