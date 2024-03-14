#include "LGFX.h"

LGFX::LGFX(void)
{
    auto cfg = _bus_instance.config();

    // SPI总线设置
    cfg.spi_host = SPI2_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = 80000000;
    cfg.freq_read = 20000000;
    cfg.spi_3wire = true;
    cfg.use_lock = true;
    cfg.dma_channel = SPI_DMA_CH_AUTO;
    cfg.pin_sclk = 6;
    cfg.pin_mosi = 7;
    cfg.pin_miso = -1;
    cfg.pin_dc = 2;

    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    // 设置显示面板控制
    auto panel_cfg = _panel_instance.config();
    panel_cfg.pin_cs = 10;
    panel_cfg.pin_rst = -1;
    panel_cfg.pin_busy = -1;
    panel_cfg.memory_width = 240;
    panel_cfg.memory_height = 240;
    panel_cfg.panel_width = 240;
    panel_cfg.panel_height = 240;
    panel_cfg.offset_x = 0;
    panel_cfg.offset_y = 0;
    panel_cfg.offset_rotation = 0;
    panel_cfg.dummy_read_pixel = 8;
    panel_cfg.dummy_read_bits = 1;
    panel_cfg.readable = false;
    panel_cfg.invert = true;
    panel_cfg.rgb_order = false;
    panel_cfg.dlen_16bit = false;
    panel_cfg.bus_shared = false;

    _panel_instance.config(panel_cfg);

    setPanel(&_panel_instance);
}
