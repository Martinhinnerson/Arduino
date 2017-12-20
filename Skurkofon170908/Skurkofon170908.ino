/* Skurkofon
   2017-09-08
   Martin Hinnerson
   Fenomenmagasinet
*/

#include <Keypad.h>
#include <MP3Trigger.h>

MP3Trigger trigger;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {7, 8, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 12, 13}; //connect to the column pinouts of the keypad

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char number[11] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0'};
char correctNumber[] = "0709974237";
int numberCounter = 0;

bool keyPressed = LOW;

#define ledpin 6 //led på knappsats
#define offpin 5 //brytare för att lägga på

void setup()
{
  pinMode(ledpin, OUTPUT);
  pinMode(offpin, INPUT);
  digitalWrite(ledpin, HIGH);
  Serial.begin(9600);

  trigger.setup(&Serial1);
  Serial1.begin(MP3Trigger::serialRate());
  delay(2000);
}

void loop() {
  trigger.update();
  if (digitalRead(offpin) == LOW)
  {
    numberCounter = 0;
    trigger.stop();
    // Stoppa rington
    // Luren är nere
    // trigger.trigger(19);
    digitalWrite(ledpin, LOW);
    trigger.setLooping(false,18);
    delay(10);
    trigger.update();
  }
  else
  {
    // Luren är lyft
    digitalWrite(ledpin, HIGH);
    if(numberCounter == 0)
    {
      //Starta ringtone
      trigger.setLooping(true, 18);
    }
    char key = kpd.getKey();
    if (key)
    {
      // Stoppa loopen av dialtone
      trigger.setLooping(false,18);
      delay(10);
      digitalWrite(ledpin, LOW);
      //trigger.trigger(19); //tyst
      trigger.update();
      delay(10);
      triggButton(key);
      //Skifta allt vänster och lägg till knapp till höger
      for (int i = 0; i < 9; i++)
      {
        number[i] = number[i + 1];
      }
      number[9] = key;
      numberCounter++;
      // delay(50);
    }

    if (numberCounter == 10)
    {
      Serial.println(number);
      trigger.update();
      //7 siffror har lästs
      delay(500);
      trigger.trigger(12); //ring-ljud
      delay(2000);
      numberCounter = 0;
      //Spela ljud beroende på nummer
      /*
         Kontroll av nummer här! Lägg till satser för olika nummer. Ev formel beroende på vilka fel. (ljudfiler med namn 13 och uppåt)
        13 - rätt nummer
        14-17 - fel nummer
      */
      if (!strcmp(number, correctNumber))
      {
        Serial.println("OK");
        trigger.trigger(15);
      }
      else
      {
        if (number[3] != correctNumber[3] || number[4] != correctNumber[4])
        {
          trigger.trigger(13);
        }
        else if (number[5] != correctNumber[5] || number[6] != correctNumber[6])
        {
          trigger.trigger(14);
        }
        else if (number[7] != correctNumber[7] || number[8] != correctNumber[8])
        {
          trigger.trigger(16);
        }
        else if (number[9] != correctNumber[9])
        {
          trigger.trigger(17);
        }
        else
        {
          int randomNum = random(14, 17);
          if(randomNum = 15){
            randomNum = 14;
          }
          trigger.trigger(randomNum);
        }
        Serial.println("FEL");
      }
      blink(20);
    }
  }
}

void triggButton(char key)
{
  switch (key) //Ljud för de olika knapptrycken (0-11)
  {
    case '0': trigger.trigger(0);
      break;
    case '1': trigger.trigger(1);
      break;
    case '2': trigger.trigger(2);
      break;
    case '3': trigger.trigger(3);
      break;
    case '4': trigger.trigger(4);
      break;
    case '5': trigger.trigger(5);
      break;
    case '6': trigger.trigger(6);
      break;
    case '7': trigger.trigger(7);
      break;
    case '8': trigger.trigger(8);
      break;
    case '9': trigger.trigger(9);
      break;
    case '*': trigger.trigger(10);
      break;
    case '#': trigger.trigger(11);
      break;
  }
  trigger.update();
}

//Enkel blinkfunktion
void blink(int duration)
{
  for (int i = 0; i < 10 * duration / 2; i++)
  {
    trigger.update();
    if (digitalRead(offpin) == LOW)
    {
      break;
    }
    digitalWrite(ledpin, LOW);
    delay(100);
    digitalWrite(ledpin, HIGH);
    delay(100);
  }
}

