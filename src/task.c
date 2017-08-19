/** @file      task.c 
 *  @brief     POSIX消息队列，多线程之间的通信
 *  @note      
 *  @note      
 *  @author   zhangyinliang
 *  @date     2017.08.18
 *  @version   v1.0
*/
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/fun.h"

//创建消息名
char *mq_name = (char*)"/MQ_Msg";

#define MSG_SIZE 512

//定义消息
struct myMsg
{
    int number1;
    int number2;
    int cal_type;
};

//定义计算类型
enum calType
{
    Add=1,
    Subtract,
    Multiply,
    Divide
};

//发送线程函数
void* thread_send()
{
	int flags = 0;
    mqd_t mqd;
    flags = O_RDWR | O_CREAT;
    struct mq_attr attr;
    long int msgsize = 1024;
    long int maxmsg = 200;
    //消息优先级
    unsigned int prio = 1;
    
    struct myMsg msg;
    int number1,number2;
    int cal_type;
 
    attr.mq_msgsize = msgsize;
    attr.mq_maxmsg = maxmsg;
    
    memset(&msg,0,sizeof(struct myMsg));
 
    mqd = mq_open(mq_name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, &attr);
 
    if (mqd == -1)
    {
        printf("mq create error\n");
        return 0;
    }
 
    printf("Create MQ success!\nMax msgs = %ld, Max bytes/msg = %ld\n", attr.mq_maxmsg, attr.mq_msgsize);
 
    while (1)
    {
        //选择计算类型
        printf("******please choose the calculation type number******\n");
        printf("1:add\n");
        printf("2:subtract\n");
        printf("3:multiply\n");
        printf("4:divide\n");
        printf("5:exit\n");
        scanf("%d", &cal_type);
        
        //判断是否退出计算
        if(5==cal_type)
        {
            msg.cal_type = cal_type;
            if ( -1 == (mq_send(mqd, (char *)&msg, msgsize, prio)))
            {
                perror("msg closed! quit the system!\n");
                break;
            }
            break;
        }
        
        printf("calculation type number= %d\n", cal_type);
        fflush(stdin);
        fflush(stdout);
        msg.cal_type = cal_type;
        
        //输入第一个数
        printf("Input the number1: ");
        scanf("%d", &number1);
        printf("number1 = %d\n",number1);
        fflush(stdin);
        fflush(stdout);
        msg.number1=number1;
        
        //输入第二个数
        printf("Input the number2: ");
        scanf("%d", &number2);
        printf("number2 = %d\n",number2);
        fflush(stdin);
        fflush(stdout);
        msg.number2=number2;
        
        //检查数据除法输入是否正确
        while(Divide==(enum calType)cal_type&&0==number2)
        {
            printf("Input wrong, please input the number2 again: ");
            scanf("%d", &number2);
            printf("number2 = %d\n",number2);
            fflush(stdin);
            fflush(stdout);
            msg.number2=number2;
        }
    
        if ( -1 == (mq_send(mqd, (char *)&msg, msgsize, prio)))
        {
            perror("msg closed! quit the system!\n");
            break;
        }
        printf("Send msg success!\n");
        sleep(2);
    }
 
    mq_close(mqd);
    printf("exit send pthread\n");
	//退出线程
	pthread_exit(NULL);
}

//接收线程函数
void* thread_receive()
{
	mqd_t mqd;
    int flags = 0;
    unsigned int prio = 0;
    struct myMsg msg;
    struct mq_attr attr;
    int i=0;
    int result=0;
 
    flags = O_RDONLY;
    mqd = mq_open(mq_name, flags);
    if (mqd == -1)
    {
        printf("mq open error\n");
        return 0;
    }
 
    mq_getattr(mqd, &attr);

    while (1)
    {
        //注意搞清楚，该消息队列接收函数中各个参数的含义
        if (mq_receive(mqd, (char *)&msg, attr.mq_msgsize, &prio))
        {
            if(5==msg.cal_type)
            {
                break;
            }
            printf("Receive msg success!\n");
            for(i=0;i<MAX_FUN;i++)
            {
                if(msg.cal_type==out_fun[i].item)
                {
                    result=(*out_fun[i].out)(msg.number1,msg.number2);   
                    printf("calculation result: %d\n",result);
                }
            } 
         }    
    }
 
    mq_close(mqd);
    printf("exit receive pthread\n");
	//退出线程
	pthread_exit(NULL);
}

void init_task()
{
	int res = -1;
	pthread_t send_thread, receive_thread;
	void *thread_result = NULL;
	
	//创建发送线程
	res = pthread_create(&send_thread, NULL, thread_send, NULL);
	if(res != 0)
	{
		perror("send pthread_create failed\n");
		exit(EXIT_FAILURE);
	}
	
    //创建接收线程
	res = pthread_create(&receive_thread, NULL, thread_receive, NULL);
	if(res != 0)
	{
		perror("receive pthread_create failed\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Waiting for thread to finish...\n");
	
	//等待子线程结束
	res = pthread_join(send_thread, &thread_result);
	if(res != 0)
	{
		perror("send pthread_join failed\n");
		exit(EXIT_FAILURE);
	}
	res = pthread_join(receive_thread, &thread_result);
	if(res != 0)
	{
		perror("receive pthread_join failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	
	exit(EXIT_SUCCESS);
}
