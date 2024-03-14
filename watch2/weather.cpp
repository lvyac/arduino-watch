#include "weather.h"

Weather::Weather(Http &httpClient)
    : httpClient(httpClient)
{
  daily_weather_url = "http://api.seniverse.com/v3/weather/daily.json?key=SGF-dGwDEzbox3-DJ&location=quanzhou&language=zh-Hans&unit=c&start=0&days=3";
  now_weather_url = "http://api.seniverse.com/v3/weather/now.json?key=SGF-dGwDEzbox3-DJ&location=quanzhou&language=zh-Hans&unit=c";
}

void Weather::getDailyWeather()
{
  String payload = httpClient.request(daily_weather_url, GET);

  StaticJsonDocument<2048> doc;

  DeserializationError error = deserializeJson(doc, payload);

  if (error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    // 添加错误处理逻辑，例如重试或记录错误信息
    int freeHeap = ESP.getFreeHeap();
    Serial.print("可用内存: ");
    Serial.println(freeHeap);
    return;
  }

  JsonArray dailyData = doc["results"][0]["daily"].as<JsonArray>();
  //清空面板内容
  lv_obj_clean(ui_weatherGroup);
  lv_obj_t *panels[dailyData.size()];
  // 处理获取到的天气数据
  for (size_t i = 0; i < dailyData.size(); i++)
  {
    JsonObject element = dailyData[i].as<JsonObject>();
    panels[i] = lv_obj_create(ui_weatherGroup);
    setStyleAndProperties(panels[i]);
    drawDailyWeather(element, panels[i]);
  }
}

//获取当前时间
void Weather::getCurrentWeather()
{
  String payload = httpClient.request(now_weather_url, GET);
  // Serial.println(payload.c_str());
  DynamicJsonDocument doc(1024);

  DeserializationError error = deserializeJson(doc, payload);
  if (error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  JsonObject currentWeater = doc["results"][0]["now"].as<JsonObject>();

  String temperature = currentWeater["temperature"].as<String>();
  String degree = "°c";
  String temperature_str = temperature + degree;
  lv_label_set_text(ui_temperatureText, temperature_str.c_str());
  String text = currentWeater["text"].as<String>();
  lv_label_set_text(ui_weatherText, text.c_str());
  lv_obj_set_style_text_font(ui_weatherText, &CHINESE, LV_PART_MAIN | LV_STATE_DEFAULT);
  return;
}


// 设置对象样式和属性
void Weather::setStyleAndProperties(lv_obj_t *weatherItem)
{
  lv_obj_set_width(weatherItem, lv_pct(33));
  lv_obj_set_height(weatherItem, lv_pct(100));
  lv_obj_set_align(weatherItem, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(weatherItem, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(weatherItem, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_clear_flag(weatherItem, LV_OBJ_FLAG_SCROLLABLE); /// Flags
  lv_obj_set_style_bg_color(weatherItem, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(weatherItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(weatherItem, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_opa(weatherItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(weatherItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(weatherItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(weatherItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(weatherItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(weatherItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void Weather::drawDailyWeather(const JsonObject &daily, lv_obj_t *weatherItem)
{

  // 天气
  lv_obj_t *text = lv_label_create(weatherItem);
  String text_day = daily["text_day"].as<String>();
  lv_label_set_text(text, text_day.c_str());
  setLabelStyles(text);
  lv_obj_set_style_text_font(text, &CHINESE, LV_PART_MAIN | LV_STATE_DEFAULT);

  // 温度
  lv_obj_t *temperature = lv_label_create(weatherItem);
  String temperature_high = daily["high"].as<String>();
  String temperature_low = daily["low"].as<String>();
  String degree = "°c";
  String _ = "~";
  String temperature_text = temperature_high + degree + _ + temperature_low + degree;
  lv_label_set_text(temperature, temperature_text.c_str());
  setLabelStyles(temperature);

  // 日期
  lv_obj_t *date = lv_label_create(weatherItem);
  String date_text = daily["date"].as<String>();
  //String date_m = date_text.substring(5, 5);
  lv_label_set_text(date, date_text.c_str());
  setLabelStyles(date);
}

void Weather::setLabelStyles(lv_obj_t *label)
{
  lv_obj_set_width(label, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
  lv_obj_set_align(label, LV_ALIGN_CENTER);
  lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
}
