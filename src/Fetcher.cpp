/*
 * Fetcher.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#include <stdio.h>
#include "Fetcher.h"

Fetcher::Fetcher() {
	// TODO Auto-generated constructor stub
	handler= new My_Svc_Handler();
}

Fetcher::~Fetcher() {
	// TODO Auto-generated destructor stub
}

void Fetcher::MakeRequest(string ip,string host,string path)
{
	char request[1024];
	const char data[] = "GET %s HTTP/1.1\r\nHOST: %s\r\n"
				"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:26.0) Gecko/20100101 Firefox/26.0\r\n"
				"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
				"Accept-Language: en-US,en;q=0.5\r\n"
				"Connection: keep-alive\r\n"
				"\r\n";

	sprintf(request,data,path,host);

	ACE_INET_Addr addr(80,ip,AF_INET);

	//Create the connector
	MyConnector connector;
	//Connects to remote machine
	if(connector.connect(handler,addr) == -1)
	{
		ACE_DEBUG((LM_ERROR,"Connect Error\n"));
		//exit(1);

	}

}
