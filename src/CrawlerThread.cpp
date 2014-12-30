/*
 * CrawlerThread.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "CrawlerThread.h"

Crawler_Thread::Crawler_Thread():value(0) {
	// TODO Auto-generated constructor stub
	 pthread_mutex_init(&count_lock, NULL);
	 pthread_cond_init(&count_nonzero, NULL);

}

Crawler_Thread::~Crawler_Thread() {
	// TODO Auto-generated destructor stub
}

void Crawler_Thread::StartGetURL()
{
	//_mutex.acquire();
	pthread_mutex_lock(&count_lock);
	value =1 ;
	//cond.signal();
	pthread_cond_signal(&count_nonzero);
	//_mutex.release();
	pthread_mutex_lock(&count_lock);
}


void Crawler_Thread::call(string/*插件方法名*/ a,void * b,void* c,void *d,void*e,void *f,unsigned long&/*函数返回值*/)
{
	if(a == "StartGetURL")
	{
		StartGetURL();
	}
}
