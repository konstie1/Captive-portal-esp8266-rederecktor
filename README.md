# WiFi Redirect to URL

This Arduino project creates a WiFi access point and redirects connected devices to a specified URL.

## Usage

1. **Hardware Setup:**
   - Connect your ESP8266 board to your computer.
   - Open the Arduino IDE.
   - Make sure you have the ESP8266 board installed in the Arduino IDE.

2. **Code Setup:**
   - Open the "WiFiRedirectToURL.ino" file in the Arduino IDE.
   - Modify the `redirectURL` variable in the code to the desired URL.
   - Verify and upload the code to your ESP8266 board.

3. **Connect to WiFi:**
   - Once the code is uploaded, the ESP8266 will create a WiFi access point named "Free WiFi".
   - Connect your device to this WiFi network.

4. **Automatic Redirection:**
   - Open a web browser on the connected device.
   - Enter any URL in the address bar.
   - The ESP8266 will automatically redirect you to the specified URL.

## Notes:
- This project uses the ESP8266 board as a standalone access point.
- Ensure that your device has a web browser to observe the redirection.

