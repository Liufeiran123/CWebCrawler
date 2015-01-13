/*
 * URLQueue.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "URLQueue.h"
#include "DBManager.h"

URL_Queue::URL_Queue() {
	// TODO Auto-generated constructor stub

}

URL_Queue::~URL_Queue() {
	// TODO Auto-generated destructor stub
}

void URL_Queue::insert_queue(string s,int priority)
{
	struct timeval val;
	urlstring us(s,priority);
	mutex_.acquire();
	m_q.push(us);
	DbManager_Singleton::instance()->writeDB(1,s,&val);
	mutex_.release();
}
string URL_Queue::pop_queue()
{
	urlstring a("",0);
	mutex_.acquire();
	if(isEmpty() == false)
	{
		a = m_q.top();
		m_q.pop();
	}
	DbManager_Singleton::instance()->deleteDB(1,a.GetURL());
	mutex_.release();
	return a.GetURL();
}

bool URL_Queue::isEmpty()
{
	mutex_.acquire();
	bool a = m_q.empty();
	mutex_.release();
	return a;
}

bool URL_Queue::isExist(string s)
{
	struct timeval tv;
	mutex_.acquire();
	bool ret = DbManager_Singleton::instance()->readDB(1,s,&tv);
	mutex_.release();
	return ret;
}
