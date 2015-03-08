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
#include "FileWriter.h"

class CrawlerEntity{
public:
	CrawlerEntity();
	virtual ~CrawlerEntity();
private:
	Crawler_Thread *ct0;
	Crawler_Thread *ct1;
	Crawler_Thread *ct2;
	Crawler_Thread *ct3;
	Crawler_Thread *ct4;
	Crawler_Thread *ct5;
	Fetcher *fe;
	DocQueue *dq;
	DocQueue *forwrite;
	HtmlParser* hp;
	FileWriter *fw;
	URLTest *ut;
public:
	void StartEntity();
	void StopEntity();
	void InitURL(string filename);

};

#endif /* CRAWLERENTITY_H_ */
