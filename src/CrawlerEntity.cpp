/*
 * CrawlerEntity.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#include "CrawlerEntity.h"
#include "MessageBus.h"

CrawlerEntity::CrawlerEntity() {
	// TODO Auto-generated constructor stub
	Crawler_Thread *ct = new Crawler_Thread;
	Fetcher *fe = new Fetcher;
	DocQueue *dq = new DocQueue;
	HtmlParser* hp = new HtmlParser;


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
	ct->start();
	hp->start();

}
