/**
 ****************************************************************************
 * \file     main.c
 * \author   zhao.zhan
 * \version  1.0
 * \date     2020.01.14
 * \brief    增量PID控制的简单测试历程
 * \note     模拟pid温度采集控制
 ****************************************************************************
 */
#include <stdio.h>
#include <unistd.h>
#include "pid.h"

/* pid 的计算类 */
struct pid g_pid;

/* 实际的温度值 */
float temp_val = 0;

/**
 * \brief 模拟实际读到的温度值
 * \param none
 * \note none
 */
float read_real(void)
{
    return temp_val;
}

/**
 * \brief 模拟控制温度的变量, 实际中可能是控制风扇速度, 或者水循环，加热或冷却
 * \param val 通过pid计算后的模拟温度误差值
 * \note 这里为了模拟方便, 直接把温度拟合反馈到实际的读取温度上
 */
void set_real_val(float val)
{
    temp_val += val;
}

/*-----------------------------------------------------------------------------
 *  main loop
 *----------------------------------------------------------------------------*/

void main(void)
{
    int step;
    const int point = 1333;
    const float kp = 1;
    const float ki = 1.8;
    const float kd = 0;

    struct pid *ptr_pid = &g_pid;
    float sum_error;

    pid_init(ptr_pid, point, kp, ki, kd);

    while (1)
    {
        printf("STEP [%d]: temp val is [%f].\n", step, temp_val);
        sum_error += pid_calc(ptr_pid, read_real());
        set_real_val(sum_error);

        usleep(500000); /* 为了观测方便, 挂起进程0.5s */
        step++;         /* 步数, 为了检测方便  */

        /**
          * 模拟在现实环节中, 温度的突变，用于观测 Ki参数的意义。
          * 当Ki 值为0的时候, step>10 之后, 误差会持续增大,
          * 当加入积分后, 误差会缩小, 最终会消除静差
          */
        if (step > 10)
        {
            temp_val += step;
        }
    }
}
