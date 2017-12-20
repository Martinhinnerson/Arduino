////////////////////////////////////////////////////////MAP///////////////////////////////////////////////////

int mapToPixels() {
  currentPixels = mapFloat(decibel, -45, 0, 0, numPixels - 1); //Decibelskala
  //currentPixels = mapFloat(volts, 0, 3.3, 0, numPixels - 1); //Alternativ skala
  //Serial.println(currentPixels);
  if (currentPixels > record) {
    record = currentPixels;
  }
  return (modifiedAverage);
}
