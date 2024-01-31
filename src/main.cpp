#include <M5StickCPlus2.h>

void morseLED(void *arg);
void morseDot();
void morseDash();
void morseLetterPulse();
void morseWordPulse();

void setup()
{
  M5.begin();

  Serial.begin(115200);
  delay(500);

  M5.Lcd.print("Farewell World\n");
  M5.Lcd.print("It's CorBi\n");
  M5.Lcd.print("made by kiri-lab\n");

  xTaskCreatePinnedToCore(morseLED, "morseTask", 4096, NULL, 1, NULL, 1);
  pinMode(19, OUTPUT);
}

void loop()
{
}

int timeUnit = 50;
void morseLED(void *arg)
{
  morseDash();
  morseDash();
  morseLetterPulse(); // m
  morseDot();
  morseDash();
  morseLetterPulse(); // a
  morseDash();
  morseDot();
  morseDot();
  morseLetterPulse(); // d
  morseDot();
  // e
  morseWordPulse(); // space
  // by
  morseDash();
  morseDot();
  morseDot();
  morseDot();
  morseLetterPulse(); // b
  morseDash();
  morseDot();
  morseDash();
  morseDash();
  // y
  morseWordPulse(); // space
  // kiri
  morseDash();
  morseDot();
  morseDash();
  morseLetterPulse(); // k
  morseDot();
  morseDot();
  morseLetterPulse(); // i
  morseDot();
  morseDash();
  morseDot();
  morseLetterPulse(); // r
  morseDot();
  morseDot();
  morseLetterPulse(); // i
  morseDash();
  morseDot();
  morseDot();
  morseDot();
  morseDot();
  morseDash();
  morseLetterPulse(); // -
  morseDot();
  morseDash();
  morseDot();
  morseDot();
  morseLetterPulse(); // l
  morseDot();
  morseDash();
  morseLetterPulse(); // a
  morseDash();
  morseDot();
  morseDot();
  morseDot();
  // b
  morseWordPulse(); // space
}

void morseDot()
{
  digitalWrite(19, HIGH);
  delay(timeUnit);
  digitalWrite(19, LOW);
  delay(timeUnit);
}

void morseDash()
{
  digitalWrite(19, HIGH);
  delay(timeUnit * 3);
  digitalWrite(19, LOW);
  delay(timeUnit);
}

void morseLetterPulse()
{
  delay(timeUnit * 3);
}

void morseWordPulse()
{
  delay(timeUnit * 7);
}
