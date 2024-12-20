#ifndef HTML_PAGE_H
#define HTML_PAGE_H

// The main HTML page stored in program memory for efficiency
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<style>
body { font-family: sans-serif; background: #f0f0f0; display: flex; justify-content: center; align-items: center; height: 100vh; margin:0; }
#controls { text-align: center; }
button { margin: 10px; padding: 20px; font-size: 18px; cursor: pointer; }
</style>
</head>
<body>
<div id="controls">
  <div><button onclick="sendAction('forward')">Forward</button></div>
  <div>
    <button onclick="sendAction('left')">Left</button>
    <button onclick="sendAction('stop')">Stop</button>
    <button onclick="sendAction('right')">Right</button>
  </div>
  <div><button onclick="sendAction('backward')">Backward</button></div>
  <div>
    <button onclick="sendAction('rotate_left')">Rotate Left</button>
    <button onclick="sendAction('rotate_right')">Rotate Right</button>
  </div>
</div>
<script>
function sendAction(action) {
  fetch('/cmd?action=' + action)
    .then(response => response.text())
    .then(text => console.log(text));
}
</script>
</body>
</html>
)rawliteral";

#endif
