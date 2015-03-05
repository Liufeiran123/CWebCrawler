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
	dq = new DocQueue;
	hp = new HtmlParser;
	ut = new URLTest(0.1,1000000000);


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

}

CrawlerEntity::~CrawlerEntity() {
	// TODO Auto-generated destructor stub
}


void CrawlerEntity::StartEntity()
{
	ct0->start();
	ct1->start();
	ct2->start();
	ct3->start();
	ct4->start();
	ct5->start();
	hp->start();
}

void CrawlerEntity::InitURL(string filename)
{
	ifstream ifs(filename.c_str());
	string s;
	while(getline(ifs,s))
	{
		URL_Queue_Singleton::instance()->insert_queue(s,1);
	}
}
