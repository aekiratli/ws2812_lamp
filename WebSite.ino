String SendHTML() {
  // TODO
  // js color add text
  // get hex instead of rgb


  String ptr = "<!DOCTYPE html> <html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <title>Lamp Control</title>\n";
  ptr += "<link rel='shortcut icon' href='https://img.icons8.com/material/24/000000/idea--v1.png' type='image/x-icon' /><style>.glow-on-hover {padding: 8px 25px; border: none;outline: none;color: #fff;background: #111;cursor: pointer;position: relative;z-index: 0;border-radius: 10px;}\n";
  ptr += ".glow-on-hover:before { content: '';background: linear-gradient(45deg, #ff0000, #ff7300, #fffb00, #48ff00, #00ffd5, #002bff, #7a00ff, #ff00c8, #ff0000); position: absolute; top: -2px;left:-2px;background-size: 400%;z-index: -1;filter: blur(5px); width: calc(100% + 4px); height: calc(100% + 4px);animation: glowing 20s linear infinite;opacity: 0;transition: opacity .3s ease-in-out; border-radius: 10px;}\n";
  ptr += ".glow-on-hover:active { color: #000}\n";
  ptr += ".glow-on-hover:active:after { background: transparent;}\n";
  ptr += ".glow-on-hover:hover:before { opacity: 1;}\n";
  ptr += ".glow-on-hover:after { z-index: -1;content: '';position: absolute; width: 100%; height: 100%;background: #111;left: 0;  top: 0; border-radius: 10px;}\n";
  ptr += ".slider {-webkit-appearance: none;width: 150px;height: 10px;border-radius: 5px;background: #000000;outline: none;opacity: 0.7;-webkit-transition: .2s;transition: opacity .2s;}\n";
  ptr += ".slider:hover {opacity: 1;}\n";
  ptr += ".slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 25px; height: 25px;  border-radius: 50%; background: #4CAF50; cursor: pointer;}\n";
  ptr += ".slider::-moz-range-thumb {width: 25px;height: 25px; border-radius: 50%;background: #4CAF50;cursor: pointer;}\n";
  ptr += "@keyframes glowing {0% { background-position: 0 0; }50% { background-position: 400% 0; }100% { background-position: 0 0; }}\n";
  ptr += "html {font-family: Helvetica; display: inline-block;margin: 0px auto;text-align: center;}\n";
  ptr += "body {margin-top: 50px; background-color: #323532;}\n";
  ptr += "h1 {color: hsl(120, 76%, 39%);margin: 50px auto 30px;}h3 {color:hsl(120, 76%, 39%);margin-bottom: 50px;}\n";
  ptr += "p {font-size: 14px;color:hsl(120, 76%, 39%);margin-bottom: 10px;}</style>\n";
  ptr += "<script src='https://cdnjs.cloudflare.com/ajax/libs/jscolor/2.0.4/jscolor.min.js'></script></head>\n";
  ptr += "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>\n";
  ptr += "<body><div class='container'><h1>Lamp Control</h1><h3>Set lamp to 1 specific colour or pick patterns from below</h3>\n";
  ptr += "<input class='jscolor' onchange='update(this.jscolor)' value='000000' id='rgb'>\n";

  String myString = String(brightness);
  ptr += "<p>Brightness : <span id='slider_p'></span></p>\n";
  ptr += "<input type='range' min='0' max='255' value='" + myString + "' class='slider' id='myRange'>\n";

  myString = String(timeInterval);
  ptr += "<p>Color Change Interval : <span id = 'slider_p2'> </span> </p>\n";
  ptr += "<input type = 'range' min = '1' max = '1000' value ='" + myString + "' class = 'slider' id = 'myRange2'>\n";


  myString = String(fps);
  ptr += "<p>FPS : <span id = 'slider_p3'> </span> </p>\n";
  ptr += "<input type = 'range' min = '1' max = '120' value ='" + myString + "' class = 'slider' id = 'myRange3'>\n";

  ptr += "<br></br><h3>Patterns:</h3>\n";
  ptr += "<script>function update(picker) {document.getElementById('rgb').innerHTML = Math.round(picker.rgb[0]) + ', ' +  Math.round(picker.rgb[1]) + ', ' + Math.round(picker.rgb[2]);";
  ptr += "var xhttp = new XMLHttpRequest();console.log(\"olm nolyi\"); xhttp.open('GET', 'setrgb?r=' + Math.round(picker.rgb[0])+'&g=' + Math.round(picker.rgb[1])+ '&b='+Math.round(picker.rgb[2]), true); xhttp.send() ;}</script>\n";
  ptr += "<script src='https://canvasjs.com/assets/script/canvasjs.min.js'></script>\n";
  ptr += "<script>var slider = document.getElementById('myRange');var output = document.getElementById('slider_p');output.innerHTML = slider.value;console.log(5 + 6);slider.onchange = function() {   output.innerHTML = this.value;pwm_change(this.value);}</script>\n";
  ptr += "<script>function pwm_change(val) {var xhttp = new XMLHttpRequest();xhttp.open('GET', 'setbrightness?brightness='+val, true);xhttp.send();}</script>\n";
  ptr += "<script>var slider2 = document.getElementById('myRange2'); var output2 = document.getElementById('slider_p2'); output2.innerHTML = slider2.value;if (output2.innerHTML >= 1000){ output2.innerHTML = 'Color Will Stay the Same';} slider2.onchange = function () { output2.innerHTML = this.value; if (output2.innerHTML >= 1000){ output2.innerHTML = 'Color Will Stay the Same'} pwm_change2(this.value); }</script>\n";
  ptr += "<script>function pwm_change2(val) { var xhttp = new XMLHttpRequest(); xhttp.open('GET', 'setinterval?interval=' + val, true); xhttp.send(); }</script>\n";
  ptr += "<script>var slider3 = document.getElementById('myRange3'); var output3 = document.getElementById('slider_p3'); output3.innerHTML = slider3.value; slider3.onchange = function () { output3.innerHTML = this.value;  pwm_change3(this.value); }</script>\n";
  ptr += "<script>function pwm_change3(val) { var xhttp = new XMLHttpRequest(); xhttp.open('GET', 'setfps?fps=' + val, true); xhttp.send(); }</script>\n";
  ptr += "<a class= 'glow-on-hover' href=  '/pulseEffect'>Pulse Effect !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/cyclon'>Cyclon !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/rainbow'>Rainbow !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/confetti'> Confetti !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/sinelon'>Sinelon !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/bpm'>BPM !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/juggle'>Juggle !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/fire'>Fire !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/pacifica'>Pacifica !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/pride'>Pride !</a>\n";
  ptr += "<br></br><a class= 'glow-on-hover' href=  '/fadeAll'>Fade to Black !</a><br></br>\n";
 // ptr += "<br></br><a class= 'glow-on-hover' href = '/turnOffLamp'>Turn off the Lamp</a></body></html> \n";

  return ptr;
}
