/*
 * DocQueue.h
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#ifndef DOCQUEUE_H_
#define DOCQUEUE_H_

#include <queue>

using namespace std;
class Document;
class DocQueue : public MessageComponent{
public:
	DocQueue();
	virtual ~DocQueue();
private:
	ACE_Thread_Mutex mutex_;
	queue<Document*> _dq;
	Document *pop_queue();

	void insert_queue(Document *s);
	Document* pop_queue();
	bool isEmpty();

};

#endif /* DOCQUEUE_H_ */
