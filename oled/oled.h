#ifndef __OLED_H__
#define __OLED_H__
#include "../module_conf.h"
#include "i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

//Device Information
#define _oled_Adress 0x3c

struct oled_DisMode
{
    _ubase8 horiz;
    _ubase8 verti;
    _ubase8 page;
};

struct oled_Frame
{
    _ubase8 frame5;
    _ubase8 frame64;
    _ubase8 frame128;
    _ubase8 frame256;
    _ubase8 frame3;
    _ubase8 frame4;
    _ubase8 frame25;
    _ubase8 frame2;
};

struct oled_Dir
{
    _ubase8 right;
    _ubase8 left;
    _ubase8 up_right;
    _ubase8 uo_left;
};
extern struct oled_DisMode oled_DisMode;
extern struct oled_Frame oled_Frame;
extern struct oled_Dir oled_Dir;

void oledInit(void);
void oledCls(void);
void oledFill(void);
void oledOff(void);
void oledOn(void);
void oledStartPage(_ubase8 pag, _ubase8 seg);
void oledAreaHoriz(_ubase8 colu1, _ubase8 colu2);
void oledAreaVerti(_ubase8 page1, _ubase8 page2);
void oledStartLine(_ubase8 line);
void oledSetPos(_ubase8 x, _ubase8 y);
void oledDisplayMode(_ubase8 oled_DisMode);
void oledShowChar(_ubase8 x, _ubase8 y, _ubase8 chr, _ubase8 Char_Size);
void oledShowNum(_ubase8 x, _ubase8 y, _ubase8 num, _ubase8 len, _ubase8 size2);
void oledShowString(_ubase8 x, _ubase8 y, _ubase8 *chr, _ubase8 Char_Size);
void oledScroll(_ubase8 oled_Dir, _ubase8 oled_Frame, _ubase8 vs_page, _ubase8 vd_page, _ubase8 row);

#ifdef __cplusplus
}
#endif

#endif //__OLED_H__