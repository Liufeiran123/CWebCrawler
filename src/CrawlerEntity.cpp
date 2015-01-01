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

using namespace std;

CrawlerEntity::CrawlerEntity() {
	// TODO Auto-generated constructor stub
	ct = new Crawler_Thread;
	fe = new Fetcher;
	dq = new DocQueue;
	hp = new HtmlParser;


	MessageBus::getInstance()->add(1,dynamic_cast<MessageComponent*>(ct));
	MessageBus::getInstance()->add(2,dynamic_cast<MessageComponent*>(fe));
	MessageBus::getInstance()->add(3,dynamic_cast<MessageComponent*>(dq));
	MessageBus::getInstance()->add(4,dynamic_cast<MessageComponent*>(hp));

}

CrawlerEntity::~CrawlerEntity() {
	// TODO Auto-generated destructor stub
}


void CrawlerEntity::StartEntity()
{
	printf("kkk\n");
	ct->start();
	printf("kkk1\n");
	hp->start();

}

void CrawlerEntity::InitURL(string filename)
{
	ifstream ifs(filename.c_str());
	string s;
	while(getline(ifs,s))
	{
		URL_Queue_Singleton::instance()->insert_queue(s.c_str());
	}
}
