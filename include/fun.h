/** @file      fun.h 
 *  @brief     POSIX消息队列，多线程之间的通信
 *  @note      
 *  @note      
 *  @author   zhangyinliang
 *  @date     2017.08.18
 *  @version   v1.0
*/
#ifndef _FUN_H
#define _FUN_H

int add(int number1,int number2);
int subtract(int number1,int number2);
int multiply(int number1,int number2);
int divide(int number1,int number2);

#define MAX_FUN 5

typedef int (*OUT)(int num1,int num2);

typedef struct {
    int item;
    OUT out;
}OUT_FUN;

static OUT_FUN out_fun[MAX_FUN]={
    {1,add},
    {2,subtract},
    {3,multiply},
    {4,divide}
};

#endif



