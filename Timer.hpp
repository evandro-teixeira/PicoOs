/**
 * @file Timer.hpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 28-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdint.h>

typedef void (*ptrFunc_t)(void);

class TimerSysTicks
{
private:
    /* data */
public:
    //TimerSysTicks(/* args */);
    //~TimerSysTicks();
    void Init(void);
    uint32_t Get(void);
    bool SetCallbacks(ptrFunc_t param);
};

extern TimerSysTicks TimeSysTicks;