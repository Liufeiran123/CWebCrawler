/*
 * CrawlerThread.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "CrawlerThread.h"

Crawler_Thread::Crawler_Thread(int id):value(1),identify(id) {
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
	pthread_mutex_unlock(&count_lock);
}


void Crawler_Thread::call(string a,void * b,void* c,void *d,void*e,void *f,void *g,void **y)
{
	if(a == "StartGetURL")
	{
		StartGetURL();
	}
}

int Crawler_Thread::start()
{
	//printf("ldksks\n");
	if(this->activate(THR_NEW_LWP | THR_JOINABLE, 1) == -1)
	{
// 		ACE_ERROR_RETURN ((LM_ERROR,
// 							ACE_TEXT ("%p.\n"),
// 							ACE_TEXT ("unable to activate thread pool")),
// 							-1);                            //by fzq
	//	LOGGER->AddLogger(LT_DEBUG_ERROR,ACE_TEXT("unable to activate thread pool")) ;
		printf("crawler_thread start fail\n");
		return -1 ;
	}

//	printf("ldksks45\n");
//	printf("lfrdreamman");
	return 0;
}

int Crawler_Thread::stop()
{

	return 0;
}

int Crawler_Thread::svc(void)
{
		while(1)
		{
		//从URL队列中提取URL
			if(URL_Queue_Singleton::instance()->isEmpty() !=0 )
			{
				ACE_OS::sleep(2);
			}
			else
			{
				string url = URL_Queue_Singleton::instance()->pop_queue();
				HTTP_URL hu(url);
				hu.URLParser(0);
				int ret = hu.gethostaddr();
				if(ret == -1)
				{
					continue;
				}
				//_mutex.acquire();
				pthread_mutex_lock(&count_lock);
				while(value == 0)
				{
					//cond.wait();
					printf("waiting pthread id is %d\n",identify);
					pthread_cond_wait(&count_nonzero, &count_lock);
					printf("end waiting id is %d\n",identify);
				}
				value =0 ;
				//_mutex.release();
				pthread_mutex_unlock(&count_lock);

				ACE_DEBUG ((LM_INFO, ACE_TEXT ("leaving the unlock\n")));
				//发送请求

				MessageBus::getInstance()->call(2,"MakeRequest",(void*)url.c_str(),(void*)hu.getip().c_str(),(void*)hu.gethost().c_str(),(void*)hu.getFile().c_str(),(void*)&identify,NULL,NULL);
				ACE_DEBUG ((LM_INFO, ACE_TEXT ("leaving MakeRequest\n")));
			}
		}
		return 0;
}
