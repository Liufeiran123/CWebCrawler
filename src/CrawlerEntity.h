/*
 * CrawlerEntity.h
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#ifndef CRAWLERENTITY_H_
#define CRAWLERENTITY_H_

#include "CrawlerThread.h"
#include "DocQueue.h"
#include "Fetcher.h"
#include "HtmlParser.h"

class CrawlerEntity{
public:
	CrawlerEntity();
	virtual ~CrawlerEntity();
private:
	Crawler_Thread *ct;
	Fetcher *fe;
	DocQueue *dq;
	HtmlParser* hp;
public:
	void StartEntity();

};

#endif /* CRAWLERENTITY_H_ */
