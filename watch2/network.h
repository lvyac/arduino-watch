#ifndef _UI_NETWORK_H
#define _UI_NETWORK_H

#include "Arduino.h"
#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include "lvgl.h"
#include "ui.h"

void timeavailable(struct timeval *t);

class Network
{
private:
    // NTPClient ntpClient;
    // WiFiUDP ntpUDP;
    const char *ntpServer1 = "ntp.aliyun.com";
    const char *ntpServer2 = "ntp2.aliyun.com";
    const char *ntpServer3 = "time.nist.gov";
    const long gmtOffset_sec = 28800; // 时区偏移：8*60*60
    const int daylightOffset_sec = 0;
    const char *time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";

public:
    void ntp_begin(void (*timeavailable)(struct timeval *t));
    void wifi_begin(const String &ssid, const String &pwd);
    void set_wifi();
    void scanWiFiNetwork();
    int getWifiStatus();
};

#endif