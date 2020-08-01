// ************* НАСТРОЙКИ *************
// The 16 bit version of our coordinates
static uint16_t x;
static uint16_t y;
static uint16_t z;

uint16_t speed = 20;                                        // speed is set dynamically once we've started up
uint16_t scale = 30;                                        // scale is set dynamically once we've started up

// This is the array that we keep our computed noise values in
#define MAX_DIMENSION (max(WIDTH, HEIGHT))
#if (WIDTH > HEIGHT)
uint8_t noise[WIDTH][WIDTH];
#else
uint8_t noise[HEIGHT][HEIGHT];
#endif

CRGBPalette16 currentPalette(PartyColors_p);
uint8_t colorLoop = 1;
uint8_t ihue = 0;

void madnessNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
  }
  fillnoise8();
  for (uint8_t i = 0; i < WIDTH; i++)
  {
    for (uint8_t j = 0; j < HEIGHT; j++)
    {
      CRGB thisColor = CHSV(noise[j][i], 255, noise[i][j]);
      drawPixelXY(i, j, thisColor);                         //leds[XY(i, j)] = CHSV(noise[j][i], 255, noise[i][j]);
    }
  }
  ihue += 1;
}

void rainbowNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = RainbowColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 1;
  }
  fillNoiseLED(true,true,true);
}

void rainbowStripeNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = RainbowStripeColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 1;
  }
  fillNoiseLED(true,true,true);
}

void zebraNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    // 'black out' all 16 palette entries...
    fill_solid(currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 1;
  }
  fillNoiseLED(true,true,true);
}

void forestNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = ForestColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 0;
  }
  fillNoiseLED(true,true,true);
}

void oceanNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = OceanColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 0;
  }

  fillNoiseLED(true,true,true);
}

void plasmaNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = PartyColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 1;
  }
  fillNoiseLED(true,true,true);
}

void cloudNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = CloudColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 0;
  }
  fillNoiseLED(true,true,true);
}

void lavaNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = LavaColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 0;
  }
  fillNoiseLED(true,true,true);
}

void heatNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = HeatColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 0;
  }
  fillNoiseLED(false,true,false);
}

void smokeNoise()
{
  if (loadingFlag)
  {
    loadingFlag = false;
    currentPalette = WaterfallColors_p;
    scale = modes[currentMode].Scale;
    speed = modes[currentMode].Speed;
    colorLoop = 0;
  }
  fillNoiseLED(false,true,false);
}

// ************* СЛУЖЕБНЫЕ *************
void fillNoiseLED(bool x_dir, bool y_dir, bool z_dir)
{
  uint8_t dataSmoothing = 0;
  if (speed < 50)
  {
    dataSmoothing = 200 - (speed * 4);
  }
  for (uint8_t i = 0; i < MAX_DIMENSION; i++)
  {
    int32_t ioffset = scale * i;
    for (uint8_t j = 0; j < MAX_DIMENSION; j++)
    {
      int32_t joffset = scale * j;

      uint8_t data = inoise8(x + ioffset, y + joffset, z);

      data = qsub8(data, 16);
      data = qadd8(data, scale8(data, 39));

      if (dataSmoothing)
      {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }

      noise[i][j] = data;
    }
  }
  if(z_dir)
  z += speed;

  // apply slow drift to X and Y, just for visual variation.
  if(x_dir){ if((z_dir)&&(x_dir))
  x += speed /8;}
  else x -= speed;
  if(y_dir){ if((z_dir)&&(y_dir))
  y -= speed / 16;}
  else y -= speed;

  for (uint8_t i = 0; i < WIDTH; i++)
  {
    for (uint8_t j = 0; j < HEIGHT; j++)
    {
      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];
      // if this palette is a 'loop', add a slowly-changing base value
      if ( colorLoop)
      {
        index += ihue;
      }
      // brighten up, as the color palette itself often contains the
      // light/dark dynamic range desired
      if ( bri > 127 )
      {
        bri = 255;
      }
      else
      {
        bri = dim8_raw( bri * 2);
      }
      CRGB color = ColorFromPalette( currentPalette, index, bri);
      drawPixelXY(i, j, color);                             //leds[XY(i, j)] = color;
    }
  }
  ihue += 1;
}

void fillnoise8()
{
  for (uint8_t i = 0; i < MAX_DIMENSION; i++)
  {
    int32_t ioffset = scale * i;
    for (uint8_t j = 0; j < MAX_DIMENSION; j++)
    {
      int32_t joffset = scale * j;
      noise[i][j] = inoise8(x + ioffset, y + joffset, z);
    }
  }
  z += speed;
}