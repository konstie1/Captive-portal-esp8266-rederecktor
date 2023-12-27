#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const char* SSID_NAME = "Free WiFi";
const IPAddress APIP(172, 0, 0, 1);
const byte DNS_PORT = 53;
ESP8266WebServer webServer(80);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));

  WiFi.softAP(SSID_NAME);

  DNSServer dnsServer;
  dnsServer.start(DNS_PORT, "*", APIP);

  webServer.onNotFound([]() {
    webServer.sendHeader("Location", "http://www.youtube.com", true);
    webServer.send(302, "text/plain", "");
  });

  webServer.begin();
}

void loop() {
  webServer.handleClient();
}
