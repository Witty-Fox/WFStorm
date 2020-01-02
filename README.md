Arduino OTA handler for Wittyfox  StormBoard
----------
- [Arduino OTA handler for Wittyfox StormBoard](#arduino-ota-handler-for-wittyfox-stormboard)
    - [Functions list](#functions-list)
    - [bool wfConfigOTA(char *ssid, char *pass, int wifi_mode);](#bool-wfconfigotachar-ssid-char-pass-int-wifimode)
    - [Default configuration](#default-configuration)
    - [void wfHandleOTA();](#void-wfhandleota)

This library includes code to allow the user to incorporate OTA functionality into their custom applications.

#### Functions list
  - wfConfigOTA: Configure the SSID and password and wifi mode for the ESP32
  - wfHandleOTA: Listen for incoming invitation for OTA firmware upgrade and perform OTA if an invitation is available

#### bool wfConfigOTA(char *ssid, char *pass, int wifi_mode);

| Parameter |       Description       |
| :-------: | :---------------------: |
|   ssid    |   ssid of the network   |
|   pass    | password of the network |
| wifi_mode |      mode of wifi       |

**ssid:** In AP mode, this parameter defines the SSID of the AP that the ESP32 will host. In STATION mode, this parameter defines the SSID of the network the ESP will try to connect to. SSID cannot be an empty string. If ssid passed is an empty string, ESP will go into AP mode and host hotspot with the default credentials given below.

**pass:** In AP mode, this parameter defines the password of the AP that the ESP32 will host. In STATION mode, this parameter defines the passwrod of the network the ESP will try to connect to. Password has to be minimum 8 characters in length. If password is shorter that that, ESP will go into AP mode and host hotspot with the default credentials given below.

**wifi_mode** can take 2 values, WF_AP or WF_STATION. in WF_AP mode, the ESP32 will host a wifi hotspot with the SSID and password as passed in the first two arguments to the config function. In WF_STATION mode, the ESP32 will try to connect to a wifi network witht he SSID and password passed to the config function.

#### Default configuration

**SSID:** Storm32  
**PASSWORD:** wittyfox  
**wifi_mode:** WF_AP (AP mode)

All new wittyfox StormBoards ship with OTA firmware which puts the ESP32 into this default configuration.

#### void wfHandleOTA();

Listens for incoming invitations for OTA firmware update. It should be ensured that this function is called in every loop iteration without being blocked.