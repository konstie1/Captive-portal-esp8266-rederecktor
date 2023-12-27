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
  <title>Перенаправление</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    // Простой JavaScript счетчик посещений
    document.addEventListener('DOMContentLoaded', function() {
      var counterElement = document.getElementById('counter');
      var currentCount = parseInt(counterElement.innerText);
      currentCount++;
      counterElement.innerText = currentCount;
    });
  </script>
</head>
<body>
  <h1>Вы были перенаправлены!</h1>
  <p>Это простая перенаправляющая страница.</p>
  <p>Автор: <a href="https://www.buymeacoffee.com/konstie">https://www.buymeacoffee.com/konstie</a></p>
  <p>Информация о проекте: Этот проект создан для отслеживания количества людей, подключающихся к небезопасной сети. Чтобы узнать больше о том, как работает проект, и получить доступ к статистике, рекомендуем подписаться <a href="https://www.buymeacoffee.com/konstie">здесь</a>.</p>
  <p>Счетчик посещений: <span id="counter">0</span></p>
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
