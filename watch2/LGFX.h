#ifndef _LGFX_H
#define _LGFX_H

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_GC9A01 _panel_instance;

    lgfx::Bus_SPI _bus_instance;

public:
    LGFX(void);
};

#endif
