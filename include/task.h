/** @file      task.h 
 *  @brief     POSIX消息队列，多线程之间的通信
 *  @note      
 *  @note      
 *  @author   zhangyinliang
 *  @date     2017.08.18
 *  @version   v1.0
*/
#ifndef _TASK_H
#define _TAKS_H

#include "/home/zhang-yinliang/zyl/message/fun/fun.h"
 
#define MAX_FUN 5

typedef int (*OUT)(int num1,int num2);

typedef struct {
    int item;
    OUT out;
}OUT_FUN;

void thread(void);

static OUT_FUN out_fun[MAX_FUN]={
    {1,add},
    {2,subtract},
    {3,multiply},
    {4,divide}
};

void init_task();

#endif
