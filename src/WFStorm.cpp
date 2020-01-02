#include "WFStorm.h"

static void setDefaultConfig();
static void wfLog(String msg);
static void wfLogln(String msg);

String mSSID = DEFAULT_WIFI_SSID;                 //Default SSID
String mPASS = DEFAULT_WIFI_PASS;                 //Default password
int mWifiMode = DEFAULT_WIFI_MODE;                //Default wifi mode
int wifiConnectionTimeout = DEFAULT_WIFI_TIMEOUT; //Default timeout
//TODO: add option to change timeout
static bool loggingEnabled = false;

/**
 * @brief This function configures wifi for ArduinoOTA on the WittyFox board
 * 
 */
bool wfConfigOTA(char *ssid, char *pass, int wifi_mode)
{
    bool config_valid = true;

    if (!(strlen(ssid) > 0))
    {
        wfLogln("SSID cannot be blank. Going to default config.");
        config_valid = false;
    }

    if (!(strlen(pass) >= 8))
    {
        wfLogln("Password should be minimum 8 characters. Going to default config.");
        config_valid = false;
    }

    if (config_valid)
    {
        mWifiMode = wifi_mode;
        mSSID = String(ssid);
        mPASS = String(pass);
    }

    if (mWifiMode == WF_STATION)
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(mSSID.c_str(), mPASS.c_str());
        wfLogln("Conecting to " + mSSID);
        unsigned long wifiConnectStartTime = millis();

        while (WiFi.status() != WL_CONNECTED)
        {
            wfLog(".");
            delay(100);

            if (millis() - wifiConnectStartTime > wifiConnectionTimeout)
            {
                wfLogln("Unable to conect to WiFi station.");
                setDefaultConfig();
                config_valid = false;
                break;
            }
        }

        if (config_valid)
        {
            wfLogln("\nConnected successfully to " + mSSID);
            wfLog("IP address: ");
            wfLogln(WiFi.localIP().toString());
        }
    }
    else if (mWifiMode == WF_AP)
    {
        WiFi.mode(WIFI_AP);
        WiFi.softAP(mSSID.c_str(), mPASS.c_str());
        IPAddress IP = WiFi.softAPIP();
        wfLog("AP IP address: ");
        wfLogln(WiFi.softAPIP().toString());
    }
    else
    {
        wfLogln("Invalid wifi mode.");
        delay(1000);
        config_valid = false;
    }

    //TODO: add option to change following parameters
    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    // ArduinoOTA.setHostname("myesp32");

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            wfLogln("Start updating " + type);
        })
        .onEnd([]() {
            wfLogln("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            wfLogln("\n\n");
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                wfLogln("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                wfLogln("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                wfLogln("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                wfLogln("Receive Failed");
            else if (error == OTA_END_ERROR)
                wfLogln("End Failed");
        });

    ArduinoOTA.begin();

    return config_valid;
}

/**
 * @brief This functions handles requests on network to perform OTA upgrade to the WittyFox board
 * 
 */
void wfHandleOTA()
{
    ArduinoOTA.handle();
}

static void setDefaultConfig()
{
    wfLogln("Falling back to default config.");

    mSSID = DEFAULT_WIFI_SSID;
    mPASS = DEFAULT_WIFI_PASS;
    mWifiMode = DEFAULT_WIFI_MODE;
    wifiConnectionTimeout = DEFAULT_WIFI_TIMEOUT;

    WiFi.mode(WIFI_AP);
    WiFi.softAP(mSSID.c_str(), mPASS.c_str());
    IPAddress IP = WiFi.softAPIP();
    wfLog("AP IP address: ");
    wfLogln(WiFi.softAPIP().toString());
}

void wfEnableLogging(int baudrate)
{
    Serial.begin(baudrate);
    loggingEnabled = true;
}

void wfDisableLogging()
{

    loggingEnabled = false;
}

void wfLogln(String msg)
{
    if (msg.length() && loggingEnabled)
    {
        Serial.println(msg);
    }
}

void wfLog(String msg)
{
    if (msg.length() && loggingEnabled)
    {
        Serial.print(msg);
    }
}