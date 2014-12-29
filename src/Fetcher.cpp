/*
 * Fetcher.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#include <stdio.h>
#include "Fetcher.h"

void My_Svc_Handler::handle_rawdata()
{
	Document *pp = Mem_Pool<Document>::getInstance()->getObject();
	if(strncmp(data,"HTTP/1.1 200 OK",15) == 0)
	{
		char *p = strstr(data,"<!DOCTYPE"); //html text data

		char tempdata1[2*1024];  //应答头
		memset(tempdata1,0,2*1024)
		memcpy(tempdata1,data,p-data);

		char *p1 = strstr(tempdata1,"Content-Length");
		char *p2 = strstr(tempdata1,"Transfer-Encoding: chunked");
		if(p1 != NULL)
		{
			//写入MEM——POOL
			pp->append((unsigned char*)p,size - p -data);
		}
		else if(p2 != NULL)
		{
			//解析HTML
			char *startp = p;
			startp-=2;
			while(*(--startp) != '\n'); //\r\n
			++startp;
			long s1 = -1;
			char te[16];

			char *tp = startp;  //指向数字开始
			do
			{
				tp += s1+1;
				char *p6 = tp;

				while(*(++p6) != '\r');
				memset(te,0,16);
				memcpy(te,tp,p6-tp);
				s1 = strtol(te,NULL,16);
				pp->append((unsigned char*)(p6+2),s1);
			}while(s1 != 0);
		}
	}
	if(pp->getSize()!=0)
	{
		MessageBus::getInstance()->call(3,"insert_queue",(void*)pp,NULL,NULL,NULL,NULL,NULL);
		return ;
	}
	Mem_Pool<Document>::getInstance()->freeObject(pp);
}

Fetcher::Fetcher() {
	// TODO Auto-generated constructor stub
	handler= new My_Svc_Handler();
	MessageBus::getInstance()->add(5,dynamic_cast<MessageComponent*>(handler));
}

Fetcher::~Fetcher() {
	// TODO Auto-generated destructor stub
}

virtual void Fetcher::call(string/*插件方法名*/ a,void * v,void *d,void *e ,void* f,void *g,void* h/*函数返回值*/)
{
	if(a == "MakeRequest")
	{
		MakeRequest(*v,*d,*e);
	}
}

void Fetcher::MakeRequest(string ip,string host,string path)
{
	char request[1024];
	memset(request,0,1024);
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

	int ret = handler->peer().send(request,strlen(request));
	if(ret != strlen(request))
	{
		MessageBus::getInstance()->call(1,"StartGetURL",NULL,NULL,NULL,NULL,NULL,NULL);
	}
}
