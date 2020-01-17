#include <WFStorm.h>
#include "Adafruit_Si7021.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

char *ssid = "YOURSSID";
char *password = "YOURPASS";
int samplingInterval = 3000; //in ms

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

    Serial.println("Si7021 test!");

    if (!sensor.begin())
    {
        Serial.println("Did not find Si7021 sensor!");
        while (true)
            ;
    }

    Serial.print("Found model ");
    switch (sensor.getModel())
    {
    case SI_Engineering_Samples:
        Serial.print("SI engineering samples");
        break;
    case SI_7013:
        Serial.print("Si7013");
        break;
    case SI_7020:
        Serial.print("Si7020");
        break;
    case SI_7021:
        Serial.print("Si7021");
        break;
    case SI_UNKNOWN:
    default:
        Serial.print("Unknown");
    }
    Serial.print(" Rev(");
    Serial.print(sensor.getRevision());
    Serial.print(")");
    Serial.print(" Serial #");
    Serial.print(sensor.sernum_a, HEX);
    Serial.println(sensor.sernum_b, HEX);
}

void loop()
{
    wfLog("Humidity:    ");
    wfLog(String(sensor.readHumidity()));
    wfLog("\tTemperature: ");
    wfLogln(String(sensor.readTemperature()));

    unsigned long int last = millis();

    while (millis() - last < samplingInterval)
    {
        wfHandleOTA();
        delay(10);
    }
}