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

using namespace std;

class URL_Queue {
public:
	URL_Queue();
	virtual ~URL_Queue();
private:
	queue<string> m_q;
	ACE_Thread_Mutex mutex_;
public:
	void insert_queue(string s);
	string pop_queue();
	int isEmpty();
};


typedef ACE_Unmanaged_Singleton<URL_Queue,ACE_Null_Mutex> URL_Queue_Singleton;

/*#include "iostream"
#include "queue"
using namespace std;
int main()
{
queue<int> q;
q.push(3);
q.push(12);
while(!q.empty()){
cout<<q.front()<<endl;
q.pop();
}
return 1;
}
*/
#endif /* URLQUEUE_H_ */
