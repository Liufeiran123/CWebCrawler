/*
 * MessageBus.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#include "MessageBus.h"
#include "MessageComponent.h"

MessageBus *MessageBus::mb = 0;

MessageBus::MessageBus() {
	// TODO Auto-generated constructor stub

}

MessageBus::~MessageBus() {
	// TODO Auto-generated destructor stub
}

MessageBus* MessageBus::getInstance()
{
	if(mb != 0)
	{
		return mb;
	}
	mb = new MessageBus();
	return mb;
}

void MessageBus::add(int id,MessageComponent* a)
{
	m_test[id] = a;
}
void MessageBus::call(int id,string name,void* d,void* t,void *f,void* g,void *e,void *c,void** p)
{
	map<int,MessageComponent*>::iterator iter = m_test.find(id);
	if(iter != m_test.end())
	{
		iter->second->call(name,d,t,f,g,e,c,p);
	}
}
