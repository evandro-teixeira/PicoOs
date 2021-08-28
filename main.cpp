/**
 * @file main.cpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 13-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "Kernel.hpp"

/* Regular Colors */
#define COLOR_BLACK			"\e[0;30m"	// Black
#define COLOR_RED			"\e[0;31m"	// Red
#define COLOR_GREEN			"\e[0;32m"	// Green
#define COLOR_YELLOW		"\e[0;33m"	// Yellow
#define COLOR_BLUE			"\e[0;34m"	// Blue
#define COLOR_PURPLE		"\e[0;35m"	// Purple
#define COLOR_CYAN			"\e[0;36m"	// Cyan
#define COLOR_WRITE			"\e[0;37m"	// White
#define COLOR_RESET			"\e[0m"		// Reset
/* Background */

#define DEBUG_APP           0
#define PROCESS             0x00000FFF

/**
 * @brief 
 * 
 */
void App_TaskA(void);
void App_TaskB(void);
void App_TaskC(void);
void App_TaskD(void);
void App_TaskE(void);
void App_TaskF(void);
void App_Process(uint32_t p);

idTask_t IdTaskA,IdTaskB,IdTaskC,IdTaskD,IdTaskE,IdTaskF;

int main()
{
    stdio_init_all();

    printf("\n\r\n\r\n\r\n\rTeste Raspberry Pi Pico OS ");
    
    PicoOs.Init();
    
    PicoOs.AddTask(App_TaskA,&IdTaskA,Core_Available);
    PicoOs.AddTask(App_TaskB,&IdTaskB,Core_Available);
    PicoOs.AddTask(App_TaskC,&IdTaskC,Core_Available);
    PicoOs.AddTask(App_TaskD,&IdTaskD,Core_Available);
    PicoOs.AddTask(App_TaskE,&IdTaskE,Core_Available);
    PicoOs.AddTask(App_TaskF,&IdTaskF,Core_Available);
    
    PicoOs.Run();

    while(1)
    {

    }

    return 0;
}

/**
 * 
 */
void App_TaskA(void)
{
#if DEBUG_APP
    printf("\n\r%s Task A %s",COLOR_YELLOW,COLOR_RESET);
#endif 
    //printf("\n\rTask A");
    //App_Process(2500);

    uint32_t i = 0;
    for(i=0;i<PROCESS;i++){}

    PicoOs.Release(IdTaskA);
}

/**
 * @brief 
 * 
 */
void App_TaskB(void)
{
#if DEBUG_APP
    printf("\n\r%s Task B %s",COLOR_RED,COLOR_RESET);
#endif 
    //App_Process(5000);
    //printf("\n\rTask B");

    uint32_t i = 0;
    for(i=0;i<PROCESS;i++){}

    PicoOs.Release(IdTaskB);
}

/**
 * @brief 
 * 
 */
void App_TaskC(void)
{
    static uint8_t number_request = 5;
#if DEBUG_APP
    printf("\n\r%s Task C %s",COLOR_BLUE,COLOR_RESET);
#endif 
    //App_Process(100);
    //printf("\n\rTask C");

    uint32_t i = 0;
    for(i=0;i<PROCESS;i++){}
    
    PicoOs.Release(IdTaskC);

    /*
    if(number_request > 0)
    {
        number_request--;
        PicoOs.Request(IdTaskC);
    }
    else 
    {
        PicoOs.Release(IdTaskC);
    }
    */
}

/**
 * @brief 
 * 
 */
void App_TaskD(void)
{
#if DEBUG_APP
    printf("\n\r%s Task D %s",COLOR_GREEN,COLOR_RESET);
#endif 
    //App_Process(1000);
    //printf("\n\rTask D");

    uint32_t i = 0;
    for(i=0;i<PROCESS;i++){}

    PicoOs.Release(IdTaskD);
    /*
    PicoOs.TaskDelay(IdTaskD,1000);
    */
}

/**
 * @brief 
 * 
 */
void App_TaskE(void)
{
    static uint8_t counter = 10;

    uint32_t i = 0;
    for(i=0;i<10000;i++){}

    PicoOs.Release(IdTaskE);

    //App_Process(1500);
    /*
    if(counter > 0)
    {
        counter--;
        PicoOs.TaskUnlock(IdTaskF);
    }
    else 
    {
        counter = 10;
        PicoOs.TaskLock(IdTaskF);
    }*/
#if DEBUG_APP
    printf("\n\r%s Task E %s",COLOR_PURPLE,COLOR_RESET);
    //printf("\n\rTask E");
#endif 
}

/**
 * @brief 
 * 
 */
void App_TaskF(void)
{
#if DEBUG_APP
    printf("\n\r%s Task F %s",COLOR_CYAN,COLOR_RESET);
#endif
    //App_Process(500);
    //printf("\n\rTask F");

    uint32_t i = 0;
    for(i=0;i<PROCESS;i++){}

    PicoOs.Release(IdTaskF);
}

/**
 * @brief 
 * 
 * @param p 
 */
void App_Process(uint32_t p)
{
    uint32_t i = 0;
    printf("\n\rProcess");
    for(i=0;i<p;i++)
    {
        printf("\n\r%d",i);
    }
}