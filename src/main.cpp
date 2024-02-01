#include <M5StickCPlus2.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <BLEUUID.h>

#define SERVICE_PULSEOXIMETER_UUID "c360fb9d-497f-4a0d-bfd3-6cbecd1786e1" // パルスオキシメータ
#define CHARA_PO_HR_UUID "0c1f518c-ffdf-4b0f-8f2f-ca1edc6dabae"           // 心拍数
#define Descriptor "55987ddf-24d7-4db8-a4b2-2731852036cd"
#define CHARA_PO_O2_UUID "1d5b21fa-1a88-4ccb-8be8-9d8f07b0180c" // 酸素濃度

void morseLED(void *arg);
void morseDot();
void morseDash();
void morseLetterPulse();
void morseWordPulse();

void startService(BLEServer *pServer);
void startAdvertising();

void setup()
{
  M5.begin();

  Serial.begin(115200);
  delay(500);

  M5.Lcd.setRotation(3);
  M5.Lcd.setTextFont(4);
  M5.Lcd.println("Farewell World");
  M5.Lcd.println("It's CorBi");
  M5.Lcd.print("made by ");
  M5.Lcd.setTextColor(TFT_PURPLE);
  M5.Lcd.println("kiri-lab");

  BLEDevice::init("CorBi");
  BLEServer *pServer = BLEDevice::createServer();
  startService(pServer);
  startAdvertising();

  xTaskCreatePinnedToCore(morseLED, "morseTask", 4096, NULL, 1, NULL, 1);
  pinMode(19, OUTPUT);
}

void loop()
{
}

void startService(BLEServer *pServer)
{
  BLEService *pService = pServer->createService(SERVICE_PULSEOXIMETER_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARA_PO_HR_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);
  BLEDescriptor *pDescriptor = new BLEDescriptor(BLEUUID((uint16_t)0x0963)); // FIXME ハードコーディング
  // pDescriptor->setValue((uint8_t *)64, 1); // FIXME 使い方いまいち分からん
  pDescriptor->setValue("Heart Rate"); // Stringで指定ならいける
  pCharacteristic->addDescriptor(pDescriptor);

  pCharacteristic->setValue("Farewell World");
  pService->start();
}

void startAdvertising()
{
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_PULSEOXIMETER_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();
}

int timeUnit = 50;
void morseLED(void *arg)
{
  for (;;)
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
