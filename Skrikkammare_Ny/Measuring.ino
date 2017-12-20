///////////////////////////////////////////////////////Measuring///////////////////////////////////////////////

float readDecibel() {
  unsigned long startMillis = millis(); //Start of sample window
  unsigned int peakToPeak = 0; // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  //Collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(micPin);
    if (sample < 1024) //toss out spurius readings
    {
      if (sample > signalMax)
      {
        signalMax = sample; //save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample; //save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin; // max - min = peak-to-peak amplitude
  double volts = (peakToPeak * 3.3) / 1024; //convert to volts
  //Serial.println(volts);

  ///////Jämna ut läsningarna
  // subtract the last reading:
  totalVolts = totalVolts - readings[index];
  // read from the sensor:
  readings[index] = volts;
  // add the reading to the totalPixels:
  totalVolts = totalVolts + readings[index];
  // advance to the next position in the array:
  index = index + 1;

  // if we're at the end of the array...
  if (index >= numReadings)
    // ...wrap around to the beginning:
    index = 0;

  // calculate the averagePixels:
  averageVolts = totalVolts / numReadings;
  //Serial.println(averageVolts);

  int readingMaxIndex = getIndexOfMaximumValue(readings, numReadings);
  modifiedAverage = ((averageVolts*numReadings) - readings[readingMaxIndex]) / (numReadings - 1);
  //Serial.println(modifiedAverage);

  //Convert to decibel(ich)
  decibel = 20 * log10(averageVolts / 3.3);
  //Serial.println(decibel);
  modifiedDecibel = 20 * log10(modifiedAverage / 3.3);

  return (decibel);
  return (modifiedDecibel);
  return (averageVolts);
}
