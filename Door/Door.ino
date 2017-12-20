/* Door
 * Monsterdörren (motaladörren)
 * 2016-08-08
 * Martin Hinnerson
 * Joakim Andersson
 */

#include <MP3Trigger.h>

MP3Trigger trigger; // mp3 trigger

#define lock 9
#define red 11
#define hand 13
#define sensor 8

void setup() {
  // put your setup code here, to run once:
for(int i = 2; i < 7; ++i)
{
  pinMode(i, OUTPUT);
  digitalWrite(i, HIGH);
}
for(int i = 9; i < 14; ++i)
{
  pinMode(i, OUTPUT);
  digitalWrite(i, LOW);
}
pinMode(8, INPUT_PULLUP);

trigger.setup(&Serial); //setup mp3 trigger
Serial.begin( MP3Trigger::serialRate() );

}

void loop() {
  trigger.update();
  
  if (digitalRead(sensor) == 0) // if hand in slot
  {
    trigger.trigger(1); //play sound
    delay(5000);
    trigger.trigger(2);
    delay(5000);
    
    if (random(2)) // random outcome
    {
      trigger.trigger(4);
      
        digitalWrite(lock, HIGH);
        delay(6000);
        
        digitalWrite(lock, LOW);
    }
    else {
        trigger.trigger(3);
        digitalWrite(red, HIGH);
        delay(1000);
        digitalWrite(hand, HIGH);
        delay(4000);
        
        digitalWrite(red, LOW);
        digitalWrite(hand, LOW);
      }
    delay(5000);
    
  }
}
