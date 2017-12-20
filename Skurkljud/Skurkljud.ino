#include <MP3Trigger.h>

MP3Trigger trigger;

#define numButtons 5

byte answerButtons[] = {2, 3, 4, 5, 6};
byte voiceButtons[] = {7, 8, 9, 10, 11};

void setup()
{
  for (int i = 0; i < numButtons; i++)
  {
    pinMode(answerButtons[i], INPUT);
    pinMode(voiceButtons[i], INPUT);
  }

  Serial.begin(9600);

  trigger.setup(&Serial1);
  Serial1.begin(MP3Trigger::serialRate());
}

void loop()
{
  trigger.update();
  for (int i = 0; i < numButtons; i++)
  {
    if (digitalRead(answerButtons[i]) == HIGH)
    {
      trigger.trigger(i);
      break;
    }
    if (digitalRead(voiceButtons[i]) == HIGH)
    {
      trigger.trigger(5+i);
      break;
    }
  }
}
