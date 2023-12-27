#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const char* SSID_NAME = "Free WiFi";
const char* SUBTITLE = "Router info.";
const char* TITLE = "Update";
const char* BODY = "Your router firmware is out of date. Update your firmware to continue browsing normally.";
const char* POST_TITLE = "Updating...";
const char* POST_BODY = "Your router is being updated. Please wait until the process finishes.</br>Thank you.";
const char* CLEAR_TITLE = "Cleared";

const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
const IPAddress APIP(172, 0, 0, 1);

String currentSSID = "";

unsigned long lastTick = 0;

DNSServer dnsServer;
ESP8266WebServer webServer(80);

String footer() {
  return "</div><div class=q><a>&#169; All rights reserved.</a></div>";
}

String header(String t) {
  String a = String(currentSSID);
  String CSS = "article { background: #f2f2f2; padding: 1.3em; }"
               "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
               "div { padding: 0.5em; }"
               "h1 { margin: 0.5em 0 0 0; padding: 0.5em; }"
               "input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 0; border: 1px solid #555555; border-radius: 10px; }"
               "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
               "nav { background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
               "nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; } "
               "textarea { width: 100%; }";
  return "<!DOCTYPE html><html>"
         "<head><title>" + a + " :: " + t + "</title>"
         "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
         "<style>" + CSS + "</style>"
         "<meta charset=\"UTF-8\"></head>"
         "<body><nav><b>" + a + "</b> " + SUBTITLE + "</nav><div><h1>" + t + "</h1></div><div>";
}

String index() {
  return header(TITLE) + "<div>" + BODY + "</ol></div>" + footer();
}

String posted() {
  return header(POST_TITLE) + POST_BODY + footer();
}

String clear() {
  return header(CLEAR_TITLE) + "<div><p>The password list has been reseted.</div></p><center><a style=\"color:blue\" href=/>Back to Index</a></center>" + footer();
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));

  currentSSID = SSID_NAME;
  WiFi.softAP(currentSSID);

  dnsServer.start(DNS_PORT, "*", APIP);
  webServer.on("/post", []() { webServer.send(HTTP_CODE, "text/html", posted()); });
  webServer.on("/clear", []() { webServer.send(HTTP_CODE, "text/html", clear()); });

  // Modify the onNotFound handler
  webServer.onNotFound([]() {
    String redirectHtml = "<!DOCTYPE html><html lang=\"uk\">"
                          "<head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                          "<title>Ласкаво просимо!</title>"
                          "<style>body {font-family: 'Arial', sans-serif;background-color: #f4f4f4;color: #333;margin: 20px;text-align: center;}"
                          "h1 {color: #0066cc;}p {margin-bottom: 15px;line-height: 1.6;}a {color: #0066cc;text-decoration: none;font-weight: bold;}"
                          "a:hover {text-decoration: underline;}.container {max-width: 600px;margin: 0 auto;padding: 20px;background-color: #fff;"
                          "border-radius: 8px;box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);}.support-link {display: block;margin-top: 20px;padding: 10px;"
                          "background-color: #0066cc;color: #fff;border-radius: 5px;transition: background-color 0.3s ease;}.support-link:hover {background-color: #004080;}"
                          "</style></head>"
                          "<body><div class=\"container\"><h1>Ласкаво просимо!</h1>"
                          "<p>Ця сторінка створена в межах проекту, спрямованого на підвищення обізнаності щодо проблем інформаційної безпеки.</p>"
                          "<p>Наша мета - привернути увагу до питань безпеки в мережі та створити статистику, яка відображатиме підключення до небезпечних мереж.</p>"
                          "<p>Якщо ви хочете дізнатися більше про зібрану <b>статистику</b> або бажаєте <b>підтримати автора</b>, ми запрошуємо вас відвідати наступну сторінку:</p>"
                          "<a class=\"support-link\" href=\"https://www.buymeacoffee.com/konstie\">Підтримати автора</a></div></body></html>";

    webServer.send(200, "text/html", redirectHtml);
  });

  webServer.begin();
}

void loop() {
  if ((millis() - lastTick) > TICK_TIMER) {
    lastTick = millis();
  }

  dnsServer.processNextRequest();
  webServer.handleClient();
}
