// ================================= ЭФФЕКТЫ =====================================
// --------------------------------- конфетти ------------------------------------
#define FADE_OUT_SPEED        (70U)                         // скорость затухания
//--------------------------Шторм,Метель------------------------------------------
#define SNOW_DENSE (32U) // плотность снега - меньше = плотнее
#define TAIL_STEP (127U) // длина хвоста
//-------------------Светлячки со шлейфом-----------------------------------------
#define BALLS_AMOUNT          (3U)     // количество "шариков"
#define CLEAR_PATH            (1U)     // очищать путь
#define TRACK_STEP            (70U)    // длина хвоста шарика (чем больше цифра, тем хвост короче)
int16_t coord[BALLS_AMOUNT][2U];
int8_t vector[BALLS_AMOUNT][2U];
CRGB ballColors[BALLS_AMOUNT];
//===================Коды эффектов==============================================
uint8_t deltaHue, deltaHue2; // ещё пара таких же, когда нужно много
uint8_t deltaValue; // просто повторно используемая переменная
byte hue, hue2;
CRGB _pulse_color;
void blurScreen(fract8 blur_amount, CRGB *LEDarray = leds)
{
  blur2d(LEDarray, WIDTH, HEIGHT, blur_amount);
}
extern const TProgmemRGBPalette16 WaterfallColors_p FL_PROGMEM = {0x000000, 0x060707, 0x101110, 0x151717, 0x1C1D22, 0x242A28, 0x363B3A, 0x313634, 0x505552, 0x6B6C70, 0x98A4A1, 0xC1C2C1, 0xCACECF, 0xCDDEDD, 0xDEDFE0, 0xB2BAB9};
static const TProgmemRGBPalette16 ZeebraColors_p FL_PROGMEM = {CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black};
static const TProgmemRGBPalette16 HeatColors2_p FL_PROGMEM = {0x000000, 0x330000, 0x660000, 0x990000, 0xCC0000, 0xFF0000, 0xFF3300, 0xFF6600, 0xFF9900, 0xFFCC00, 0xFFFF00, 0xFFFF33, 0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF};
static const TProgmemRGBPalette16 WoodFireColors_p FL_PROGMEM = {CRGB::Black, 0x330e00, 0x661c00, 0x992900, 0xcc3700, CRGB::OrangeRed, 0xff5800, 0xff6b00, 0xff7f00, 0xff9200, CRGB::Orange, 0xffaf00, 0xffb900, 0xffc300, 0xffcd00, CRGB::Gold};             //* Orange
static const TProgmemRGBPalette16 NormalFire_p FL_PROGMEM = {CRGB::Black, 0x330000, 0x660000, 0x990000, 0xcc0000, CRGB::Red, 0xff0c00, 0xff1800, 0xff2400, 0xff3000, 0xff3c00, 0xff4800, 0xff5400, 0xff6000, 0xff6c00, 0xff7800};                             // пытаюсь сделать что-то более приличное
static const TProgmemRGBPalette16 NormalFire2_p FL_PROGMEM = {CRGB::Black, 0x560000, 0x6b0000, 0x820000, 0x9a0011, CRGB::FireBrick, 0xc22520, 0xd12a1c, 0xe12f17, 0xf0350f, 0xff3c00, 0xff6400, 0xff8300, 0xffa000, 0xffba00, 0xffd400};                      // пытаюсь сделать что-то более приличное
static const TProgmemRGBPalette16 LithiumFireColors_p FL_PROGMEM = {CRGB::Black, 0x240707, 0x470e0e, 0x6b1414, 0x8e1b1b, CRGB::FireBrick, 0xc14244, 0xd16166, 0xe08187, 0xf0a0a9, CRGB::Pink, 0xff9ec0, 0xff7bb5, 0xff59a9, 0xff369e, CRGB::DeepPink};        //* Red
static const TProgmemRGBPalette16 SodiumFireColors_p FL_PROGMEM = {CRGB::Black, 0x332100, 0x664200, 0x996300, 0xcc8400, CRGB::Orange, 0xffaf00, 0xffb900, 0xffc300, 0xffcd00, CRGB::Gold, 0xf8cd06, 0xf0c30d, 0xe9b913, 0xe1af1a, CRGB::Goldenrod};           //* Yellow
static const TProgmemRGBPalette16 CopperFireColors_p FL_PROGMEM = {CRGB::Black, 0x001a00, 0x003300, 0x004d00, 0x006600, CRGB::Green, 0x239909, 0x45b313, 0x68cc1c, 0x8ae626, CRGB::GreenYellow, 0x94f530, 0x7ceb30, 0x63e131, 0x4bd731, CRGB::LimeGreen};     //* Green
static const TProgmemRGBPalette16 AlcoholFireColors_p FL_PROGMEM = {CRGB::Black, 0x000033, 0x000066, 0x000099, 0x0000cc, CRGB::Blue, 0x0026ff, 0x004cff, 0x0073ff, 0x0099ff, CRGB::DeepSkyBlue, 0x1bc2fe, 0x36c5fd, 0x51c8fc, 0x6ccbfb, CRGB::LightSkyBlue};  //* Blue
static const TProgmemRGBPalette16 RubidiumFireColors_p FL_PROGMEM = {CRGB::Black, 0x0f001a, 0x1e0034, 0x2d004e, 0x3c0068, CRGB::Indigo, CRGB::Indigo, CRGB::Indigo, CRGB::Indigo, CRGB::Indigo, CRGB::Indigo, 0x3c0084, 0x2d0086, 0x1e0087, 0x0f0089, CRGB::DarkBlue};        //* Indigo
static const TProgmemRGBPalette16 PotassiumFireColors_p FL_PROGMEM = {CRGB::Black, 0x0f001a, 0x1e0034, 0x2d004e, 0x3c0068, CRGB::Indigo, 0x591694, 0x682da6, 0x7643b7, 0x855ac9, CRGB::MediumPurple, 0xa95ecd, 0xbe4bbe, 0xd439b0, 0xe926a1, CRGB::DeepPink}; //* Violet
const TProgmemRGBPalette16 *palette_arr[] = {
  &PartyColors_p,
  &OceanColors_p,
  &LavaColors_p,
  &HeatColors_p,
  &WaterfallColors_p,
  &CloudColors_p,
  &ForestColors_p,
  &RainbowColors_p,
  &RainbowStripeColors_p,
  &ZeebraColors_p,
  &NormalFire_p,
  &HeatColors2_p,
  &NormalFire2_p,
  &CopperFireColors_p,
  &SodiumFireColors_p,
  &PotassiumFireColors_p,
  &RubidiumFireColors_p,
  &AlcoholFireColors_p,
  &LithiumFireColors_p,
  &WoodFireColors_p,
};
const TProgmemRGBPalette16 *curPalette = palette_arr[0];
void setCurrentPalette(uint8_t palIdx) {
  curPalette = palette_arr[palIdx];
}
// --------------------------------- конфетти ------------------------------------
void sparklesRoutine()
{
  for (uint8_t i = 0; i < modes[currentMode].Scale; i++)
  {
    uint8_t x = random(0U, WIDTH);
    uint8_t y = random(0U, HEIGHT);
    if (getPixColorXY(x, y) == 0U)
    {
      drawPixelXY(x, y, CHSV(random(0U, 255U), 255U, 255U));
    }
  }
  fader(FADE_OUT_SPEED);
}
// функция плавного угасания цвета для всех пикселей
void fader(uint8_t step)
{
  for (uint8_t i = 0U; i < WIDTH; i++)
  {
    for (uint8_t j = 0U; j < HEIGHT; j++)
    {
      fadePixel(i, j, step);
    }
  }
}
void fadePixel(uint8_t i, uint8_t j, uint8_t step)          // новый фейдер
{
  int32_t pixelNum = XY(i, j);
  if (getPixColor(pixelNum) == 0U) return;

  if (leds[pixelNum].r >= 30U ||
      leds[pixelNum].g >= 30U ||
      leds[pixelNum].b >= 30U)
  {
    leds[pixelNum].fadeToBlackBy(step);
  }
  else
  {
    leds[pixelNum] = 0U;
  }
}

// радуги 2D
// ------------- Pадуга вертикальная/горизонтальная ----------------
void rainbowHorVertRoutine(bool isVertical)
{ hue + 4;
  for (uint8_t i = 0U; i < (isVertical ? WIDTH : HEIGHT); i++)
  {
    CHSV thisColor = CHSV((uint8_t)(hue + i * modes[currentMode].Scale % 170), 255, 255);
    for (uint8_t j = 0U; j < (isVertical ? HEIGHT : WIDTH); j++)
    {
      drawPixelXY((isVertical ? i : j), (isVertical ? j : i), thisColor);
    }
  }
}

// ------------- Радуга диагональная -------------
void RainbowRoutine()
{
  if (modes[currentMode].Scale < 85) {
    rainbowHorVertRoutine(false);
  } else if (modes[currentMode].Scale > 170) {
    rainbowHorVertRoutine(true);
  } else {
    hue + 8;
    for (uint8_t i = 0U; i < WIDTH; i++)
    {
      for (uint8_t j = 0U; j < HEIGHT; j++)
      {
        float twirlFactor = fmap((float)modes[currentMode].Scale, 85, 170, 8.3, 24);      // на сколько оборотов будет закручена матрица, [0..3]
        CRGB thisColor = CHSV((uint8_t)(hue + ((float)WIDTH / HEIGHT * i + j * twirlFactor) * ((float)255 / maxDim)), 255, 255);
        drawPixelXY(i, j, thisColor);
      }
    }
  }
}

// ---------------------------------------- ЦВЕТА -----------------------------
void colorsRoutine() {
  hue += modes[currentMode].Scale;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue, 255, 255);
  }
}

// --------------------------------- ЦВЕТ ------------------------------------
void colorRoutine() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(modes[currentMode].Scale * 2.5, modes[currentMode].Speed * 2.5, 255);
  }
}

// ------------------------------ снегопад 2.5 --------------------------------
void snowRoutine() {
  shiftDown();

  for (byte x = 0; x < WIDTH; x++) {
    // заполняем случайно верхнюю строку
    // а также не даём двум блокам по вертикали вместе быть
    if (getPixColorXY(x, HEIGHT - 2) == 0 && (random(0, modes[currentMode].Scale) == 0))
      drawPixelXY(x, HEIGHT - 1U, CHSV(0, 0, random(50, 255)));
    else
      drawPixelXY(x, HEIGHT - 1, 0x000000);
  }
}

// ------------------------------ МАТРИЦА ------------------------------
void matrixRoutine()
{
  for (uint8_t x = 0U; x < WIDTH; x++)
  {
    // обрабатываем нашу матрицу снизу вверх до второй сверху строчки
    for (uint8_t y = 0U; y < HEIGHT - 1U; y++)
    {
      uint32_t thisColor = getPixColorXY(x, y);                                              // берём цвет нашего пикселя
      uint32_t upperColor = getPixColorXY(x, y + 1U);                                        // берём цвет пикселя над нашим
      if (upperColor >= 0x900000 && random(7 * HEIGHT) != 0U)                  // если выше нас максимальная яркость, игнорим этот факт с некой вероятностью или опускаем цепочку ниже
        drawPixelXY(x, y, upperColor);
      else if (thisColor == 0U && random((100 - modes[currentMode].Scale) * HEIGHT) == 0U)  // если наш пиксель ещё не горит, иногда зажигаем новые цепочки
        //else if (thisColor == 0U && random((100 - modes[currentMode].Scale) * HEIGHT*3) == 0U)  // для длинных хвостов
        drawPixelXY(x, y, 0x9bf800);
      else if (thisColor <= 0x050800)                                                        // если наш пиксель почти погас, стараемся сделать затухание медленней
      {
        if (thisColor >= 0x030000)
          drawPixelXY(x, y, 0x020300);
        else if (thisColor != 0U)
          drawPixelXY(x, y, 0U);
      }
      else if (thisColor >= 0x900000)                                                        // если наш пиксель максимальной яркости, резко снижаем яркость
        drawPixelXY(x, y, 0x558800);
      else
        drawPixelXY(x, y, thisColor - 0x0a1000);                                             // в остальных случаях снижаем яркость на 1 уровень
      //drawPixelXY(x, y, thisColor - 0x050800);                                             // для длинных хвостов
    }
    // аналогично обрабатываем верхний ряд пикселей матрицы
    uint32_t thisColor = getPixColorXY(x, HEIGHT - 1U);
    if (thisColor == 0U)                                                                     // если наш верхний пиксель не горит, заполняем его с вероятностью .Scale
    {
      if (random(100 - modes[currentMode].Scale) == 0U)
        drawPixelXY(x, HEIGHT - 1U, 0x9bf800);
    }
    else if (thisColor <= 0x050800)                                                          // если наш верхний пиксель почти погас, стараемся сделать затухание медленней
    {
      if (thisColor >= 0x030000)
        drawPixelXY(x, HEIGHT - 1U, 0x020300);
      else
        drawPixelXY(x, HEIGHT - 1U, 0U);
    }
    else if (thisColor >= 0x900000)                                                          // если наш верхний пиксель максимальной яркости, резко снижаем яркость
      drawPixelXY(x, HEIGHT - 1U, 0x558800);
    else
      drawPixelXY(x, HEIGHT - 1U, thisColor - 0x0a1000);                                     // в остальных случаях снижаем яркость на 1 уровень
    //drawPixelXY(x, HEIGHT - 1U, thisColor - 0x050800);                                     // для длинных хвостов
  }
}


// ------------- белый свет (светится горизонтальная полоса по центру лампы; масштаб - высота центральной горизонтальной полосы; скорость - регулировка от холодного к тёплому; яркость - общая яркость) -------------
// mod by @Fruity
void whiteLampRoutine()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    FastLED.clear();
    //delay(1);

    uint8_t centerY =  (uint8_t)round(HEIGHT / 2.0F) - 1U;// max((uint8_t)round(HEIGHT / 2.0F) - 1, 0); нахрена тут максимум было вычислять? для ленты?!
    uint8_t bottomOffset = (uint8_t)(!(HEIGHT & 0x01));// && (HEIGHT > 1)); и высота больше единицы. супер!                     // если высота матрицы чётная, линий с максимальной яркостью две, а линии с минимальной яркостью снизу будут смещены на один ряд

    uint8_t fullRows =  centerY / 100.0 * modes[currentMode].Scale;
    uint8_t iPol = (centerY / 100.0 * modes[currentMode].Scale - fullRows) * 255;

    for (int16_t y = centerY; y >= 0; y--)
    {
      CRGB color = CHSV(
                     45U,                                                                              // определяем тон
                     map(modes[currentMode].Speed, 0U, 255U, 0U, 170U),                                // определяем насыщенность
                     y > (centerY - fullRows - 1)                                                      // определяем яркость
                     ? 255U                                                                            // для центральных горизонтальных полос
                     : iPol * (y > centerY - fullRows - 2));  // для остальных горизонтальных полос яркость равна либо 255, либо 0 в зависимости от масштаба

      for (uint8_t x = 0U; x < WIDTH; x++)
      {
        drawPixelXY(x, y, color);                              // при чётной высоте матрицы максимально яркими отрисуются 2 центральных горизонтальных полосы
        drawPixelXY(x, HEIGHT + bottomOffset - y - 2U, color); // при нечётной - одна, но дважды
      }
    }
  }
}

//--------------------------Шторм,Метель-------------------------
void stormRoutine() {
  // заполняем головами комет левую и верхнюю линию
  for (byte i = HEIGHT / 2; i < HEIGHT; i++) {
    if (getPixColorXY(0, i) == 0
        && (random(0, SNOW_DENSE) == 0)
        && getPixColorXY(0, i + 1) == 0
        && getPixColorXY(0, i - 1) == 0)
      leds[getPixelNumber(0, i)] = CHSV(random(0, 200), modes[currentMode].Scale, 255);
  }
  for (byte i = 0; i < WIDTH / 2; i++) {
    if (getPixColorXY(i, HEIGHT - 1) == 0
        && (random(0, SNOW_DENSE) == 0)
        && getPixColorXY(i + 1, HEIGHT - 1) == 0
        && getPixColorXY(i - 1, HEIGHT - 1) == 0)
      leds[getPixelNumber(i, HEIGHT - 1)] = CHSV(random(0, 200), modes[currentMode].Scale, 255);
  }

  // сдвигаем по диагонали
  for (byte y = 0; y < HEIGHT - 1; y++) {
    for (byte x = WIDTH - 1; x > 0; x--) {
      drawPixelXY(x, y, getPixColorXY(x - 1, y + 1));
    }
  }

  // уменьшаем яркость левой и верхней линии, формируем "хвосты"
  for (byte i = HEIGHT / 2; i < HEIGHT; i++) {
    fadePixel(0, i, 120);
  }
  for (byte i = 0; i < WIDTH / 2; i++) {
    fadePixel(i, HEIGHT - 1, TAIL_STEP);
  }
}

//-------------------------Блуждающий кубик-----------------------
int16_t coordB[2U];
int8_t vectorB[2U];
CRGB ballColor;

void ballRoutine()
{
  if (loadingFlag)
  {
    loadingFlag = false;

    if (modes[currentMode].Scale <= 85)
      deltaValue = map(modes[currentMode].Scale, 1, 85, 1U, max((uint8_t)min(WIDTH, HEIGHT) / 3, 1));
    else if (modes[currentMode].Scale > 85 and modes[currentMode].Scale <= 170)
      deltaValue = map(modes[currentMode].Scale, 170, 86, 1U, max((uint8_t)min(WIDTH, HEIGHT) / 3, 1));
    else
      deltaValue = map(modes[currentMode].Scale, 171, 255, 1U, max((uint8_t)min(WIDTH, HEIGHT) / 3, 1));

    for (uint8_t i = 0U; i < 2U; i++)
    {
      coordB[i] = WIDTH / 2 * 10;
      vectorB[i] = random(8, 20);
    }
    ballColor = CHSV(random(0, 9) * 28, 255U, 255U);
  }


  if ((modes[currentMode].Scale & 0x01))
    for (uint8_t i = 0U; i < deltaValue; i++)
      for (uint8_t j = 0U; j < deltaValue; j++)
        leds[XY(coordB[0U] / 10 + i, coordB[1U] / 10 + j)] = _pulse_color;

  for (uint8_t i = 0U; i < 2U; i++)
  {
    coordB[i] += vectorB[i];
    if (coordB[i] < 0)
    {
      coordB[i] = 0;
      vectorB[i] = -vectorB[i];
      ballColor = CHSV(random(0, 9) * 28, 255U, 255U);

    }
  }
  if (coordB[0U] > (int16_t)((WIDTH - deltaValue) * 10))
  {
    coordB[0U] = (WIDTH - deltaValue) * 10;
    vectorB[0U] = -vectorB[0U];
    ballColor = CHSV(random(0, 9) * 28, 255U, 255U);

  }
  if (coordB[1U] > (int16_t)((HEIGHT - deltaValue) * 10))
  {
    coordB[1U] = (HEIGHT - deltaValue) * 10;
    vectorB[1U] = -vectorB[1U];
    ballColor = CHSV(random(0, 9) * 28, 255U, 255U);

  }

  if (modes[currentMode].Scale <= 85)  // при масштабе до 85 выводим кубик без шлейфа
    memset8( leds, 0, NUM_LEDS * 3);
  else if (modes[currentMode].Scale > 85 and modes[currentMode].Scale <= 170)
    fadeToBlackBy(leds, NUM_LEDS, 255 - (10 * (modes[currentMode].Speed) / 255) + 30); // выводим кубик со шлейфом, длинна которого зависит от скорости.
  else
    fadeToBlackBy(leds, NUM_LEDS, 255 - (10 * (modes[currentMode].Speed) / 255) + 15); // выводим кубик с длинным шлейфом, длинна которого зависит от скорости.


  for (uint8_t i = 0U; i < deltaValue; i++)
    for (uint8_t j = 0U; j < deltaValue; j++)
      leds[XY(coordB[0U] / 10 + i, coordB[1U] / 10 + j)] = ballColor;
}

//-------------------Светлячки со шлейфом----------------------------
void ballsRoutine()
{
  if (loadingFlag)
  {
    loadingFlag = false;

    for (uint8_t j = 0U; j < BALLS_AMOUNT; j++)
    {
      int8_t sign;
      // забиваем случайными данными
      coord[j][0U] = WIDTH / 2 * 10;
      random(0, 2) ? sign = 1 : sign = -1;
      vector[j][0U] = random(4, 15) * sign;
      coord[j][1U] = HEIGHT / 2 * 10;
      random(0, 2) ? sign = 1 : sign = -1;
      vector[j][1U] = random(4, 15) * sign;
      //ballColors[j] = CHSV(random(0, 9) * 28, 255U, 255U);
      // цвет зависит от масштаба
      ballColors[j] = CHSV((modes[currentMode].Scale * (j + 1)) % 256U, 255U, 255U);
    }
  }

  fader(TRACK_STEP);

  // движение шариков
  for (uint8_t j = 0U; j < BALLS_AMOUNT; j++)
  {
    // движение шариков
    for (uint8_t i = 0U; i < 2U; i++)
    {
      coord[j][i] += vector[j][i];
      if (coord[j][i] < 0)
      {
        coord[j][i] = 0;
        vector[j][i] = -vector[j][i];
      }
    }

    if (coord[j][0U] > (int16_t)((WIDTH - 1) * 10))
    {
      coord[j][0U] = (WIDTH - 1) * 10;
      vector[j][0U] = -vector[j][0U];
    }
    if (coord[j][1U] > (int16_t)((HEIGHT - 1) * 10))
    {
      coord[j][1U] = (HEIGHT - 1) * 10;
      vector[j][1U] = -vector[j][1U];
    }
    leds[XY(coord[j][0U] / 10, coord[j][1U] / 10)] =  ballColors[j];
  }
}

// -------------------------------------- огонь ---------------------------------------------
unsigned char matrixValue[8][16];
// эффект "огонь"
#define SPARKLES 1        // вылетающие угольки вкл выкл
unsigned char line[WIDTH];
int pcnt = 0;

//these values are substracetd from the generated values to give a shape to the animation
const unsigned char valueMask[8][16] PROGMEM = {
  {32 , 0  , 0  , 0  , 0  , 0  , 0  , 32 , 32 , 0  , 0  , 0  , 0  , 0  , 0  , 32 },
  {64 , 0  , 0  , 0  , 0  , 0  , 0  , 64 , 64 , 0  , 0  , 0  , 0  , 0  , 0  , 64 },
  {96 , 32 , 0  , 0  , 0  , 0  , 32 , 96 , 96 , 32 , 0  , 0  , 0  , 0  , 32 , 96 },
  {128, 64 , 32 , 0  , 0  , 32 , 64 , 128, 128, 64 , 32 , 0  , 0  , 32 , 64 , 128},
  {160, 96 , 64 , 32 , 32 , 64 , 96 , 160, 160, 96 , 64 , 32 , 32 , 64 , 96 , 160},
  {192, 128, 96 , 64 , 64 , 96 , 128, 192, 192, 128, 96 , 64 , 64 , 96 , 128, 192},
  {255, 160, 128, 96 , 96 , 128, 160, 255, 255, 160, 128, 96 , 96 , 128, 160, 255},
  {255, 192, 160, 128, 128, 160, 192, 255, 255, 192, 160, 128, 128, 160, 192, 255}
};

//these are the hues for the fire,
//should be between 0 (red) to about 25 (yellow)
const unsigned char hueMask[8][16] PROGMEM = {
  {1 , 11, 19, 25, 25, 22, 11, 1 , 1 , 11, 19, 25, 25, 22, 11, 1 },
  {1 , 8 , 13, 19, 25, 19, 8 , 1 , 1 , 8 , 13, 19, 25, 19, 8 , 1 },
  {1 , 8 , 13, 16, 19, 16, 8 , 1 , 1 , 8 , 13, 16, 19, 16, 8 , 1 },
  {1 , 5 , 11, 13, 13, 13, 5 , 1 , 1 , 5 , 11, 13, 13, 13, 5 , 1 },
  {1 , 5 , 11, 11, 11, 11, 5 , 1 , 1 , 5 , 11, 11, 11, 11, 5 , 1 },
  {0 , 1 , 5 , 8 , 8 , 5 , 1 , 0 , 0 , 1 , 5 , 8 , 8 , 5 , 1 , 0 },
  {0 , 0 , 1 , 5 , 5 , 1 , 0 , 0 , 0 , 0 , 1 , 5 , 5 , 1 , 0 , 0 },
  {0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 }
};

void fireRoutine() {
  if (loadingFlag) {
    loadingFlag = false;
    //FastLED.clear();
    generateLine();
  }
  if (pcnt >= 100) {
    ShiftUp();
    generateLine();
    pcnt = 0;
  }
  drawFrame(pcnt);
  pcnt += 30;
}

// Случайным образом генерирует следующую линию (matrix row)

void generateLine() {
  for (uint8_t x = 0; x < WIDTH; x++) {
    line[x] = random(64, 255);
  }
}

void ShiftUp() {
  for (uint8_t y = HEIGHT - 1; y > 0; y--) {
    for (uint8_t x = 0; x < WIDTH; x++) {
      uint8_t newX = x;
      if (x > 15) newX = x - 15;
      if (y > 7) continue;
      matrixValue[y][newX] = matrixValue[y - 1][newX];
    }
  }

  for (uint8_t x = 0; x < WIDTH; x++) {
    uint8_t newX = x;
    if (x > 15) newX = x - 15;
    matrixValue[0][newX] = line[newX];
  }
}

// рисует кадр, интерполируя между 2 "ключевых кадров"
// параметр pcnt - процент интерполяции

void drawFrame(int pcnt) {
  int nextv;

  //each row interpolates with the one before it
  for (unsigned char y = HEIGHT - 1; y > 0; y--) {
    for (unsigned char x = 0; x < WIDTH; x++) {
      uint8_t newX = x;
      if (x > 15) newX = x - 15;
      if (y < 8) {
        nextv =
          (((100.0 - pcnt) * matrixValue[y][newX]
            + pcnt * matrixValue[y - 1][newX]) / 100.0)
          - pgm_read_byte(&(valueMask[y][newX]));

        CRGB color = CHSV(
                       modes[1].Scale * 2.5 + pgm_read_byte(&(hueMask[y][newX])), // H
                       255, // S
                       (uint8_t)max(0, nextv) // V
                     );

        leds[getPixelNumber(x, y)] = color;
      } else if (y == 8 && SPARKLES) {
        if (random(0, 20) == 0 && getPixColorXY(x, y - 1) != 0) drawPixelXY(x, y, getPixColorXY(x, y - 1));
        else drawPixelXY(x, y, 0);
      } else if (SPARKLES) {

        // старая версия для яркости
        if (getPixColorXY(x, y - 1) > 0)
          drawPixelXY(x, y, getPixColorXY(x, y - 1));
        else drawPixelXY(x, y, 0);

      }
    }
  }

  //Перавя стрка интерполируется со следующей "next" линией
  for (unsigned char x = 0; x < WIDTH; x++) {
    uint8_t newX = x;
    if (x > 15) newX = x - 15;
    CRGB color = CHSV(
                   modes[1].Scale * 2.5 + pgm_read_byte(&(hueMask[0][newX])), // H
                   255,           // S
                   (uint8_t)(((100.0 - pcnt) * matrixValue[0][newX] + pcnt * line[newX]) / 100.0) // V
                 );
    leds[getPixelNumber(newX, 0)] = color;
  }
}
// ---------------------Огненная Лампа-------------------------------
// Yaroslaw Turbin, 22.06.2020
// https://vk.com/ldirko
// https://pastebin.com/eKqe4zzA
// доработки - kostyamat
void FireRoutine() {
  if (loadingFlag) {
    setCurrentPalette(palette + 10);
    loadingFlag = false;
  }

  uint8_t speedy = map(modes[currentMode].Speed, 1, 255, 255, 0);
  uint8_t _scale = modes[currentMode].Scale + 30;

  uint32_t a = millis();
  for (byte i = 0U; i < WIDTH; i++) {
    for (byte j = 0U; j < HEIGHT; j++) {
      if (palette <= 9)
        drawPixelXY((WIDTH - 1) - i, (HEIGHT - 1) - j, ColorFromPalette(*curPalette, qsub8(inoise8(i * _scale, j * _scale + a, a / speedy), abs8(j - (HEIGHT - 1)) * 255 / (HEIGHT - 1)), 255));
      else
        drawPixelXY((WIDTH - 1) - i, (HEIGHT - 1) - j, ColorFromPalette(HeatColors_p, qsub8(inoise8(i * _scale, j * _scale + a, a / speedy), abs8(j - (HEIGHT - 1)) * 255 / (HEIGHT - 1)), 255));
    }
  }
}

//---------------Лаволампа------------------------------
//Основа @SottNick
//Оптимизация @Stepko
float ball[(WIDTH / 2) -  ((WIDTH - 1) & 0x01)][4];
void drawBlob(uint8_t l, CRGB color) { //раз круги нарисовать не получается, будем попиксельно вырисовывать 2 варианта пузырей
  if (ball[l][3] == 2)
  {
    for (int8_t x = -2; x < 3; x++)
      for (int8_t y = -2; y < 3; y++)
        if (abs(x) + abs(y) < 4)
          drawPixelXYF(fmod(ball[l][1] + x + WIDTH, WIDTH), ball[l][0] + y, color);
  }
  else
  {
    for (int8_t x = -1; x < 3; x++)
      for (int8_t y = -1; y < 3; y++)
        if (!(x == -1 && (y == -1 || y == 2) || x == 2 && (y == -1 || y == 2)))
          drawPixelXYF(fmod(ball[l][1] + x + WIDTH, WIDTH), ball[l][0] + y, color);
  }
}

void LavaLampRoutine() {
  if (loadingFlag)
  { for (byte i = 0; i < (WIDTH / 2) -  ((WIDTH - 1) & 0x01); i++) {
      ball[i][3] = random(1, 3);
      ball[i][2] = (float)random8(5, 11) / (257U - modes[currentMode].Speed) / 4.0;
      ball[i][0] = 0;
      ball[i][1] = i * 2U + random8(2);
      if ( ball[i][2] == 0)
        ball[i][2] = 1;
    }
    loadingFlag = false;
    setCurrentPalette(palette);
  }
  dimAll(100);
  blurScreen(20);
  for (byte i = 0; i < (WIDTH / 2) -  ((WIDTH - 1) & 0x01); i++) {
    // Draw 'ball'
    if (palette <= 9)
      drawBlob(i, ColorFromPalette(*curPalette, ball[i][0] * 16));
    else
      drawBlob(i, CHSV(modes[currentMode].Scale, 255, 255));

    if (ball[i][0] + ball[i][3] >= HEIGHT - 1)
      ball[i][0] += (ball[i][2] * ((HEIGHT - 1 - ball[i][0]) / ball[i][3] + 0.005));
    else if (ball[i][0] - ball[i][3] <= 0)
      ball[i][0] += (ball[i][2] * (ball[i][0] / ball[i][3] + 0.005));
    else
      ball[i][0] += ball[i][2];
    if (ball[i][0] < 0.01) {                  // почему-то при нуле появляется мерцание (один кадр, еле заметно)
      ball[i][2] = (float)random8(5, 11) / (257U - modes[currentMode].Speed) / 4.0;
      ball[i][0] = 0.01;
    }
    else if (ball[i][0] > HEIGHT - 1.01) {    // тоже на всякий пожарный
      ball[i][2] = (float)random8(5, 11) / (257U - modes[currentMode].Speed) / 4.0;
      ball[i][2] = -ball[i][2];
      ball[i][0] = HEIGHT - 1.01;
    }
  }
}
// ============= ЭФФЕКТ ПРИЗМАТА ===============
// Prismata Loading Animation
// https://github.com/pixelmatix/aurora/blob/master/PatternPendulumWave.h
// Адаптация от (c) SottNick

void PrismataRoutine() {
  if (loadingFlag)
  {
    loadingFlag = false;
    setCurrentPalette(palette);

  } 
  

    hue += 1;

  fadeToBlackBy(leds, NUM_LEDS, 256U - modes[currentMode].Scale); // делаем шлейф

  for (float x = 0.0f; x <= (float)WIDTH - 1; x += 0.25f) {
      float y = (float)beatsin8((uint8_t)x + 1 * (float)modes[currentMode].Speed / 2.0f, 0, (HEIGHT-1)* 4) / 4.0f;
  drawPixelXYF(x, y, ColorFromPalette(*curPalette, hue));
    }
}