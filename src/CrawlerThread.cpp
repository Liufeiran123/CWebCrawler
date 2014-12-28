/*
 * CrawlerThread.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "CrawlerThread.h"

Crawler_Thread::Crawler_Thread():value(0) {
	// TODO Auto-generated constructor stub

}

Crawler_Thread::~Crawler_Thread() {
	// TODO Auto-generated destructor stub
}

void Crawler_Thread::StartGetURL()
{
	mutex.acqure();
	value =1 ;
	cond.signal();
	mutex.release();
}
