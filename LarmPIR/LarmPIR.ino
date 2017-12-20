/*
   LarmPIR
   Saftblandare med tillhörande ljud i ingången av deckargåtan.
   2016-08-08
   Martin Hinnerson
   Fenomenmagasinet
*/
/* Pin setup */
#define pirPin 5
#define alarmPin 10

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(alarmPin, OUTPUT);
  delay(5000);
}

// All the loop does is continuously step through the trigger
//  pins to see if one is pulled low. If it is, it'll stop any
//  currently playing track, and start playing a new one.
void loop()
{
  bool pirVal = digitalRead(pirPin);
  Serial.println(pirVal);
  if (pirVal == LOW)
  {
    Serial.println("MOTION DETECTED");
    int randNumber = random(3);
    Serial.println(randNumber);
    if (randNumber == 1)
    {
      Serial.println("Random OK!");
      digitalWrite(alarmPin, HIGH); //saftblandare på
      delay(5000);
      digitalWrite(alarmPin, LOW);
    }
    delay(10000);
  }
  delay(10);
}

