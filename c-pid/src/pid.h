/**
 ****************************************************************************
 * \file     pid.c
 * \author   zhao.zhan
 * \version  1.0
 * \date     2020.01.14
 * \brief    增量PID的实现
 ****************************************************************************
 */
#ifndef PID_H__
#define PID_H__

#include <stdio.h>

#define USE_DEBUG (0)

struct pid
{
	float point;		 /* 设置目标值 */
	float kp, ki, kd;	/* 比例, 积分, 微分常数 */
	float prve_error;	/* 前一次误差 */
	float prve_2_error;  /* 前两次误差 */
	float current_error; /* 当前的误差 */
};

void pid_init(struct pid *sptr, float point, float kp, float ki, float kd);
float pid_calc(struct pid *sptr, float feedback_value);

#endif /* PID_H__ */
