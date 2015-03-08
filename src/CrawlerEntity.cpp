/*
 * CrawlerEntity.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#include "CrawlerEntity.h"
#include "MessageBus.h"
#include <fstream>
#include <string>
#include <istream>
#include "DBManager.h"
#include "FileWriter.h"

using namespace std;

CrawlerEntity::CrawlerEntity() {
	// TODO Auto-generated constructor stub
	ct0 = new Crawler_Thread(1);
	ct1 = new Crawler_Thread(6);
	ct2 = new Crawler_Thread(7);
	ct3 = new Crawler_Thread(8);
	ct4 = new Crawler_Thread(9);
	ct5 = new Crawler_Thread(10);

	fe = new Fetcher;
	dq = new DocQueue("htmlparser");
	forwrite = new DocQueue("File Writer");
	hp = new HtmlParser;
	fw = new FileWriter;
	ut = new URLTest(0.1,1000000000);

	//1- 抓取线程0，6-抓取线程1，7-抓取线程2，8-抓取线程3,9-抓取线程4,10-抓取线程5
	//2-抓取器，3-文档队列，4-链接提取器线程，5-布隆过滤器构件
	//11-文档队列写入，12-文档写入线程


	MessageBus::getInstance()->add(1,dynamic_cast<MessageComponent*>(ct0));
	MessageBus::getInstance()->add(2,dynamic_cast<MessageComponent*>(fe));
	MessageBus::getInstance()->add(3,dynamic_cast<MessageComponent*>(dq));
	MessageBus::getInstance()->add(4,dynamic_cast<MessageComponent*>(hp));
	MessageBus::getInstance()->add(5,dynamic_cast<MessageComponent*>(ut));
	MessageBus::getInstance()->add(6,dynamic_cast<MessageComponent*>(ct1));
	MessageBus::getInstance()->add(7,dynamic_cast<MessageComponent*>(ct2));
	MessageBus::getInstance()->add(8,dynamic_cast<MessageComponent*>(ct3));
	MessageBus::getInstance()->add(9,dynamic_cast<MessageComponent*>(ct4));
	MessageBus::getInstance()->add(10,dynamic_cast<MessageComponent*>(ct5));
	MessageBus::getInstance()->add(11,dynamic_cast<MessageComponent*>(forwrite));
	MessageBus::getInstance()->add(12,dynamic_cast<MessageComponent*>(fw));
}

CrawlerEntity::~CrawlerEntity() {
	// TODO Auto-generated destructor stub

	delete ct0;
	delete ct1;
	delete ct2;
	delete ct3;
	delete ct4;
	delete ct5;

	delete fe;
	delete hp;
	delete fw;
	delete dq;
	delete forwrite;
	delete ut;
}


void CrawlerEntity::StartEntity()
{
	ct0->start();
	ct1->start();
	ct2->start();
	ct3->start();
	ct4->start();
//	ct5->start();
	hp->start();
	fw->start();
}
void CrawlerEntity::StopEntity()
{
	ct0->stop();
    ct1->stop();
	ct2->stop();
    ct3->stop();
    ct4->stop();
	hp->stop();
	fw->stop();

}

void CrawlerEntity::InitURL(string filename)
{
	//是否已经抓取
//	ifstream dbifs;
//	dbifs.open()

	ifstream ifs(filename.c_str());
	string s;
	while(getline(ifs,s))
	{
		URL_Queue_Singleton::instance()->insert_queue(s,1);
	}
}
