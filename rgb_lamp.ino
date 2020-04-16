//------------------------------- SETTINGS -------------------------------------- //
// Libraries
#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
// End of Libraries

// Pins
#define ledPin 23
#define numberOfLeds 24
#define touchPin 33
#define COOLING  55
#define SPARKING  120
//End of Pins

// Variables
int touchCounter = 0;
int brightness = 1;
float fps = 120;
bool previousState = false;
bool currentState = false;
int touchLimit = 5;
bool gReverseDirection = false;
uint8_t gHue = 0;
int timeInterval = 20;
CRGBPalette16 pacifica_palette_1 =
{ 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
  0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50
};
CRGBPalette16 pacifica_palette_2 =
{ 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117,
  0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F
};
CRGBPalette16 pacifica_palette_3 =
{ 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33,
  0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF
};
// End of Variables

//Network
const char* ssid = "";  // Enter SSID here
const char* password = "";  //Enter Password here
IPAddress IP(192, 168, 0, 43);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
// End of Network

// Init class
WebServer server(80);
CRGBArray<numberOfLeds> leds;
// End of init class

//------------------------------------- END OF REGION SETTINGS --------------------------- //

void setup() {

  delay(3000);
  Serial.begin(9600);

  if (!WiFi.config(IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Trying ...");
  }
  delay(500);
  pinMode(touchPin, INPUT);
  FastLED.addLeds<WS2812, ledPin, GRB>(leds, numberOfLeds);
  LEDS.setBrightness(brightness);

  delay(500);
  initServer();
  Serial.println("HTTP server started on ");
  Serial.print(IP);
}
void updateHue()
{
  Serial.println("timeInterval = ");
  Serial.println(timeInterval);
  Serial.println("gHue = ");
  Serial.println(gHue);
  EVERY_N_MILLISECONDS_I( timingObj, 20 ) {
    timingObj.setPeriod( timeInterval );
    if ( timeInterval < 1000)
      gHue++;
  }

}
void tryToUpdate() // Need to update dynamicly due to webserver and touch module
{
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(500);
    Serial.println("Trying ...");
  }
  TouchCount();
  LEDS.setBrightness(brightness);
  server.handleClient();
}

void loop() {
  // TO DO
  // LOAD THE LAMP AND INCREASE COUNTER TO 1 THEN MAKE IT WHITE AND LISTEN RGB ! DONE
  // Find more patterns and add it to code !
  // 1.2 ) MANY COLOUR PALETTES pick from color palettes and add your own
  // 1.4 ) PACIFICA use pacifica example
  // 1.5 ) PRIDE2015 use pride example
  tryToUpdate();
  // LAMP LOAD --------------------------------------
  if ( touchCounter == 0)
  {
    //LoadTheLamp();
    LoadTheLamp();
    touchCounter = 1;
    for (int i = 0; i < numberOfLeds; i++)
      leds[i] = CRGB::White;

  }
  // SINGLE COLOR ----------------------------------
  else if ( touchCounter == 1)
  {
    for (int i = 0; i < numberOfLeds; i++) {

      server.handleClient();
      LEDS.setBrightness(brightness);
      FastLED.delay(1000/fps);
      FastLED.show();

    }
  }
  // PULSE EFFECT  ---------------------------------
  else if ( touchCounter == 2)
  {
    PulseEffect();
  }


  else if ( touchCounter == 3)
  {
    TurnOff();

  }
  else if ( touchCounter == 4)
  {
    fadeToBlack();

  }
  else if ( touchCounter == 5)
  {
    Cyclon();
  }

  else if ( touchCounter == 6)
  {
    updateHue();
    Rainbow();
  }
  else if ( touchCounter == 7)
  {
    updateHue();
    Confetti();
  }
  else if ( touchCounter == 8)
  {
    updateHue();
    Sinelon();
  }
  else if ( touchCounter == 9)
  {
    updateHue();
    Bpm();
  }
  else if ( touchCounter == 10)
  {
    Juggle();
  }
  else if ( touchCounter == 11)
  {
    Fire2012();

  }
  else if ( touchCounter == 12)
  {
    EVERY_N_MILLISECONDS( 20) {
      Pacifica();
    }
  }
  else if ( touchCounter == 13)
  {
    Pride();
  }

}
