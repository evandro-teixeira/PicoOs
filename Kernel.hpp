/**
 * @file Kernel.hpp
 * @author Evandro Teixeira
 * @brief 
 * @version 0.1
 * @date 12-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdint.h>
#include <stdbool.h>

#define NUMBER_TASK 8
//#define NUMBER_CPU      2

typedef void (*ptrTask_t)(void);
typedef uint8_t idTask_t;

typedef enum
{
    CPU_Task_Release = 0,
    CPU_Task_Request
} cpuTask_t;

typedef enum
{
    Core_Available = 0,
    Core_One,
    Core_Two,
    Core_Max
} coreTask_t;

typedef enum
{
    Running = 0,
    Ready,
    Blocked,
    Terminated,
} stsTask_t;

typedef struct
{
    ptrTask_t Task;
    stsTask_t Status;
    idTask_t IdTask;
    int32_t Ticks;
    cpuTask_t CpuTask;
    coreTask_t Core;
} strTask_t;

typedef struct
{
    strTask_t Tasks[NUMBER_TASK];
    uint8_t Index;
    uint8_t CounterTask = 0;
    //uint32_t Systick;
    bool Enable;
} strKernel_t;

class Kernel
{
private:
    //strKernel_t Parameters;
    //strTask_t Scheduler(void);
    //bool Core(strTask_t task);
    //void MainCPU(void);
    //ptrTask_t SecondaryCPU;
    //void SecondaryCPU(void);
public:
    //strKernel_t
    //Kernel(/* args */);
    //~Kernel();
    bool Init(void);
    bool AddTask(ptrTask_t task, idTask_t *idTask, coreTask_t core);
    void Run(void);
    bool TaskDelay(idTask_t idTask, uint32_t tick);
    bool Release(idTask_t idTask);
    bool Request(idTask_t idTask);
    bool TaskUnlock(idTask_t idTask);
    bool TaskLock(idTask_t idTask);
};

extern Kernel PicoOs;