/**
 * @file Kernel.cpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 13-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Kernel.hpp"
#include <stddef.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/structs/systick.h"
#include "Timer.hpp"

/** @brief  */
/*
enum
{
    Core0 = 0,
    Core1,
    CoreMAX
};*/

/** @brief */
/*
enum 
{
    Available = 0,
    Busy, 
};*/

#define ENABLE          1
#define DISABLE         0
#define DEBUG_KERNEL    ENABLE


/**
 * @brief 
 * 
 */
Kernel PicoOs;
strKernel_t Parameters;
strTask_t Scheduler(uint8_t core);
//bool SemScheduler = Available;
void MainCPU(void);
void SecondaryCPU(void);
void IrqTimer(void);
//void init_systick(void);

///sys_timer systick;

//void init_systick(void)
//{ 
//	systick_hw->csr = 0; 	    //Disable /
//	systick_hw->rvr = 124999UL; //Standard System clock (125Mhz)/ (rvr value + 1) = 1ms 
//    systick_hw->csr = 0x7;      //Enable Systic, Enable Exceptions	
//}

//extern void isr_systick() //Rewrite of weak systick IRQ in crt0.s file
//{
//	//systick.u32_tick_count++;
//    Parameters.Systick++;
//    printf("\n\r %d",Parameters.Systick);
//}

/**
 * @brief 
 * 
 */
void MainCPU(void)
{
    strTask_t task;
    uint8_t core = 8;
    //uint16_t i = 0;
    while(1)
    {
        //Parameters.Tasks[0].Task();
        //printf("\n\rKernel MainCPU");
        //for(i=0;i<1000;i++);

        // Checa se Escalonador esta livre
        //while(SemScheduler) {};
        //SemScheduler = Busy;
        task = Scheduler(Core_One);
        //SemScheduler = Available;
        if(task.Task != NULL)
        {
            do
            {
                task.Task();
#if DEBUG_KERNEL
                printf("\n\rCore: %d Task: %d",core,task.IdTask); 
#endif /* DEBUG_KERNEL */
            }
            /* Checa se a tarefa solicitou o uso da CPU */ 
            while (task.CpuTask == CPU_Task_Request); 
            /* Informa que terminou de executar a tarefa */
            PicoOs.TaskUnlock( task.IdTask );
        }
    }
}

/**
 * @brief 
 * 
 */
void SecondaryCPU(void)
{
    strTask_t task;
    uint8_t core = 9;
    //uint16_t i = 0;
    while(1)
    {
        //add_alarm_in_ms
        //Parameters.Tasks[1].Task();
        //printf("\n\rKernel SecondaryCPU");
        //for(i=0;i<1250;i++);

        
        // Checa se Escalonador esta livre
        //while(SemScheduler) {};
        //SemScheduler = Busy;
        task = Scheduler(Core_Two);
        //SemScheduler = Available;

        if(task.Task != NULL)
        {
            do
            {
                task.Task();
#if DEBUG_KERNEL
                printf("\n\rCore: %d Task: %d",core,task.IdTask);
#endif /* DEBUG_KERNEL */
            }
            /* Checa se a tarefa solicitou o uso da CPU */ 
            while (task.CpuTask == CPU_Task_Request); 

            /* Informa que terminou de executar a tarefa */
            PicoOs.TaskUnlock( task.IdTask );
        }
    }
}

/**
 * @brief 
 * 
 */
void IrqTimer(void)
{
    uint8_t i = 0;
    if(Parameters.Enable == true)
    {
        for(i=0;i<Parameters.CounterTask;i++)
        {
            if(Parameters.Tasks[i].Status == Ready) 
            {
                Parameters.Tasks[i].Ticks--;
            }
        }
    }
}

/**
 * @brief 
 * 
 */
//Kernel::Kernel(/* args */)
//{}

/**
 * @brief Destroy the Kernel:: Kernel object
 * 
 */
//Kernel::~Kernel()
//{}

/**
 * @brief 
 * 
 * @return strTask_t 
 */
strTask_t Scheduler(uint8_t core)
{
    strTask_t task;
    uint8_t i = 0;
    
#if 0    
    for(i=Parameters.Index;i<Parameters.CounterTask;i++)
    {
        if((Parameters.Tasks[i].Status == Ready) && 
           ((Parameters.Tasks[i].Core  == core)  || 
            (Parameters.Tasks[i].Core  == Core_Available)))
        {
            Parameters.Tasks[i].Status = Running;
            task = Parameters.Tasks[i];
            Parameters.Index = i;
            break;
        }
    }

    Parameters.Index++;
    if(Parameters.Index > Parameters.CounterTask) Parameters.Index = 0; 
#else 



#endif


    return task;
}

/**
 * @brief 
 * 
 * @param task 
 * @return true 
 * @return false 
 */
//bool Kernel::Core(strTask_t task)
//{
//    return true;
//}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool Kernel::Init(void)
{
    uint8_t i = 0;

    TimeSysTicks.Init();
    TimeSysTicks.SetCallbacks(IrqTimer);

    Parameters.Index = 0;
    Parameters.CounterTask = 0;
    Parameters.Enable = false;
    for (i = 0; i < NUMBER_TASK; i++)
    {
        Parameters.Tasks[i].IdTask = 0;
        Parameters.Tasks[i].Status = Blocked;
        Parameters.Tasks[i].Task = NULL;
        Parameters.Tasks[i].Ticks = 0;
        Parameters.Tasks[i].CpuTask = CPU_Task_Release;
    }
   
    multicore_launch_core1(SecondaryCPU);
    return true;
}

/**
 * @brief 
 * 
 * @param task 
 * @return true 
 * @return false 
 */
bool Kernel::AddTask(ptrTask_t task, idTask_t *idTask,coreTask_t core)
{
    if ((Parameters.CounterTask < NUMBER_TASK) && (task != NULL) && (core < Core_Max))
    {
        Parameters.Tasks[Parameters.CounterTask].IdTask = Parameters.CounterTask + 1;
        Parameters.Tasks[Parameters.CounterTask].Status = Ready;
        Parameters.Tasks[Parameters.CounterTask].Task = task;
        Parameters.Tasks[Parameters.CounterTask].Ticks = 0;
        Parameters.Tasks[Parameters.CounterTask].CpuTask = CPU_Task_Release;
        Parameters.Tasks[Parameters.CounterTask].Core = core;
        Parameters.CounterTask++;
        *idTask = Parameters.Tasks[Parameters.CounterTask].IdTask;
        return true;
    }
    else
        return false;
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
void Kernel::Run(void)
{
    MainCPU();
    Parameters.Enable = true;
}

/**
 * @brief 
 * 
 * @param tick 
 */
bool Kernel::TaskDelay(idTask_t idTask,uint32_t tick)
{
    if (Parameters.CounterTask > --idTask)
    {
        Parameters.Tasks[idTask].Status = Blocked;
        Parameters.Tasks[idTask].Ticks = tick;
        return true;
    }
    else return false;
}

/**
 * @brief 
 * 
 */
bool Kernel::Release(idTask_t idTask)
{
    if (Parameters.CounterTask > --idTask)
    {
        Parameters.Tasks[idTask].CpuTask = CPU_Task_Release;
        //Parameters.Tasks[idTask].Status = Ready;
        return true;
    }
    else return false;
}

/**
 * @brief 
 * 
 */
bool Kernel::Request(idTask_t idTask)
{
    if (Parameters.CounterTask > --idTask)
    {
        Parameters.Tasks[idTask].CpuTask = CPU_Task_Request;
        //Parameters.Tasks[idTask].Status = Ready;
        return true;
    }
    else return false;
}

/**
 * @brief 
 * 
 * @param idTask 
 */
bool Kernel::TaskUnlock(uint8_t idTask)
{
    if (Parameters.CounterTask > --idTask)
    {
        Parameters.Tasks[idTask].Status = Ready;
        return true;
    }
    else
        return false;
}

/**
 * @brief 
 * 
 * @param idTask 
 */
bool Kernel::TaskLock(uint8_t idTask)
{
    if (Parameters.CounterTask > --idTask)
    {
        Parameters.Tasks[idTask].Status = Blocked;
        return true;
    }
    else
        return false;
}