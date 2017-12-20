/* MorseDecoder.ino
 * 
 * Martin Hinnerson
 * 
 * 2017-04-06
 */

void strobe(int strobeFrequency, int duration)
{
  for(int i = 0; i < duration*strobeFrequency; i++)
  {
   digitalWrite(ledPin, HIGH);
   delay(500/strobeFrequency);
   digitalWrite(ledPin, LOW);
   delay(500/strobeFrequency); 
  }
}

