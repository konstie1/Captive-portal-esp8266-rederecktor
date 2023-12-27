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
<html lang="uk">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Ласкаво просимо!</title>
  <style>
    body {
      font-family: 'Arial', sans-serif;
      background-color: #f4f4f4;
      color: #333;
      margin: 20px;
      text-align: center;
    }

    h1 {
      color: #0066cc;
    }

    p {
      margin-bottom: 15px;
    }

    a {
      color: #0066cc;
      text-decoration: none;
      font-weight: bold;
    }

    a:hover {
      text-decoration: underline;
    }

    .container {
      max-width: 600px;
      margin: 0 auto;
      padding: 20px;
      background-color: #fff;
      border-radius: 8px;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Ласкаво просимо!</h1>
    <p>Ця сторінка створена в межах проекту, спрямованого на підвищення обізнаності щодо проблем інформаційної безпеки.</p>
    <p>Наша мета - привернути увагу до питань безпеки в мережі та створити статистику, яка відображатиме підключення до небезпечних мереж.</p>
    <p>Якщо ви хочете дізнатися більше про зібрану <b>статистику</b> або бажаєте <b>підтримати автора</b>, ми запрошуємо вас відвідати наступну сторінку:</p>
    <p><a href="https://www.buymeacoffee.com/konstie">Підтримати автора</a></p>
  </div>
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
