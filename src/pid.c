
#include "pid.h"
#include <math.h>

void pid_init(struct pid *sptr, const float point, const float kp, const float ki, const float kd)
{
    sptr->point = point;

    sptr->kp = kp;
    sptr->ki = ki;
    sptr->kd = kd;

    sptr->prve_error = 0;
    sptr->prve_2_error = 0;

    sptr->current_error = 0;

#if USE_DEBUG != 0
    printf("---------------------------.\n");
    printf("kp is %f.\n", sptr->kp);
    printf("ki is %f.\n", sptr->ki);
    printf("kd is %f.\n", sptr->kd);
    printf("point is %f.\n", sptr->point);
    printf("---------------------------.\n");
#endif 
}

float pid_calc(struct pid *sptr, float feedback_value)
{
    float iinc_pid;

    //当前误差
    sptr->current_error = sptr->point - feedback_value;

    iinc_pid = sptr->kp * (sptr->current_error - sptr->prve_error) /* 计算增量误差 */
               + (sptr->ki * sptr->current_error) + (sptr->kd * (sptr->current_error - 2 * sptr->prve_error + sptr->prve_2_error));

#if USE_DEBUG != 0
    printf("current_error[%f], prve_error[%f], prve_2_error[%f], iinc_pid[%f].\n",
           sptr->current_error, sptr->prve_error, sptr->prve_2_error, iinc_pid);
#endif 

    //存储误差，用于下次计算
    sptr->prve_2_error = sptr->prve_error;
    sptr->prve_error = sptr->current_error;

    return iinc_pid;
}
