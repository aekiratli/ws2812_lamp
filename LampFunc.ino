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
  static uint8_t hue;
  for (int i = 0; i < numberOfLeds / 2; i++) {
    tryToUpdate();
    LEDS.setBrightness(brightness);

    leds.fadeToBlackBy(40);

    leds[i] = CHSV(hue++, 255, 255);

    leds(numberOfLeds / 2, numberOfLeds - 1) = leds(numberOfLeds / 2 - 1 , 0);
    FastLED.delay(33);
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
  static uint8_t hue = 0;
  Serial.print("x");
  LEDS.setBrightness(brightness);

  for (int i = 0; i < numberOfLeds; i++) {
    tryToUpdate();
    LEDS.setBrightness(brightness);
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(10);
  }

  for (int i = (numberOfLeds) - 1; i >= 0; i--) {
    tryToUpdate();
    LEDS.setBrightness(brightness);
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    delay(10);
  }
}

void Rainbow()
{
  tryToUpdate();
  LEDS.setBrightness(brightness);
  fill_rainbow( leds, numberOfLeds, gHue, 7);
  FastLED.show();
  FastLED.delay(8.33);
}

void Confetti()
{
  tryToUpdate();
  LEDS.setBrightness(brightness);
  fadeToBlackBy( leds, numberOfLeds, 10);
  int pos = random16(numberOfLeds);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  FastLED.show();
  FastLED.delay(8.33);
}

void Sinelon()
{
  tryToUpdate();
  LEDS.setBrightness(brightness);
  fadeToBlackBy( leds, numberOfLeds, 20);
  int pos = beatsin16( 13, 0, numberOfLeds - 1 );
  leds[pos] += CHSV( gHue, 255, 192);
  FastLED.show();
  FastLED.delay(8.33);
}

void Bpm()
{
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < numberOfLeds; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    tryToUpdate();
    LEDS.setBrightness(brightness);
  }
  FastLED.show();
  FastLED.delay(8.33);
}

void Juggle() {
  tryToUpdate();
  fadeToBlackBy( leds, numberOfLeds, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    tryToUpdate();
    LEDS.setBrightness(brightness);
    leds[beatsin16( i + 7, 0, numberOfLeds - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
  FastLED.show();
  FastLED.delay(8.33);
}
