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
#include "URLTest.h"

class CrawlerEntity{
public:
	CrawlerEntity();
	virtual ~CrawlerEntity();
private:
	Crawler_Thread *ct;
	Crawler_Thread *ct1;
	Crawler_Thread *ct2;
	Crawler_Thread *ct3;
	Fetcher *fe;
	DocQueue *dq;
	HtmlParser* hp;
	URLTest *ut;
public:
	void StartEntity();
	void InitURL(string filename);

};

#endif /* CRAWLERENTITY_H_ */
