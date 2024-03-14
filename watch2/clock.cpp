
#include "clock.h"

void Clock::begin() {
  setTime();
  setClock();
  // 时间同步完成，加载动画
  timedot_Animation(ui_timedot, 0);
}

void Clock::setTime()
{
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }
    int _hour = timeinfo.tm_hour;
    int _minute = timeinfo.tm_min;
    int _weekday = timeinfo.tm_wday;
    int _sec = timeinfo.tm_sec;
    char hour[4];
    char min[4];
    char date[20];
    char taskText[20];

    strftime(date, sizeof(date), "%Y-%m-%d", &timeinfo);
    // 计算走完一天的百分比
    int16_t percentage = (_hour * 3600 + _minute * 60 + _sec) / (24.0 * 3600) * 100;
    //lv_arc_set_value(ui_taskArc, percentage);
    // String taskText = String(percentage) + "%";
    //sprintf(taskText, "%d%%", percentage);
    //lv_label_set_text(ui_tasktext, taskText);

    snprintf(hour, sizeof(hour), "%02d", _hour);
    snprintf(min, sizeof(min), "%02d", _minute);
    // sprintf(weekday, "%d", _weekday);
    lv_label_set_text(ui_hour, hour);
    lv_label_set_text(ui_minute, min);
    lv_label_set_text(ui_dateText, date);

    //设置星期
    const char *weekday = getWeekday(_weekday);
    lv_obj_set_style_text_font(ui_weekText, &CHINESE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_weekText, weekday);
    // int hour_angle = (_hour % 12 + _minute / 60 + _sec / 3600) * 30 * 10;
    // int minute_angle = (_minute + _sec / 60) * 6 * 10;


    
    // 秒针偏移
    // int second_angle = _sec * 6 * 10;
    // lv_img_set_angle(ui_dotimg, second_angle);
}

void Clock::setClock()
{
    if (timeinfo.tm_sec == 0)
    {
        Serial.println("Failed to obtain time");
        return;
    }
    //秒针动画
    lv_anim_del(ui_dotimg, 0); // 删除之前的动画，并重新开始
    int _sec = timeinfo.tm_sec;
    int second_angle = _sec * 6 * 10 + 6;
    // 秒针偏移
    lv_img_set_angle(ui_dotimg, second_angle);
    dot_a_Animation(ui_dotimg, 0);
}

const char *Clock::getWeekday(int tm_wday)
{
    static const char *weekdayArr[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};

    if (tm_wday >= 0 && tm_wday < 7)
    {
        return weekdayArr[tm_wday];
    }

    return "未知";
}