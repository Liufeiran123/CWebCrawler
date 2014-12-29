/*
 * CrawlerThread.h
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#ifndef CRAWLERTHREAD_H_
#define CRAWLERTHREAD_H_

#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"
#include "ace/Task_T.h"
#include "MessageComponent.h"
#include "URLQueue.h"

class Crawler_Thread: public ACE_Task<ACE_NULL_SYNCH>,public MessageComponent {
public:
	Crawler_Thread();
	virtual ~Crawler_Thread();

public:
//Implement the Service Initialization and Termination methods
	int open(void*)
	{
		ACE_DEBUG((LM_DEBUG,"(%t) Active Object opened \n"));
		//Activate the object with a thread in it.
		activate();
		return 0;
	}
	int close(u_long)
	{
		ACE_DEBUG((LM_DEBUG, "(%t) Active Object being closed down \n"));
		return 0;
	}
	int svc(void)
	{
		while(1)
		{
		//从URL队列中提取URL
			if(URL_Queue_Singleton::instance()->isEmpty() !=0 )
			{
				ACE_OS::sleep(1);
			}
			else
			{
				string url = URL_Queue_Singleton::instance()->pop_queue();
				HTTP_URL hu(url);
				hu.URLParser();
				int ret = hu.gethostaddr();
				if(ret == -1)
				{
					continue;
				}
				mutex.acqure();
				while(value == 0)
				{
					cond.wait();
				}
				value =1 ;
				mutex.release();

				//发送请求
				MessageBus::getInstance()->call(2,"MakeRequest",(void*)hu.getip().c_str(),(void*)hu.gethost().c_str(),(void*)hu.getFile().c_str(),NULL,NULL,NULL);
			}
		}
	}
public:
	virtual void call(string/*插件方法名*/,void *,void*,void *,void*,void *,void*/*函数返回值*/);
	void StartGetURL();
private:
	int value;

	ACE_Thread_Mutex mutex;
	ACE_Condition<ACE_Thread_Mutex> cond(mutex);
};

#endif /* CRAWLERTHREAD_H_ */
