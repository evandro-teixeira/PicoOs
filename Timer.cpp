/**
 * @file Timer.cpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 28-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stddef.h>
#include "Timer.hpp"
#include "hardware/timer.h"
#include "hardware/structs/systick.h"



/** @brief  */
TimerSysTicks TimeSysTicks;
uint32_t Ticks;
ptrFunc_t IrqSysTicks = NULL;

/**
 * @brief 
 */
//TimerSysTicks::TimerSysTicks(/* args */)
//{
//}

/**
 * @brief Destroy the Timer Sys Ticks:: Timer Sys Ticks object
 */
//TimerSysTicks::~TimerSysTicks()
//{
//}

/**
 * @brief 
 * 
 */
void TimerSysTicks::Init(void)
{
    systick_hw->csr = 0; 	    // Disable 
    systick_hw->rvr = 124999UL; // Standard System clock (125Mhz)/ (rvr value + 1) = 1ms 
    systick_hw->csr = 0x7;      // Enable Systic, Enable Exceptions	

    Ticks = 0;
}

/**
 * @brief 
 * 
 * @return uint32_t 
 */
uint32_t TimerSysTicks::Get(void)
{
    return Ticks;
}

/**
 * @brief 
 * 
 * @param param 
 * @return true 
 * @return false 
 */
bool TimerSysTicks::SetCallbacks(ptrFunc_t param)
{
    if((param != NULL) && (IrqSysTicks != NULL))
    {
        IrqSysTicks = param;
        return true;
    }
    else 
    {
        return false;
    }
}

/**
 * @brief 
 * @note Rewrite of weak systick IRQ in crt0.s file
 * 
 */
extern void isr_systick(void) 
{
    Ticks++;
    if(IrqSysTicks != NULL)
    {
        IrqSysTicks();
    }
}
