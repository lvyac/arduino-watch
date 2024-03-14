#ifndef _UI_WEATHER_H
#define _UI_WEATHER_H

#define LV_LVGL_H_INCLUDE_SIMPLE

#include "Arduino.h"
#include <ArduinoJson.h>
#include <unordered_map>
#include "lvgl.h"
#include "ui.h"
#include "http.h"
#include "Network.h"
#include "font.h"

class Weather
{
private:
    const char *daily_weather_url = "http://api.seniverse.com/v3/weather/daily.json?key=SGF-dGwDEzbox3-DJ&location=quanzhou&language=zh-Hans&unit=c&start=0&days=3";
    const char *now_weather_url = "http://api.seniverse.com/v3/weather/now.json?key=SGF-dGwDEzbox3-DJ&location=quanzhou&language=zh-Hans&unit=c";
    mutable std::unordered_map<int, lv_img_dsc_t> code;
    Http &httpClient;

public:
    explicit Weather(Http& httpClient);
    void getDailyWeather();
    void getCurrentWeather();
    void drawDailyWeather(const JsonObject &daily, lv_obj_t *ui_weatherItem);
    void setLabelStyles(lv_obj_t *label);
    void setStyleAndProperties(lv_obj_t *weatherItem);
    // lv_img_dsc_t getWeatherCode(int code);
};

#endif