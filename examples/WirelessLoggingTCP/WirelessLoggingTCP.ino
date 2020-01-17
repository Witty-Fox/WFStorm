#include <WFStorm.h>

char *ssid = "YOURSSID";
char *password = "YOURPASS";
int i = 0;

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

    wfLoggingMode(LOGGING_WIFI_SERIAL);
    wfSetWiFiLoggerProtocol(PROTO_TCP); // TCP port is 3334
}

void loop()
{
    wfLogln("Hello world " + String(i++));
    wfHandleOTA();
    delay(100);
}