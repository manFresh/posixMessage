/** @file      main.c 
 *  @brief     POSIX消息队列，多线程之间的通信
 *  @note      
 *  @note      
 *  @author   zhangyinliang
 *  @date     2017.08.18
 *  @version   v1.0
*/
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/task.h"

int main()
{
    init_task();
    exit(EXIT_SUCCESS);
}


