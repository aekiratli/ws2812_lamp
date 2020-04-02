String SendHTML() {
  String ptr = "<!DOCTYPE html> <html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  ptr += "<style>.glow-on-hover {padding: 8px 25px; border: none;outline: none;color: #fff;background: #111;cursor: pointer;position: relative;z-index: 0;border-radius: 10px;}\n";
  ptr += ".glow-on-hover:before { content: '';background: linear-gradient(45deg, #ff0000, #ff7300, #fffb00, #48ff00, #00ffd5, #002bff, #7a00ff, #ff00c8, #ff0000); position: absolute; top: -2px;left:-2px;background-size: 400%;z-index: -1;filter: blur(5px); width: calc(100% + 4px); height: calc(100% + 4px);animation: glowing 20s linear infinite;opacity: 0;transition: opacity .3s ease-in-out; border-radius: 10px;}\n";
  ptr += ".glow-on-hover:active { color: #000}\n";
  ptr += ".glow-on-hover:active:after { background: transparent;}\n";
  ptr += ".glow-on-hover:hover:before { opacity: 1;}\n";
  ptr += ".glow-on-hover:after { z-index: -1;content: '';position: absolute; width: 100%; height: 100%;background: #111;left: 0;  top: 0; border-radius: 10px;}\n";
  ptr += "@keyframes glowing {0% { background-position: 0 0; }50% { background-position: 400% 0; }100% { background-position: 0 0; }}\n";
  ptr += "html {font-family: Helvetica; display: inline-block;margin: 0px auto;text-align: center;}\n";
  ptr += "body {margin-top: 50px; background-color: #323532;}\n";
  ptr += "h1 {color: hsl(120, 76%, 39%);margin: 50px auto 30px;}h3 {color:hsl(120, 76%, 39%);margin-bottom: 50px;}\n";
  ptr += "p {font-size: 14px;color:hsl(120, 76%, 39%);margin-bottom: 10px;}</style>\n";
  ptr += "<script src='https://cdnjs.cloudflare.com/ajax/libs/jscolor/2.0.4/jscolor.min.js'></script></head>\n";
  ptr += "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>\n";
  ptr += "<body><div class='container'><h1>Lamp Control</h1><h3>Set lamp to 1 specific colour or pick patterns from below</h3>\n";
  ptr += "<input class=\"jscolor {onFineChange:'update(this)'}\" id=\"rgb\" value='ab25672'>\n";
  ptr += "<a class=\"glow-on-hover\" href='/setrgb' id=\"change_color\" role=\"button\">Change Color</a>\n";
  ptr += "<p>Brightness : <span id='slider_p'></span></p>\n";
  ptr += "<input type='range' min='0' max='255' value='64' class='slider' id='myRange'>\n";
  ptr += "<br></br><h3>Patterns:</h3>\n";
  ptr += "<script>function update(picker) {document.getElementById('rgb').innerHTML = Math.round(picker.rgb[0]) + ', ' +  Math.round(picker.rgb[1]) + ', ' + Math.round(picker.rgb[2]);";
  ptr += "document.getElementById(\"change_color\").href=\"setrgb?r=\" + Math.round(picker.rgb[0]) + \"&g=\" +  Math.round(picker.rgb[1]) + \"&b=\" + Math.round(picker.rgb[2]) ;}</script>\n";
  ptr += "<script src='https://canvasjs.com/assets/script/canvasjs.min.js'></script>\n";
  ptr += "<script>var slider = document.getElementById('myRange');var output = document.getElementById('slider_p');output.innerHTML = slider.value;console.log(5 + 6);slider.onchange = function() {   output.innerHTML = this.value;pwm_change(this.value);}</script>\n";
  ptr += "<script>function pwm_change(val) {var xhttp = new XMLHttpRequest();xhttp.open('GET', 'setbrightness?brightness='+val, true);xhttp.send();}</script>\n";
  ptr += "<a class= 'glow-on-hover' href=  '/pulseEffect'>Pulse Effect !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/cyclon'>Cyclon !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/rainbow'>Rainbow !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/confetti'> Confetti !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/sinelon'>Sinelon !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/bpm'>BPM !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/juggle'>Juggle !</a>\n";
  /* ptr += "<br></br><a class= 'glow-on-hover' href=  '/cyclon'>F !</a>\n";*/
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/fadeAll'>Fade to Black !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href = '/turnOffLamp'>Turn off the Lamp</a></body></html> \n";

  return ptr;
}
