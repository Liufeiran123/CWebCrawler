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

using namespace std;

class My_Svc_Handler;

typedef ACE_Connector<My_Svc_Handler,ACE_SOCK_CONNECTOR> MyConnector;


//Create a service handler similar to as seen in example 1. Except this
//time include the handle_input() method which will be called back
//automatically by the reactor when new data arrives on the newly
//established connection
class My_Svc_Handler: public ACE_Svc_Handler <ACE_SOCK_STREAM,ACE_NULL_SYNCH>, MessageComponent
{
public:
	My_Svc_Handler()
	{

	}
/*	int open(void *)
	{
		ACE_DEBUG((LM_INFO,"open called\n"));
		return 0;
	}
*/
	void handle_rawdata();

	int handle_input(ACE_HANDLE)
	{
		int size1 = peer().recv(tempdata,1024);
		if(size1 <= 0)
		{
			peer().close();
			handle_rawdata();
			MessageBus::getInstance()->call(1,"StartGetURL",NULL,NULL,NULL,NULL,NULL,NULL);
			return -1;
		}
		tempdata[size1] = '\0';
		memcpy(data+size,tempdata,size1);
		size += size1;
		return 0;
	}

	int handle_close()
private:
	char tempdata[1024];
	char data[1024*1024];
	int size;
};

class Fetcher : public MessageComponent {
public:
	Fetcher();
	virtual ~Fetcher();
public:

private:
	MyConnector connector;
	My_Svc_Handler * handler;
	string preip;

public:
	void MakeRequest(string ip,string host,string path);
	virtual void call(string/*插件方法名*/ a,void * v,void *d,void *e ,void* f,void *g,void* h/*函数返回值*/);
};

#endif /* FETCHER_H_ */
