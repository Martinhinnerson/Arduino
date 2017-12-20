/* MorseDecoder.ino
 *
 * Martin Hinnerson
 *
 * 2017-04-24
 */
/***** INCLUDES ******************************************************/
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
/***** Pin Config ****************************************************/
#define buttonPin       8       // the number of the push button pin
#define ledPin          13      // the number of the LED pin
#define sendButtonPin   10      // the number of the send button pin
#define deleteButtonPin 9       // Button to delete last character 
/***** Variables *****************************************************/43
bool ledState = HIGH;           // the current state of the output pin
bool buttonState;               // the current reading from the input pin
bool lastButtonState = LOW;     // the previous reading from the input pin
bool onState = false;
bool offState = false;
bool hasPrinted = false;
bool sendButtonState = LOW;     // if button to send string is pressed
bool oldSendButtonState = LOW;
bool deleteButtonState = LOW;
bool oldDeleteButtonState = LOW;
/***** Short and long press configuration ****************************/
int shortDelayMin = 10;
int shortDelayMax = 120;
int longDelayMin = 121;
int longDelayMax = 499;
int pauseDelay = 500;           // how fast to start on next char
/***** Button debounce configuration *********************************/
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;    // the debounce time; increase if the output flickers
long timeCounter = 0;
long onCounter = 0;
long offCounter = 0;
/***** Strings for sending and recieving *****************************/
#define maxStringLength 20
String letter;
char recievedLetters[maxStringLength];
char writtenLetters[maxStringLength];
int writeCounter = 0;
/***** DECLARATIONS **************************************************/
void printLetter(String s);
SoftwareSerial mySerial(6, 7); // Rx Tx
/***** SETUP *********************************************************/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  Serial.begin(115200);
  mySerial.begin(57600);
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sendButtonPin, INPUT);

  lcd.begin(20, 4);
  lcd.print("Skriven text:");
  lcd.setCursor(0, 2);
  lcd.print("Mottagen text:");
  lcd.setCursor(0, 1);

  // Initialize strings
  int i;
  for (i = 0; i < maxStringLength; i++)
  {
    recievedLetters[i] = ' ';
    writtenLetters[i] = ' ';
  }
}
/***** MAIN **********************************************************/
void loop()
{
  sendButtonState = digitalRead(sendButtonPin);
  deleteButtonState = digitalRead(deleteButtonPin);

  writeLetters();
  readLetters();
  updateLCD();

  if (sendButtonState && !oldSendButtonState)
  {
    sendLetters();
    oldSendButtonState = HIGH;
  }
  if (deleteButtonState && !oldDeleteButtonState)
  {
    if (writeCounter > 0)
    {
      writeCounter--;
    }
    writtenLetters[writeCounter] = ' ';
    //lcd.setCursor(writeCounter, 1);
    oldDeleteButtonState = HIGH;
  }
  if (!deleteButtonState)
  {
    oldDeleteButtonState = LOW;
  }
  if (!sendButtonState)
  {
    oldSendButtonState = LOW;
  }
}
/***** Update LCD ****************************************************/
void updateLCD()
{
  //  lcd.setCursor(0, 0);
  //  lcd.print("Skriven text:");

  //  lcd.setCursor(0, 1);
  //  lcd.print(writtenLetters);

  // lcd.setCursor(0, 3);
  //lcd.print(recievedLetters);

  // Tillagt 18-14-17, tar bort flimmer hos första raden
  int i;
  for (i = 0; i < maxStringLength; i++)
  {
    lcd.setCursor(i, 1);
    lcd.print(writtenLetters[i]);
    lcd.setCursor(i, 3);
    lcd.print(recievedLetters[i]);
  }
}
/***** READ LETTERS FROM SERIAL **************************************/
void readLetters()
{
  if (mySerial.available())
  {
    for (int j = 0; j < maxStringLength; j++)
    {
      recievedLetters[j] = ' ';
    }
    writeCounter = 0;

    delay(100);
    int i = 0;
    while (mySerial.available())
    {
      recievedLetters[i++] = mySerial.read();
    }
    //recievedLetters[i++] = '\0';
  }
}
/***** WRITE LETTERS WITH PUSHBUTTON *********************************/
void writeLetters()
{
  // read the state of the switch into a local variable:
  int reading = !digitalRead(buttonPin); //Invertera eventuellt denna beroende på hur knappen är kopplad

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  long tempMilliTime = millis();

  //Short pulse
  if ((tempMilliTime - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;

    if (buttonState == HIGH)
    {

      if (!onState)
      {
        onState = true;
        timeCounter = tempMilliTime;
      }

      onCounter = tempMilliTime;
      offState = false;
    }
    else
    {
      int timeDiff = onCounter - timeCounter;
      if (timeDiff > shortDelayMin && (timeDiff < shortDelayMax) && onState)
      {
        //Serial.println("short");
        letter += "0";
        hasPrinted = false;
      }
      else if (timeDiff > longDelayMin && onState)
      {
        //Serial.println("long");
        letter += "1";
        hasPrinted = false;
      }

      if (offState && (tempMilliTime - offCounter) > pauseDelay && !hasPrinted)
      {
        printLetter(letter);
        offState = false;
        hasPrinted = true;
      }

      if (!offState)
      {
        offState = true;
        offCounter = tempMilliTime;
      }

      onState = false;
      timeCounter = 0;
    }
  }

  // set the LED using the state of the button:
  digitalWrite(ledPin, buttonState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
/***** SEND LETTERS OVER SERIAL **************************************/
void sendLetters()
{
  mySerial.print(writtenLetters);
  Serial.print(writtenLetters);

  for (int i = 0; i < maxStringLength; i++)
  {
    writtenLetters[i] = ' ';
  }
  writeCounter = 0;

  lcd.setCursor(0, 1);
  lcd.print("Texten skickas");
  delay(100);
  lcd.print(".");
  delay(100);
  lcd.print(".");
  delay(100);
  lcd.print(".");
  delay(100);
  lcd.print(".");
  delay(100);
  lcd.print(".");
  delay(100);
  lcd.setCursor(0, 1);
  lcd.print("Texten har skickats!");
  delay(1000);

  /*
    for (int i = 0; i < maxStringLength; i++)
    {
      writtenLetters[i] = ' ';
      lcd.setCursor(i, 1);
      lcd.print(" ");
      writeCounter = 0;
    }
  */
  lcd.setCursor(0, 1);
}
/***** Clear line ****************************************************/
/*void clearLine(int line)
{
  if (line = 1)
  {
    for (int i = 0; i < maxStringLength; i++)
    {
      writtenLetters[i] = ' ';
    }
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    writeCounter = 0;
    lcd.setCursor(0, 1);
  }
}*/
/***** MAKE LETTERS FROM MORSE CODE **********************************/
void printLetter(String s)
{
  //Serial.println(s);
  double letterCode = 0.0;
  int length = s.length();
  for (int i = 0 ; length > i ; i++)
  {
    if (s.charAt(i) == '1')
    {
      letterCode += (pow(10.0, ((float)length - (float)i - 1.0)) * 2);
    }
    else
    {
      letterCode += pow(10.0, ((float)length - (float)i - 1.0));
    }
  }
  //Serial.println(letterCode);
  //Serial.println(length);
  //letterCode*=(double)length;
  //letterCode+=(double)length;
  unsigned int intLetter = letterCode;
  if (intLetter >= 100)
  {
    intLetter += 1;
  }

  //Serial.println(letterCode);
  //Serial.println(intLetter);

  char localLetter[1];
  bool correctChar = HIGH;

  switch (intLetter)
  {
    case 12:
      localLetter[0] = 'A';
      break;
    case 2111:
      localLetter[0] = 'B';
      break;
    case 2121:
      localLetter[0] = 'C';
      break;
    case 211:
      localLetter[0] = 'D';
      break;
    case 1:
      localLetter[0] = 'E';
      break;
    case 1121:
      localLetter[0] = 'F';
      break;
    case 221:
      localLetter[0] = 'G';
      break;
    case 1111:
      localLetter[0] = 'H';
      break;
    case 11:
      localLetter[0] = 'I';
      break;
    case 1222:
      localLetter[0] = 'J';
      break;
    case 212:
      localLetter[0] = 'K';
      break;
    case 1211:
      localLetter[0] = 'L';
      break;
    case 22:
      localLetter[0] = 'M';
      break;
    case 21:
      localLetter[0] = 'N';
      break;
    case 222:
      localLetter[0] = 'O';
      break;
    case 1221:
      localLetter[0] = 'P';
      break;
    case 2212:
      localLetter[0] = 'Q';
      break;
    case 121:
      localLetter[0] = 'R';
      break;
    case 111:
      localLetter[0] = 'S';
      break;
    case 2:
      localLetter[0] = 'T';
      break;
    case 112:
      localLetter[0] = 'U';
      break;
    case 1112:
      localLetter[0] = 'V';
      break;
    case 122:
      localLetter[0] = 'W';
      break;
    case 2112:
      localLetter[0] = 'X';
      break;
    case 2122:
      localLetter[0] = 'Y';
      break;
    case 2211:
      localLetter[0] = 'Z';
      break;
    case 12212:
      localLetter[0] = char(197); // Å
      break;
    case 1212:
      localLetter[0] = char(196); // Ä
      break;
    case 2221:
      localLetter[0] = char(214); // Ö
      break;
    case 12222:
      localLetter[0] = '1';
      break;
    case 11222:
      localLetter[0] = '2';
      break;
    case 11122:
      localLetter[0] = '3';
      break;
    case 11112:
      localLetter[0] = '4';
      break;
    case 11111:
      localLetter[0] = '5';
      break;
    case 21111:
      localLetter[0] = '6';
      break;
    case 22111:
      localLetter[0] = '7';
      break;
    case 22211:
      localLetter[0] = '8';
      break;
    case 22221:
      localLetter[0] = '9';
      break;
    case 22222:
      localLetter[0] = '0';
      break;
    case 121212:
      localLetter[0] = char(46); // .
      break;
    case 221122:
      localLetter[0] = char(44); // ,
      break;
    case 222111:
      localLetter[0] = char(58); // :
      break;
    case 112211:
      localLetter[0] = char(63); // ?
      break;
    case 21121:
      localLetter[0] = char(47); // /
      break;
    case 121121:
      localLetter[0] = char(148); // "
      break;
    case 12121:
      localLetter[0] = ' '; // space
      break;
    default:
      correctChar = LOW;
      localLetter[0] = ' ';
      break;
  }

  if (correctChar)
  {
    writtenLetters[writeCounter] = localLetter[0];
    writeCounter++;
    if (writeCounter >= maxStringLength)
    {
      writeCounter = 0;
    }
    Serial.print(localLetter[0]);
    //lcd.print(localLetter[0]);
  }

  letter = "";
}
/*********************************************************************/
