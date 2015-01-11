/*
 * Fetcher.h
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#ifndef FETCHER_H_
#define FETCHER_H_

#include "ace/Synch.h"
#include "ace/Log_Msg.h"
#include "ace/SOCK_Connector.h"
#include "ace/Connector.h"

#include "MessageComponent.h"
#include "commondefine.h"

#include <string>

#include "MessageBus.h"

using namespace std;

class Net_Svc_Handler;

typedef ACE_Connector<Net_Svc_Handler,ACE_SOCK_CONNECTOR> NetConnector;


class Net_Svc_Handler: public ACE_Svc_Handler <ACE_SOCK_STREAM,ACE_NULL_SYNCH>
{
public:
	Net_Svc_Handler();
	~Net_Svc_Handler();
public:

	void handle_rawdata();

	int handle_input(ACE_HANDLE);

	bool isNeed();
private:
	char tempdata[tmpdata];
	char data[max_doc];
	int size;
	string currenturl;
	bool issize;
	int crawlerid;

public:
	void SetUrl(string a)
	{
		currenturl =a;
	}
	void SetId(int a)
	{
		crawlerid = a;
	}

};

class Fetcher : public MessageComponent {
public:
	Fetcher();
	virtual ~Fetcher();
public:

private:
	NetConnector connector;
//	ACE_Thread_Mutex _mutex;
public:
	void MakeRequest(string url,string ip,string host,string path,int id);
	virtual void call(string/*插件方法名*/ a,void * v,void *d,void *e ,void* f,void *g,void *h,void **i/*函数返回值*/);
};

#endif /* FETCHER_H_ */
