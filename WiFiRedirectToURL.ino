#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const char* SSID_NAME = "Free WiFi";
const IPAddress APIP(172, 0, 0, 1);
const byte DNS_PORT = 53;
ESP8266WebServer webServer(80);

// Пример HTML-шаблона
const char* htmlTemplate = R"(
<!DOCTYPE html>
<html>
<head>
  <title>Redirected Page</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h1>You have been redirected!</h1>
  <p>This is a simple redirected page.</p>
</body>
</html>
)";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));

  WiFi.softAP(SSID_NAME);

  DNSServer dnsServer;
  dnsServer.start(DNS_PORT, "*", APIP);

  webServer.onNotFound([]() {
    webServer.sendHeader("Location", "/redirected", true);
    webServer.send(302, "text/plain", "");
  });

  // Добавляем обработчик для страницы /redirected
  webServer.on("/redirected", HTTP_GET, []() {
    webServer.send(200, "text/html", htmlTemplate);
  });

  webServer.begin();
}

void loop() {
  webServer.handleClient();
}
