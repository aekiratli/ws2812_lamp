void TouchCount()
{

  currentState = digitalRead(touchPin);
  if ( currentState == true && previousState == false)
  {
    touchCounter++;
    if (touchCounter > touchLimit)
    {
      touchCounter = 0;
    }
    previousState = true;
    Serial.println(touchCounter);
  }

  if ( currentState == false && previousState == true)
    previousState = false;

}

void LoadTheLamp()
{
  float v = 175;
  float a = 1.05;
  float x = 7.5;

  for (int i = 0; i < numberOfLeds; i++)
  {
    leds[i] = CRGB::White;
    x =  x * a;
    v = v - x;
    if ( v <= 20 ) v = 20;
    FastLED.delay(round(v));
    FastLED.show();

  }

  for (int i = 1; i < numberOfLeds; i++)
  {
    leds[i] = CRGB::Black;
    x = x  * a;
    v = v - x;
    if ( v <= 20 ) v = 20;

    FastLED.delay(round(v));
    FastLED.show();

  }
  leds[0] = CRGB::Black;
  FastLED.show();

  delay(500);

  for (int i = 0; i < numberOfLeds; i++)
  {
    leds[i] = CRGB::White;
    x = x * a;
    v = v - x;
  }

  FastLED.show();
  delay(500);

  for (int i = 0; i < numberOfLeds; i++)
  {
    leds[i] = CRGB::Black;

  }
  FastLED.show();
  delay(500);

  for (int i = 0; i < numberOfLeds; i++)
  {
    leds[i] = CRGB::White;

  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < numberOfLeds; i++)
  {
    leds[i] = CRGB::Black;

  }
  FastLED.show();
  delay(500);


}


void PulseEffect()
{
  for (int i = 0; i < numberOfLeds / 2; i++) {
    tryToUpdate();
    updateHue();
    leds.fadeToBlackBy(40);

    leds[i] = CHSV(gHue, 255, 255);

    leds(numberOfLeds / 2, numberOfLeds - 1) = leds(numberOfLeds / 2 - 1 , 0);
    FastLED.delay(1000 / fps);
  }
}

void TurnOff()
{
  for (int i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    server.handleClient();
    LEDS.setBrightness(brightness);

    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
}

void fadeall() {
  for (int i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    LEDS.setBrightness(brightness);
    leds[i].nscale8(250);
  }
}

void fadeToBlack() {
  for (int i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    leds[i].nscale8(250);
    LEDS.setBrightness(brightness);

    FastLED.show();
  }
}

void Cyclon()
{
  Serial.print("x");
  LEDS.setBrightness(brightness);

  for (int i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    updateHue();
    leds[i] = CHSV(gHue, 255, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000 / fps);
  }

  for (int i = (numberOfLeds) - 1; i >= 0; i--) {
    tryToUpdate();
    updateHue();
    leds[i] = CHSV(gHue, 255, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(1000 / fps);
  }
}

void Rainbow()
{
  tryToUpdate();
  LEDS.setBrightness(brightness);
  fill_rainbow( leds, numberOfLeds, gHue, 7);
  FastLED.show();
  FastLED.delay(1000 / fps);
}

void Confetti()
{
  tryToUpdate();
  LEDS.setBrightness(brightness);
  fadeToBlackBy( leds, numberOfLeds, 10);
  int pos = random16(numberOfLeds);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  FastLED.show();
  FastLED.delay(1000 / fps);
}

void Sinelon()
{
  tryToUpdate();
  fadeToBlackBy( leds, numberOfLeds, 20);
  int pos = beatsin16( 13, 0, numberOfLeds - 1 );
  leds[pos] += CHSV( gHue, 255, 192);
  FastLED.show();
  FastLED.delay(1000 / fps);
}

void Bpm()
{
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < numberOfLeds; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    tryToUpdate();
  }
  FastLED.show();
  FastLED.delay(1000 / fps);
}

void Juggle() {
  tryToUpdate();
  fadeToBlackBy( leds, numberOfLeds, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    tryToUpdate();
    leds[beatsin16( i + 7, 0, numberOfLeds - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  FastLED.show();
  FastLED.delay(1000 / fps);
}



void Fire2012()
{
  // Array of temperature readings at each simulation cell

  static byte heat[numberOfLeds];
  tryToUpdate();
  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / numberOfLeds) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = numberOfLeds - 1; k >= 2; k--) {
    tryToUpdate();
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < numberOfLeds; j++) {
    tryToUpdate();
    CRGB color = HeatColor( heat[j]);
    int pixelnumber;
    if ( gReverseDirection ) {
      pixelnumber = (numberOfLeds - 1) - j;
    } else {
      pixelnumber = j;
    }
    leds[pixelnumber] = color;
  }

  FastLED.show(); // display this frame
  FastLED.delay(1000 / fps);
}

void Pacifica()
{
  // Increment the four "color index start" counters, one for each wave layer.
  // Each is incremented at a different speed, and the speeds vary over time.
  tryToUpdate();
  static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
  static uint32_t sLastms = 0;
  uint32_t ms = GET_MILLIS();
  uint32_t deltams = ms - sLastms;
  sLastms = ms;
  uint16_t speedfactor1 = beatsin16(3, 179, 269);
  uint16_t speedfactor2 = beatsin16(4, 179, 269);
  uint32_t deltams1 = (deltams * speedfactor1) / 256;
  uint32_t deltams2 = (deltams * speedfactor2) / 256;
  uint32_t deltams21 = (deltams1 + deltams2) / 2;
  sCIStart1 += (deltams1 * beatsin88(1011, 10, 13));
  sCIStart2 -= (deltams21 * beatsin88(777, 8, 11));
  sCIStart3 -= (deltams1 * beatsin88(501, 5, 7));
  sCIStart4 -= (deltams2 * beatsin88(257, 4, 6));

  // Clear out the LED array to a dim background blue-green
  fill_solid( leds, numberOfLeds, CRGB( 2, 6, 10));

  // Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer( pacifica_palette_1, sCIStart1, beatsin16( 3, 11 * 256, 14 * 256), beatsin8( 10, 70, 130), 0 - beat16( 301) );
  pacifica_one_layer( pacifica_palette_2, sCIStart2, beatsin16( 4,  6 * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401) );
  pacifica_one_layer( pacifica_palette_3, sCIStart3, 6 * 256, beatsin8( 9, 10, 38), 0 - beat16(503));
  pacifica_one_layer( pacifica_palette_3, sCIStart4, 5 * 256, beatsin8( 8, 10, 28), beat16(601));

  // Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps();

  // Deepen the blues and greens a bit
  pacifica_deepen_colors();
  FastLED.delay(1000 / fps);
}

// Add one layer of waves into the led array
void pacifica_one_layer( CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for ( uint16_t i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    waveangle += 250;
    uint16_t s16 = sin16( waveangle ) + 32768;
    uint16_t cs = scale16( s16 , wavescale_half ) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16( ci) + 32768;
    uint8_t sindex8 = scale16( sindex16, 240);
    CRGB c = ColorFromPalette( p, sindex8, bri, LINEARBLEND);
    leds[i] += c;
  }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps()
{
  uint8_t basethreshold = beatsin8( 9, 55, 65);
  uint8_t wave = beat8( 7 );

  for ( uint16_t i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    uint8_t threshold = scale8( sin8( wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = leds[i].getAverageLight();
    if ( l > threshold) {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8( overage, overage);
      leds[i] += CRGB( overage, overage2, qadd8( overage2, overage2));
    }
  }
}

// Deepen the blues and greens
void pacifica_deepen_colors()
{
  for ( uint16_t i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    leds[i].blue = scale8( leds[i].blue,  145);
    leds[i].green = scale8( leds[i].green, 200);
    leds[i] |= CRGB( 2, 5, 7);
  }
}

void Pride()
{
  tryToUpdate();
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for ( uint16_t i = 0 ; i < numberOfLeds; i++) {
    tryToUpdate();
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    CRGB newcolor = CHSV( hue8, sat8, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numberOfLeds - 1) - pixelnumber;

    nblend( leds[pixelnumber], newcolor, 64);
  }
  FastLED.delay(1000 / fps);
}
