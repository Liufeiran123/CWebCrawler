/*
 * URLQueue.h
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#ifndef URLQUEUE_H_
#define URLQUEUE_H_

#include <queue>
#include <string>
#include <vector>
#include "urlstring.h"
#include "ace/Recursive_Thread_Mutex.h"
#include "ace/Singleton.h"

using namespace std;

class URL_Queue {
public:
	URL_Queue();
	virtual ~URL_Queue();
private:
	priority_queue<urlstring, vector<urlstring>, cmp> m_q;
	ACE_Recursive_Thread_Mutex mutex_;
public:
	void insert_queue(string s,int priority);
	string pop_queue();
	bool isEmpty();
	bool isExist(string s);
};


typedef ACE_Unmanaged_Singleton<URL_Queue,ACE_Null_Mutex> URL_Queue_Singleton;

#endif /* URLQUEUE_H_ */
