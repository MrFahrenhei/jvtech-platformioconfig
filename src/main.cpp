#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SSID";
const char* password = "PSW";

WebServer server(80);

String getHTML() {
    String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {
  font-family: Arial;
  background: #0f172a;
  color: #e2e8f0;
  text-align: center;
}
.card {
  background: #1e293b;
  margin: 10px auto;
  padding: 20px;
  border-radius: 15px;
  width: 300px;
  box-shadow: 0 0 10px rgba(0,0,0,0.5);
}
h1 { color: #38bdf8; }
.value { font-size: 20px; color: #22c55e; }
</style>
</head>
<body>

<h1>JVTECH ESP32</h1>

<div class="card">
  <h2>RAM</h2>
  <div class="value">)rawliteral";

    html += ESP.getFreeHeap();

    html += R"rawliteral( bytes</div>
</div>

<div class="card">
  <h2>Flash</h2>
  <div class="value">)rawliteral";

    html += ESP.getFlashChipSize();

    html += R"rawliteral( bytes</div>
</div>

<div class="card">
  <h2>CPU</h2>
  <div class="value">)rawliteral";

    html += getCpuFrequencyMhz();

    html += R"rawliteral( MHz</div>
</div>

<div class="card">
  <h2>Uptime</h2>
  <div class="value">)rawliteral";

    html += millis() / 1000;

    html += R"rawliteral( s</div>
</div>

<div class="card">
  <h2>IP</h2>
  <div class="value">)rawliteral";

    html += WiFi.localIP().toString();

    html += R"rawliteral(</div>
</div>

</body>
</html>
)rawliteral";

    return html;
}

void handleRoot() {
    server.send(200, "text/html", getHTML());
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Conectando");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConectado!");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.begin();
}

void loop() {
    server.handleClient();
}