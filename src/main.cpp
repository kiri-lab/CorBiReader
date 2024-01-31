#include <M5StickCPlus2.h>
#include <MAX30100_PulseOximeter.h>

void pulseOximeter(void *arg);

void morseLED(void *arg);
void morseDot();
void morseDash();
void morseLetterPulse();
void morseWordPulse();

#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
uint32_t tsLastReport = 0;

void setup()
{
  M5.begin();

  Serial.begin(115200);
  delay(500);

  if (!pox.begin())
  {
    Serial.println("FAILED");
  }
  else
  {
    Serial.println("SUCCESS");
  }

  M5.Lcd.setRotation(3);
  M5.Lcd.setTextFont(4);
  M5.Lcd.println("Farewell World");
  M5.Lcd.println("It's CorBi");
  M5.Lcd.print("made by ");
  M5.Lcd.setTextColor(TFT_PURPLE, TFT_BLACK);
  M5.Lcd.println("kiri-lab");
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.println("HR");
  M5.Lcd.println("O2");

  // xTaskCreatePinnedToCore(morseLED, "morseTask", 4096, NULL, 1, NULL, 1);
  // xTaskCreatePinnedToCore(pulseOximeter, "MAX30100", 4096, NULL, 2, NULL, 1);
  pinMode(19, OUTPUT);
}

void loop()
{
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  {
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setCursor(40, 80);
    M5.Lcd.print(pox.getHeartRate());

    M5.Lcd.setCursor(40, 100);
    M5.Lcd.print(pox.getSpO2());

    tsLastReport = millis();
  }
}

void pulseOximeter(void *arg)
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
