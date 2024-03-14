#define LGFX_USE_V1
#include "app.h"

bool ntpBegin = false;
bool wifiBegin = false;

Clock _clock{};
Network network{};
Http httpClient{};
Weather weather(httpClient);

Ticker time_ticker{};
Ticker weather_ticker{};

// 创建已准备类的实例。
LGFX tft;
CST816D touch(I2C_SDA, I2C_SCL, TP_RST, TP_INT);

/*屏幕分辨率*/
static const uint32_t screenWidth = 240;
static const uint32_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[2][screenWidth * buf_size];

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *fn_name, const char *dsc)
{
  Serial.printf("%s(%s)@%d->%s\r\n", file, fn_name, line, dsc);
  Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  if (tft.getStartCount() == 0)
  {
    tft.endWrite();
  }

  tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t *)&color_p->full);

  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{

  bool touched;
  uint8_t gesture;
  uint16_t touchX, touchY;

  touched = touch.getTouch(&touchX, &touchY, &gesture);

  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

    /*Set the coordinates*/
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

// 同步时间完成
void timeavailable(struct timeval *t)
{
  _clock.begin();
  ntpBegin = true;
}

void setTime()
{
  // 每分钟设置一次秒针动画
  _clock.setClock();
  // 每秒钟设置一次时间
  _clock.setTime();
}

void getWeather()
{
  weather.getCurrentWeather(); // 获取当前天气
  weather.getDailyWeather();   // 获取天气列表
}


// 初始化
void initial_action(lv_event_t *e)
{
  // 初始化网络
  network.wifi_begin("hxrc", "abcd123456789");
  while (network.getWifiStatus() == 0)
  {
    lv_label_set_text(ui_sysLoadTapsText, "WIFI connect...");
    delay(100);
  }
  wifiBegin = true;
  // 同步时间
  lv_label_set_text(ui_sysLoadTapsText, "WIFI connected");
  lv_label_set_text(ui_sysLoadTapsText, "sync time...");
  // 开始同步时间
  network.ntp_begin(timeavailable);
  lv_label_set_text(ui_sysLoadTapsText, "system ready");
  // 删除当前屏幕并切换到手表界面
  _ui_screen_delete(&ui_initScreen);
  _ui_screen_change(&ui_watchScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_watchScreen_screen_init);
  // 同步天气
  getWeather();
}

void setup()
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.println("system start");

  tft.init();
  tft.initDMA();
  tft.startWrite();
  tft.setColor(0, 0, 0);

  // if (is_touch == 1)
  // {
  //   touch.begin();
  // }

  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  lv_disp_draw_buf_init(&draw_buf, buf[0], buf[1], screenWidth * buf_size);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  if (is_touch == 1)
  {
    touch.begin();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
  }

#if 0
   /* Create simple label */
   lv_obj_t *label = lv_label_create( lv_scr_act() );
   lv_label_set_text( label, "Hello Arduino! (V8.0.X)" );
   lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
#else

  ui_init(); // watch
  time_ticker.attach(1, setTime);
  weather_ticker.attach(300, getWeather);

#endif
  Serial.println("Setup done");

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(0, INPUT);
}

// long currentTime = millis();

void loop()
{
  // if (millis() - currentTime > 10000)
  // {
  //   currentTime = millis();
  //   int freeHeap = ESP.getFreeHeap();
  //   Serial.print("可用内存: ");
  //   Serial.println(freeHeap);
  //   Serial.println("-----------------内存---------------------");
  // }

  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
