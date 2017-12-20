/*
 * Saftblandare i ingången av deckargåtan.
 * 2017-04-28
 * Martin Hinnerson
 * Fenomenmagasinet
 */


/* Pin setup */
#define pirPin 5
#define alarmPin 10

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  delay(2000);
}

void loop()
{
  digitalWrite(alarmPin, HIGH);
  delay(2000);
  digitalWrite(alarmPin, LOW);
  delay(2000);
  
  //bool pirVal = digitalRead(pirPin);
  /*if (pirVal == LOW)
  {
    Serial.println("MOTION DETECTED");
    int randNumber = random(3);
    Serial.println(randNumber);
    if (randNumber == 1)
    {
      Serial.println("Random OK!");
      digitalWrite(alarmPin, HIGH); //saftblandare på
      delay(3000);
      digitalWrite(alarmPin, LOW); //saftblandare av
    }
    delay(10000);
 }*/
}

