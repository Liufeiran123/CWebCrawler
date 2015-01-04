/*
 * mainfile.cpp

 *
 *  Created on: 2014年12月29日
 *      Author: lfr
 */
#include <stdio.h>
#include "ace/Reactor.h"
#include "ace/Dev_Poll_Reactor.h"
#include "CrawlerEntity.h"
#include "TP_Task.h"
#include "URLQueue.h"
#include "CrawlerThread.h"


int main()
{
	ACE_Dev_Poll_Reactor * reactor_impl;
	ACE_Reactor *reactor;
	ACE_NEW_RETURN(reactor_impl, ACE_Dev_Poll_Reactor(), -1);
	reactor_impl->restart(true);
	ACE_NEW_RETURN(reactor, ACE_Reactor(reactor_impl, 1), -1);
	ACE_Reactor::instance(reactor);




	printf("lll1\n");
	TP_Task tp(1);
	tp.start();

	printf("lll2\n");

	//Crawler_Thread *ce1 = new Crawler_Thread();
	//ce1->start();
	CrawlerEntity ce;
	ce.InitURL("/home/lfr/workspace3/crawler/Debug/initurl");
	ce.StartEntity();

/*	Crawler_Thread *ct = new Crawler_Thread;
	Fetcher *fe = new Fetcher;
	DocQueue *dq = new DocQueue;
	HtmlParser* hp = new HtmlParser;


	MessageBus::getInstance()->add(1,dynamic_cast<MessageComponent*>(ct));
	MessageBus::getInstance()->add(2,dynamic_cast<MessageComponent*>(fe));
	MessageBus::getInstance()->add(3,dynamic_cast<MessageComponent*>(dq));
	MessageBus::getInstance()->add(4,dynamic_cast<MessageComponent*>(hp));

	ct->start();
	hp->start();*/
	printf("lll3\n");
	int a;
	scanf("%d",&a);
	return 0;
}
