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

void URL_Queue::insert_queue(string s)
{
	mutex_.acquire();
	m_q.push(s);
	mutex_.release();
}
string URL_Queue::pop_queue()
{
	mutex_.acquire();
	string a = m_q.front();
	m_q.pop();
	mutex_.release();
	return a;
}

int URL_Queue::isEmpty()
{
	mutex_.acquire();
	int a = m_q.empty();
	mutex_.release();
	return a;
}
