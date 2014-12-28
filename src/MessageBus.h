/*
 * MessageBus.h
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#ifndef MESSAGEBUS_H_
#define MESSAGEBUS_H_

#include <map>
#include <string>

using namespace std;

class MessageComponent;

class MessageBus {
protected:
	MessageBus();
	virtual ~MessageBus();
private:
	static MessageBus *mb;
public:
	static MessageBus *getInstance();
public:
	map<int,MessageComponent*> m_test;
	void add(int id,MessageComponent* a);
    void call(int id,string name,void *,void*,void *,void*,void *,void*/*函数返回值*/);
};

#endif /* MESSAGEBUS_H_ */
