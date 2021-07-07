#include "module_conf.h"

//log
#if (_log_level>0)
void _print(_base8 *str)
{
    //function can print string and not print '\n' automatically
    //print(str);
    //function only print char and not print '\n' automatically
    while(str!='\0')
        print(*str++);
}
//time delay
void _time_delayUs(_ubase16 time)
{

}
void _time_delayMs(_ubase16 time)
{

}
//gpio
void _gpio_Mode(_ubase8 gpioNum,_ubase8 gpioMode)
{
    if(gpioMode==_gpio_IN)
    {

    }
    if(gpioMode==_gpio_OUT)
    {

    }
}
_ubase8 _gpio_Read(_ubase8 gpioNum)
{

}
void _gpio_Write(_ubase8 gpioNum,_ubase8 gpioStatus)
{
    if(gpioStatus==_gpio_HIGH)
    {

    }
    else
    {

    }
}
#endif
