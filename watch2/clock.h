//
// Created by 陈辉鸿 on 2024/3/11.
//

#ifndef WATCH2_CLOCK_H
#define WATCH2_CLOCK_H

#include "Arduino.h"
#include "ui.h"
#include <time.h>
#include "font.h"

class Clock
{
public:
    void begin();
    void setTime();
    void setClock();
    const char *getWeekday(int tm_wday);

private:
    struct tm timeinfo;
};

#endif // WATCH2_CLOCK_H
