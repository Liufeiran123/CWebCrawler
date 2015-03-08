/*
 * mainfile.cpp

 *
 *  Created on: 2014年12月29日
 *      Author: lfr
 */
#include <stdio.h>
#include <boost/filesystem.hpp>
#include "ace/Reactor.h"
#include "ace/Dev_Poll_Reactor.h"
#include "CrawlerEntity.h"
#include "TP_Task.h"
#include "URLQueue.h"
#include "CrawlerThread.h"
#include "DBManager.h"

using namespace boost::filesystem;

int main()
{
	//删除数据库文件
	remove("/home/lfr/workspace3/crawler/crawlerurl.db");
	remove("/home/lfr/workspace3/crawler/urlq.db");


	ACE_Dev_Poll_Reactor * reactor_impl;
	ACE_Reactor *reactor;
	ACE_NEW_RETURN(reactor_impl, ACE_Dev_Poll_Reactor(), -1);
	reactor_impl->restart(true);
	ACE_NEW_RETURN(reactor, ACE_Reactor(reactor_impl, 1), -1);
	ACE_Reactor::instance(reactor);

	TP_Task tp;
	tp.start();


	CrawlerEntity ce;
	ce.InitURL("/home/lfr/workspace3/crawler/Debug/initurl");
	ce.StartEntity();

	//sleep(3600);

		int a;
		scanf("%d",&a);

	ce.StopEntity();
	tp.stop();
	Mem_Pool::getInstance()->freeMemPool();
	DbManager_Singleton::close();
	URL_Queue_Singleton::close();

	delete reactor;

/*	int a;
	scanf("%d",&a);*/

	return 0;
}
