/*
 * URLQueue.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "URLQueue.h"

URL_Queue::URL_Queue() {
	// TODO Auto-generated constructor stub

}

URL_Queue::~URL_Queue() {
	// TODO Auto-generated destructor stub
}

void URL_Queue::insert_queue(string s,int priority)
{
	urlstring us(s,priority);
	mutex_.acquire();
	m_q.push(us);
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
