// Если вы хотите добавить эффекты или сделать им копии для демонстрации на разных настройках, нужно делать это в 5 местах:
// 1. в файле effects.ino - добавляется программный код самого эффекта.
// 2. В Constants.h указывается общее количество MODE_AMOUNT.
// 3. здесь в файле effectTicker.ino - подключается процедура вызова эффекта case"номер": "назва эффекта"; break; 
//    Можно подключать один и тот же эффект под разными номерами. Но это уже слишком.
uint32_t effTimer; byte ind;
void effectsTick() {
  {
    if (ONflag && millis() - effTimer >= ((currentMode < 3 || currentMode > 6) ? 256 - Speed[currentMode] : 50) ) {
      effTimer = millis(); switch (currentMode) {
        //|номер   |название функции эффекта     |тоже надо|
        case 0 : sparklesRoutine();             break;
        case 1 : RainbowRoutine();              break;
        case 2 : FireRoutine();                 break;//Новый-Fire.. Старый fire...
        case 3 : LavaLampRoutine();             break;
        case 4 : Noise3D();                     break;
        case 5 : whiteLampRoutine();            break;
        case 6 : colorRoutine();                break;
        case 7 : colorsRoutine();               break;
        case 8 : matrixRoutine();               break;
        case 9 : RainRoutine();                 break;
        case 10: stormRoutine();                break;
        case 11: ballRoutine();                 break;
        case 12: ballsRoutine();                break;
        case 13: LLandRoutine();                break;
      }
#ifdef INDICATOR
   #if (ROATRE)
      switch (numHold) {    // индикатор уровня яркости/скорости/масштаба
        case 1:
          ind = sqrt(Brightness[currentMode] + 1);
          for (byte x = 0; x < HEIGHT ; x++) {
            if (ind > x) drawPixelXY(x, IND_POS, CHSV(10, 255, 255));
            else drawPixelXY(x, IND_POS,  0);
          }
          break;
        case 2:
          ind = sqrt(Speed[currentMode] + 1);
          for (byte x = 0; x < WIDTH ; x++) {
            if (ind > x) drawPixelXY(x, IND_POS, CHSV(100, 255, 255));
            else drawPixelXY(x, IND_POS,  0);
          }
          break;
        case 3:
          ind = sqrt(Scale[currentMode] + 1);
          for (byte x = 0; x < WIDTH ; x++) {
            if (ind > x) drawPixelXY(x, IND_POS, CHSV(150, 255, 255));
            else drawPixelXY(x, IND_POS,  0);
          }
          break;}
          #else
          switch (numHold) {    // индикатор уровня яркости/скорости/масштаба
        case 1:
          ind = sqrt(Brightness[currentMode] + 1);
          for (byte y = 0; y < HEIGHT ; y++) {
            if (ind > y) drawPixelXY(IND_POS, y, CHSV(10, 255, 255));
            else drawPixelXY(IND_POS, y,  0);
          }
          break;
        case 2:
          ind = sqrt(Speed[currentMode] + 1);
          for (byte y = 0; y <= HEIGHT ; y++) {
            if (ind > y) drawPixelXY(IND_POS, y, CHSV(100, 255, 255));
            else drawPixelXY(IND_POS, y,  0);
          }
          break;
        case 3:
          ind = sqrt(Scale[currentMode] + 1);
          for (byte y = 0; y < HEIGHT ; y++) {
            if (ind > y) drawPixelXY(IND_POS, y, CHSV(150, 255, 255));
            else drawPixelXY(IND_POS, y,  0);
          }
          break;}
          #endif
#endif
#if (CONTROL_TYPE == 0 || CONTROL_TYPE == 5)
      if (!IRLremote.receiving())    // если на ИК приёмник не приходит сигнал (без этого НЕ РАБОТАЕТ!)
        FastLED.show();
#else
      FastLED.show();
#endif
    }
  }
}

void demoTick() {
  if (isDemo && ONflag && millis() >= DemTimer) {
    #ifdef RANDOM_DEMO
      currentMode = random8(MODE_AMOUNT); // если нужен следующий случайный эффект
    #else
      currentMode = currentMode + 1U < MODE_AMOUNT ? currentMode + 1U : 0U; // если нужен следующий по списку эффект
    #endif
    #ifdef RANDOM_EFF
      Speed[currentMode] = random8(); Scale[currentMode] = random8();
    #endif  
    memset8( leds, 0, NUM_LEDS * 3);
    DemTimer = millis() + DEMOT*1000;
    loadingFlag = true;
  }
}
