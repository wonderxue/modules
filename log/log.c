#include "../module_conf.h"

#if (_log_level>0)
extern void _print(_base8 *str);
#endif
void _logReport(_ubase8 loglevel,_base8 *file,_base8 *function,_base8 *info)
{
    #if (_log_level>0)
    //error
    if(loglevel==1)
    {
        _print("<ERROR> $");
        _print(file);
        _print("$ @");
        _print(function);
        _print("@ ");
        _print(info);
    }
    #endif
    #if (_log_level>1)
    //warning
    if(loglevel==2)
    {
        _print("< WARN> $");
        _print(file);
        _print("$ @");
        _print(function);
        _print("@ ");
        _print(info);
    }
    #endif
    #if (_log_level>2)
    //normal log
    if(loglevel==3)
    {
        _print("< LOG > $");
        _print(file);
        _print("$ @");
        _print(function);
        _print("@ ");
        _print(info);
    }
    #endif
}