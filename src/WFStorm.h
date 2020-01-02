#ifndef WFSTORM_H
#define WFSTORM_H

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define WF_STATION 1
#define WF_AP 2

#define DEFAULT_WIFI_SSID (char *)"Storm32"
#define DEFAULT_WIFI_PASS (char *)"wittyfox"
#define DEFAULT_WIFI_MODE WF_AP
#define DEFAULT_WIFI_TIMEOUT 15000

bool wfConfigOTA(char *ssid, char *pass, int wifi_mode);
void wfHandleOTA();
void wfEnableLogging(int baudrate = 115200);
void wfDisableLogging();

#endif