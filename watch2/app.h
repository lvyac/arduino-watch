#ifndef WATCH_APP_H
#define WATCH_APP_H

#include <Arduino.h>
#include <Ticker.h>
#include "network.h"
#include "weather.h"
#include "http.h"
#include "clock.h"
#include "LGFX.h"
#include "CST816D.h"
#include "lvgl.h"
#include "ui.h"
#include "font.h"

#define I2C_SDA 4
#define I2C_SCL 5
#define TP_INT 0
#define TP_RST 1

#define off_pin 35
#define buf_size 120

#define is_touch 1

#define debug false

#endif //WATCH_APP_H