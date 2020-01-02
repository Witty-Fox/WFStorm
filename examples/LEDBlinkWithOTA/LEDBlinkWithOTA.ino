#include <WFStorm.h>

char *ssid = "YOURSSID";
char *password = "YOURPASS";

const int LED_PIN = 2;

void blink();

void setup()
{
  wfEnableLogging(); //Enable logging for wittyfox. Default baudrate is 115200

  /**
   * The wfConfigureOTA function takes three parameters. SSID, Password and wifi mode
   * In wifi mode WF_STATION, the ESP32 will connect to a network with the SSID and Password which are passed to the function
   * In wifi mode WF_AP, the ESP32 will host a wifi AP with the SSID and the Password passed to the fucntion
  */
  if (!wfConfigOTA(ssid, password, WF_AP))
  {
    Serial.println("OTA configuration failed. Please check network details.");
  }
  else
  {
    Serial.println("OTA configured");
  }

  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  blink(); //Blink the onboard LED on pin 2

  /**
       The wfHandleOTA function listens for OTA updates triggered from the arduino IDE
  */
  wfHandleOTA();
}

void blink()
{
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
