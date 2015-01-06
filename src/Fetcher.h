/*
 * Fetcher.h
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#ifndef FETCHER_H_
#define FETCHER_H_

#include "ace/Log_Msg.h"
#include "ace/SOCK_Connector.h"
#include "ace/Connector.h"

#include "MessageComponent.h"

#include <string>

#include "MessageBus.h"

using namespace std;

class Net_Svc_Handler;

typedef ACE_Connector<Net_Svc_Handler,ACE_SOCK_CONNECTOR> NetConnector;


//Create a service handler similar to as seen in example 1. Except this
//time include the handle_input() method which will be called back
//automatically by the reactor when new data arrives on the newly
//established connection
class Net_Svc_Handler: public ACE_Svc_Handler <ACE_SOCK_STREAM,ACE_NULL_SYNCH>
{
public:
	Net_Svc_Handler():size(0)
	{

	}
/*	int open(void *)
	{
		ACE_DEBUG((LM_INFO,"open called\n"));
		return 0;
	}
*/
	void handle_rawdata();

	int handle_input(ACE_HANDLE);
private:
	char tempdata[1024];
	char data[1024*1024];
	int size;
	string currenturl;

public:
	void SetUrl(string a)
	{
		currenturl =a;
	}

};

class Fetcher : public MessageComponent {
public:
	Fetcher();
	virtual ~Fetcher();
public:

private:
	NetConnector connector;
	Net_Svc_Handler * handler;
	string preip;

public:
	void MakeRequest(string url,string ip,string host,string path);
	virtual void call(string/*插件方法名*/ a,void * v,void *d,void *e ,void* f,void *g,void *h,void **i/*函数返回值*/);
};

#endif /* FETCHER_H_ */
