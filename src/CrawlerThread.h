/*
 * CrawlerThread.h
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#ifndef CRAWLERTHREAD_H_
#define CRAWLERTHREAD_H_

#include "ace/Thread.h"
#include "ace/Synch.h"
#include "ace/Task_T.h"
#include "MessageComponent.h"
#include "URLQueue.h"
#include "HTTPURL.h"
#include "MessageBus.h"
#include "pthread.h"

class Crawler_Thread: public ACE_Task<ACE_NULL_SYNCH>,public MessageComponent {
public:
	Crawler_Thread();
	virtual ~Crawler_Thread();

public:
	int svc(void);
	virtual void call(string/*插件方法名*/,void *,void*,void *,void*,void *,void *,void **/*函数返回值*/);
	void StartGetURL();
	int start();
	int stop();
private:
	int value;
//	ACE_Thread_Mutex _mutex;
//	ACE_Condition<ACE_Thread_Mutex> cond(_mutex);

	pthread_mutex_t count_lock;
	pthread_cond_t count_nonzero;
};

#endif /* CRAWLERTHREAD_H_ */
