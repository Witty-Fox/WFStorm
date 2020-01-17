#ifndef WFSTORM_H
#define WFSTORM_H

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>

#define WF_STATION 1
#define WF_AP 2

#define UDP_LOGGING_PORT 3333
#define TCP_LOGGING_PORT 3334
#define PROTO_UDP 1
#define PROTO_TCP 2

#define LOGGING_SERIAL 1
#define LOGGING_WIFI 2
#define LOGGING_WIFI_SERIAL 3

#define DEFAULT_WIFI_SSID (char *)"Storm32"
#define DEFAULT_WIFI_PASS (char *)"wittyfox"
#define DEFAULT_WIFI_MODE WF_AP
#define DEFAULT_WIFI_TIMEOUT 15000

bool wfConfigOTA(char *ssid, char *pass, int wifi_mode);
void wfHandleOTA();
void wfEnableLogging(int baudrate = 115200);
void wfLoggingMode(int logging_mode);
void wfDisableLogging();
void wfLogln(String msg);
void wfLog(String msg);
void wfSetWiFiLoggerProtocol(int proto);
void wfCheckLoggerClientConnection();

#endif