# ESP8266 WiFi Access Point with Redirect

This Arduino project sets up an ESP8266 WiFi access point (AP) that provides a simple welcome page and redirects clients to another page. It is designed to raise awareness of network security issues and collect statistics on connections to potentially unsafe networks.

## Features

- Configurable WiFi Access Point with the SSID "Free WiFi."
- Redirects all client requests to a welcome page.
- Provides a welcome page with information about the project and a link to support the author.
- Supports a basic HTML template with inline CSS styling.

## Getting Started

### Prerequisites

1. Arduino IDE installed.
2. ESP8266 board support installed in the Arduino IDE.
3. Required libraries installed: `ESP8266WiFi`, `DNSServer`, `ESP8266WebServer`.

### Installation

1. Open the Arduino IDE.
2. Install the required libraries if not already installed (`ESP8266WiFi`, `DNSServer`, `ESP8266WebServer`).
3. Copy and paste the provided Arduino code into a new sketch.
4. Upload the sketch to your ESP8266 board.

## Usage

1. Power up your ESP8266 board.
2. Connect to the WiFi network with the SSID "Free WiFi."
3. Open a web browser and enter any URL; you will be redirected to the welcome page.

## Customization

- You can customize the SSID_NAME, APIP, and other parameters in the code according to your preferences.
- Modify the HTML template (`htmlTemplate`) to change the content and styling of the welcome page.

## Author

- Konstie

## Support

If you find this project useful and would like to support the author, consider [buying them a coffee](https://www.buymeacoffee.com/konstie).
