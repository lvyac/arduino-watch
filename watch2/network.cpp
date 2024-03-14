#include "network.h"

void Network::ntp_begin(void (*timeavailable)(struct timeval *t))
{
    sntp_set_time_sync_notification_cb(timeavailable);
    sntp_servermode_dhcp(1);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2, ntpServer3);
}


void Network::wifi_begin(const String &ssid, const String &pwd)
{
    WiFi.begin(ssid.c_str(), pwd.c_str());
}

void Network::set_wifi()
{
//    const char *ssid = lv_dropdown_get_text(ui_Dropdown1);
//    const char *pwd = lv_textarea_get_text(ui_WiFiPwdTextArea);
//    WiFi.begin(ssid, pwd);
//    while (WiFi.status() != WL_CONNECTED)
//    {
//        Serial.print(".");
//        Serial.println(WiFi.status());
//        delay(500);
//    }
//    Serial.println(WiFi.localIP());
//    Serial.println(ssid);
//    Serial.println(pwd);
}

// 列表可用的 wifi 名称
void Network::scanWiFiNetwork()
{
    int networkCount = WiFi.scanNetworks();
    for (int i = 0; i < networkCount; i++)
    {
        Serial.println(WiFi.SSID(i).c_str());
    }
}

int Network::getWifiStatus()
{
    return WiFi.status() == WL_CONNECTED;
}

