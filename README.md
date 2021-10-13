Arduino OTA handler for Wittyfox  StormBoard
----------
- [Arduino OTA handler for Wittyfox  StormBoard](#arduino-ota-handler-for-wittyfox-stormboard)
    - [Functions list](#functions-list)
  - [bool wfConfigOTA(char *ssid, char *pass, int wifi_mode);](#bool-wfconfigotachar-ssid-char-pass-int-wifimode)
    - [Default configuration](#default-configuration)
  - [void wfHandleOTA();](#void-wfhandleota)
  - [void wfLog(String msg);](#void-wflogstring-msg)
  - [void wfLogln(String msg);](#void-wfloglnstring-msg)
  - [void wfLoggingMode(int logging_mode);](#void-wfloggingmodeint-loggingmode)
  - [void wfSetWiFiLoggerProtocol(int proto);](#void-wfsetwifiloggerprotocolint-proto)
  - [void wfCheckLoggerClientConnection();](#void-wfcheckloggerclientconnection)
- [Example Codes](#example-codes)
  - [LEDBlinkWithOTA](#ledblinkwithota)
  - [Si7021WirelessLogging](#si7021wirelesslogging)
  - [WirelessLoggingTCP](#wirelessloggingtcp)
  - [WirelessLoggingUDP](#wirelessloggingudp)

This library includes code to allow the user to incorporate OTA functionality into their custom applications.

#### Functions list
  - wfConfigOTA: Configure the SSID and password and wifi mode for the ESP32
  - wfHandleOTA: Listen for incoming invitation for OTA firmware upgrade and perform OTA if an invitation is available
  - wfLog: Prints logs to the interface currently configured
  - wfLogln: Prints logs to the interface currently configured with an addiitional  carriage return and new line character at the end of the message
  - wfLoggingMode: This function sets the logging interface
  - wfSetWiFiLoggerProtocol: Selects the protocol to use in case wireless interface is selcted for logging

### bool wfConfigOTA(char *ssid, char *pass, int wifi_mode);

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

### void wfHandleOTA();

Listens for incoming invitations for OTA firmware update. It should be ensured that this function is called in every loop iteration without being blocked.

### void wfLog(String msg);

Prints the debug string message passed as argument to the selected logging interface. Check out the wfLoggingMode function to learn more about the Witty Fox logging interfaces.

### void wfLogln(String msg);

Same as the wfLog function, except, this adds an additional "\r\n" (carriage return and new line) character to the end of the debug message.

### void wfLoggingMode(int logging_mode);

This function is used to select the interface on which you would like to receive your debug messages printed using the wfLog function. The parameter logging_mode can be set to one of the following three options:

**LOGGING_SERIAL:** This sets the logging mode to the serial interface. (Similar to using Serial.print() or Serial.println())  
**LOGGING_WIFI:** This sets the logging mode to WiFi. Protocol for WiFi logging can be set using the wfSetWiFiLoggerProtocol. WiFi logging can be done using both TCP or UDP protocols.  
**LOGGING_WIFI_SERIAL:** This sets the logging mode to both serial as well as WiFI.

### void wfSetWiFiLoggerProtocol(int proto);

This function selects the protocol to be used for wireless logging. The parameter proto can be set to one of the following two options:

**PROTO_TCP:** Sets the WiFi logging to use the TCP protocol. The port on which the TCP logs are received is 3334.  
**PROTO_UDP:** Sets the WiFi logging to use the UDP protocol. UDP logs use port 3333. This is the default logging mode.  

**Note: TCP logger supports only a single TCP client at a time. All subsequent clients who try to connect will be rejected**  

### void wfCheckLoggerClientConnection();

This function checks for and acceptsconnections, if allowed, from any TCP client which tries to conenct to the Wittfy Fox Storm Board to receive TCP logs. This function is called internally as well, every time the wfLog or wfLogln functions are called with logging on WiFi mode with TCP protocol selected, but you may also call this function if you wish to accept TCP connections at any point in the code where wireless logs are not being sent (for example in a blocking loop with no calls to wfLog/wfLogln functions).

## Example Codes

### LEDBlinkWithOTA
This example demonstrates how to use the OTA functionality through a basic LED Blink code.


### Si7021WirelessLogging
This example demonstrates wireless logging of Si7021 sensor readings using the TCP protocol in addition to the Serial monitor. Connect to the Storm Board wifi AP and then connect to the mentioned TCP port in code to view the logs.

Note: Please install the [Adafruit_Si7021](https://github.com/adafruit/Adafruit_Si7021) library in order to compile this code.


### WirelessLoggingTCP
This example demonstrates wireless logging by printing "Hello World" using the TCP protocol in addition to the Serial monitor. Connect to the Storm Board wifi AP and then connect to the mentioned TCP port in code to view the logs.

### WirelessLoggingUDP
This example demonstrates wireless logging by printing "Hello World" using the UDP protocol in addition to the Serial monitor. Connect to the Storm Board wifi AP and then connect to the mentioned UDP port in code to view the logs.

