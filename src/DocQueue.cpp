/*
 * DocQueue.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#include "DocQueue.h"

DocQueue::DocQueue() {
	// TODO Auto-generated constructor stub

}

DocQueue::~DocQueue() {
	// TODO Auto-generated destructor stub
}

void DocQueue::insert_queue(Document *s)
{
	mutex_.acquire();
	_dq.push(s);
	mutex_.release();
}
Document* DocQueue::pop_queue()
{
	Document* a = NULL;
	mutex_.acquire();
	if(isEmpty() == false)
	{
		a = _dq.front();
		_dq.pop();
	}
	mutex_.release();
	return a;
}

bool DocQueue::isEmpty()
{
	mutex_.acquire();
	bool a = _dq.empty();
	mutex_.release();
	return a;
}
