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
	int handle_input(ACE_HANDLE)
	{
	//After using the peer() method of ACE_Svc_Handler to obtain a
	//reference to the underlying stream of the service handler class
	//we call recv_n() on it to read the data which has been received.
	//This data is stored in the data array and then printed out
		ACE_OS::printf("lfrdreamman");
	//keep yourself registered with the reactor
		return 0;
	}

	int handle_close()
private:
	char* data;
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
};

#endif /* FETCHER_H_ */
