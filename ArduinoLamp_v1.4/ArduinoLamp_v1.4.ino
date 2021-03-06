// =================== ВНИМАНИЕ !!! =========================
//  Почти все настройки делаются на закладке Constants.h
//  Далее ищите по вашему выбору настройки управления.
//  Почитайте там то, что на русском языке написано.
// ==========================================================
/*
  Скетч к проекту "Многофункциональный RGB светильник"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverLamp/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver, AlexGyver Technologies, 2019(Портировал на Ардуино Norovl(+ эффекты, демо от stepko365)
  https://AlexGyver.ru/
*/
// ---------------- БИБЛИОТЕКИ -----------------
#include <FastLED.h>
#include <EEPROM.h>
// ----------------- ПЕРЕМЕННЫЕ ------------------
#include "Constants.h"
#define NUM_LEDS WIDTH * HEIGHT
CRGB leds[NUM_LEDS];
boolean loadingFlag = true;
boolean ONflag = true;
byte numHold;
byte palette;
unsigned long numHold_Timer = 0;
uint32_t DemTimer = 0UL;                      // тут будет храниться время следующего переключения эффекта
//-------------------------------------------------------------
void changePower() {    // плавное включение/выключение
  if (ONflag) {
    effectsTick();
    for (int i = 0; i < Brightness[currentMode]; i += 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    FastLED.setBrightness(Brightness[currentMode]);
    delay(2);
    FastLED.show();
  } else {
    effectsTick();
    for (int i = Brightness[currentMode]; i > 8; i -= 8) {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    memset8( leds, 0, NUM_LEDS * 3);
    delay(2);
    FastLED.show();
  }
}

#if(CONTROL_TYPE == 0)
#include "IrControl.h"
#elif(CONTROL_TYPE == 1)
#include "1_BTn.h"
#elif(CONTROL_TYPE == 2)
#include "2_BTns.h"
#elif(CONTROL_TYPE == 3)
#include "3_BTns.h"
#elif(CONTROL_TYPE == 4)
#include "4_BTns.h"
#elif(CONTROL_TYPE == 5)
#include "ButtonWithIR.h"
#else
void controlTick() {return;}
void SetUP() {return;}
#endif
// ----------- ЗАПУСК ------------------
static const byte maxDim = max(WIDTH, HEIGHT);
void setup() {
  // ЛЕНТА
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(0xFFB0F0);
  FastLED.setBrightness(BRIGHTNESS);
  if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  memset8( leds, 0, NUM_LEDS * 3);
  FastLED.show();
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println();
#endif
  SetUP();
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println();
#endif
  if (EEPROM.read(0) == 102) {                    // если было сохранение настроек, то восстанавливаем их (с)НР
    currentMode = EEPROM.read(1);
    for (byte x = 0; x < MODE_AMOUNT; x++) {
      Brightness[x] = EEPROM.read(x * 3 + 11); // (2-10 байт - резерв)
      Speed[x] = EEPROM.read(x * 3 + 12);
      Scale[x] = EEPROM.read(x * 3 + 13);
    }
  }
}
void loop() {
  effectsTick();
  controlTick();
  demoTick();
}
