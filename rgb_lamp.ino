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
//End of Pins

// Variables
int touchCounter = 0;
int brightness = 1;
bool previousState = false;
bool currentState = false;
int touchLimit = 5;
uint8_t gHue = 0;
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
  FastLED.addLeds<WS2812, ledPin, RGB>(leds, numberOfLeds);
  LEDS.setBrightness(brightness);

  delay(500);
  initServer();
  Serial.println("HTTP server started on ");
  Serial.print(IP);
}
void tryToUpdate() // Need to update dynamicly due to webserver and touch module
{
  TouchCount();
  server.handleClient();
}
void loop() {
  // TO DO
  // LOAD THE LAMP AND INCREASE COUNTER TO 1 THEN MAKE IT WHITE AND LISTEN RGB ! DONE
  // Find more patterns and add it to code !
  // 1.1 ) RAINBOW
  // 1.2 ) MANY COLOUR PALETTES pick from color palettes and add your own
  // 1.3 ) FIRE use fire example
  // 1.4 ) PACIFICA use pacifica example
  // 1.5 ) PRIDE2015 use pride example
  tryToUpdate();

  if ( touchCounter == 0)
  {
    LoadTheLamp();
    LoadTheLamp();
    touchCounter = 1;
    for (int i = 0; i < numberOfLeds; i++)
      leds[i] = CRGB::White;

  }
  else if ( touchCounter == 1)
  {
    for (int i = 0; i < numberOfLeds; i++) {

      server.handleClient();
      LEDS.setBrightness(brightness);
      FastLED.delay(50);
      FastLED.show();

    }
  }
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
    EVERY_N_MILLISECONDS( 10 ) {
      gHue++;  // slowly cycle the "base color" through the rainbow
    }

    Rainbow();
  }
  else if ( touchCounter == 7)
  {
    EVERY_N_MILLISECONDS( 20 ) {
      gHue++;  // slowly cycle the "base color" through the rainbow
    }

    Confetti();
  }
    else if ( touchCounter == 8)
  {
    EVERY_N_MILLISECONDS( 20 ) {
      gHue++;  // slowly cycle the "base color" through the rainbow
    }

    Sinelon();
  }
    else if ( touchCounter == 9)
  {
    EVERY_N_MILLISECONDS( 20 ) {
      gHue++;  // slowly cycle the "base color" through the rainbow
    }

    Bpm();
  }
    else if ( touchCounter == 10)
  {
    Juggle();
  }
}
