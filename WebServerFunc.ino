void handle_OnConnect() {
  touchCounter = 1;
  server.send(200, "text/html", SendHTML());
}

void handle_Fire2012()
{
  touchCounter = 11;
  server.send(200, "text/html", SendHTML());
}
void handle_Pride2015()
{
  touchCounter = 13;
  server.send(200, "text/html", SendHTML());
}
void handle_Pacifica()
{
  touchCounter = 12;
  server.send(200, "text/html", SendHTML());
}

void handle_bright() {
  String bright = server.arg("brightness"); // reading from slider on html pagae
  Serial.print("slider val: ");
  Serial.println(bright);
  brightness = bright.toInt();
  server.send(200, "text/plane", "0");
}

void handle_fps() { // YAPIYORSUN
  String framepersecond = server.arg("fps"); // reading from slider on html pagae
  Serial.print("slider fps: ");
  Serial.println(framepersecond);
  fps = framepersecond.toInt();
  server.send(200, "text/plane", "0");
}

void handle_interval() {
  String interval = server.arg("interval"); // reading from slider on html pagae
  Serial.print("interval val: ");
  Serial.println(interval);
  timeInterval = interval.toInt();
  server.send(200, "text/plane", "0");
}

void handle_pulseEffect() {
  touchCounter = 2;
  Serial.println("Simetri Pulse Effect");
  server.send(200, "text/html", SendHTML());
}

void handle_rainbow() {
  touchCounter = 6;
  Serial.println("Simetri Pulse Effect");
  server.send(200, "text/html", SendHTML());
}

void handle_confetti() {
  touchCounter = 7;
  server.send(200, "text/html", SendHTML());
}

void handle_sinelon() {
  touchCounter = 8;
  server.send(200, "text/html", SendHTML());
}

void handle_bpm() {
  touchCounter = 9;
  server.send(200, "text/html", SendHTML());
}

void handle_juggle() {
  touchCounter = 10;
  server.send(200, "text/html", SendHTML());
}

void handle_turnOffLamp() {
  touchCounter = 3;
  Serial.println("Lamp off");
  server.send(200, "text/html", SendHTML());
}
void handle_fadeAll() {
  touchCounter = 4;
  Serial.println("fadeAll");
  server.send(200, "text/html", SendHTML());
}
void handle_cyclon() {
  touchCounter = 5;
  Serial.println("cyclon");
  server.send(200, "text/html", SendHTML());
}
void handle_NotFound() {
  server.send(200, "text/html", SendHTML());
}
void  handle_setRGB()
{

  Serial.println(server.arg("r"));
  Serial.println(server.arg("g"));
  Serial.println(server.arg("b"));
  for (int i = 0; i < numberOfLeds; i++) {
    leds[i].r = server.arg("r").toInt();
    leds[i].g = server.arg("g").toInt();
    leds[i].b = server.arg("b").toInt();
    delay(10);
  } delay(100);
  server.send(200, "text/plane", "0");
  touchCounter = 1;
}
void initServer()
{
  server.on("/", handle_OnConnect);
  server.on("/pulseEffect", handle_pulseEffect);
  server.on("/fadeAll", handle_fadeAll);
  server.on("/cyclon", handle_cyclon);
  server.on("/turnOffLamp", handle_turnOffLamp);
  server.on("/setrgb", handle_setRGB);
  server.on("/setbrightness" , handle_bright);
  server.on("/setinterval" , handle_interval);
  server.on("/setfps" , handle_fps);
  server.on("/rainbow", handle_rainbow);
  server.on("/confetti", handle_confetti);
  server.on("/sinelon", handle_sinelon);
  server.on("/bpm", handle_bpm);
  server.on("/juggle", handle_juggle);
  server.on("/fire", handle_Fire2012);
  server.on("/pacifica", handle_Pacifica);
  server.on("/pride", handle_Pride2015);
  server.onNotFound(handle_NotFound);
  server.begin();
}
