/*
 * Fetcher.cpp
 *
 *  Created on: 2014年12月17日
 *      Author: lfr
 */

#include <stdio.h>
#include "Fetcher.h"
#include "Document.h"
#include "MemPool.h"
#include <string.h>
#include "URLQueue.h"

Net_Svc_Handler::Net_Svc_Handler():size(0),issize(true)
{

}
Net_Svc_Handler::~Net_Svc_Handler()
{

}

bool Net_Svc_Handler::isNeed()
{
	char *p = strstr(data,"Content-Type");
	if(!p)
	{
		p = strstr(data,"Content-type");
	}
	if(!p)
	{
		return true;
	}
	p+=14;
	if(strncmp(p,"text/html",9) != 0)
	{
		printf("the p is %s\n",p);
		return false;
	}
	return true;
}

int Net_Svc_Handler::handle_input(ACE_HANDLE)
{
	int size1 = peer().recv(tempdata,tmpdata-1);
	if(size1 <= 0)
	{
		//peer().close();
		handle_rawdata();
		MessageBus::getInstance()->call(1,"StartGetURL",NULL,NULL,NULL,NULL,NULL,NULL,NULL);
		printf("end....\n");
		return -1;
	}
	tempdata[size1] = '\0';
	memcpy(data+size,tempdata,size1);
	size += size1;
	if(size >= 1024 && issize==true)
	{
		issize = false;
		if(isNeed() == false)
		{
			MessageBus::getInstance()->call(1,"StartGetURL",NULL,NULL,NULL,NULL,NULL,NULL,NULL);
			return -1;
		}
	}
	return 0;
}

void Net_Svc_Handler::handle_rawdata()
{
	if(strncmp(data,"HTTP/1.1 200",12) == 0)
	{
		char *p = strstr(data,"<!DOCTYPE"); //html text data
		if(!p)
		{
			p = strstr(data,"<!doctype");
		}

		if(!p)
		{
			return;
		}

		Document *pp = Mem_Pool::getInstance()->getObject();
		char tempdata1[2*1024];  //应答头
		memset(tempdata1,0,2*1024);
		memcpy(tempdata1,data,p-data);
		printf("the p-data is %d\n",p-data);

	//	char *p1 = strstr(tempdata1,"Content-Length");
		char *p2 = strstr(tempdata1,"Transfer-Encoding: chunked");
		if(p2 == NULL)
		{
			//写入MEM——POOL
			pp->append((unsigned char*)p,size - (p -data));
		}
		else if(p2 != NULL)
		{
			//解析HTML
			char *startp = p;
			while(*startp <  48 || (*startp > 57 && *startp <97) || *startp >102 )
			{
				--startp;
			}
			while(*(--startp) != '\r'); //\r\n

			long s1 = 0;
			char te[16];

			char *tp = startp;  //指向节开始
			char *datap = tp;
			do
			{
				tp = datap+s1;
				char *startnum = tp+2;
				char *p6 = startnum;

				while(*(++p6) != '\r');
				memset(te,0,16);
				memcpy(te,startnum,p6-startnum);
				printf("the p6-startnum is %d\n",p6-startnum);
				s1 = strtol(te,NULL,16);
				datap = p6+2;
				pp->append((unsigned char*)datap,s1);
			}while(s1 != 0);
		}
		pp->SetURl(currenturl);
		MessageBus::getInstance()->call(3,"insert_queue",(void*)pp,NULL,NULL,NULL,NULL,NULL,NULL);
	}
	else if(strncmp(data,"HTTP/1.1 301",12) == 0)
	{
		char *p1 = strstr(data,"Location"); //html text data
		if(p1!= NULL)
		{
			p1+=10;
			char *p2 = p1;
			while(*(++p2) != '\r');
			char tmpurl[1024];
			memcpy(tmpurl,p1,p2-p1);
			printf("the p2-p1 is %d\n",p2-p1);
			tmpurl[p2-p1] = '\0';
			Document *pp = Mem_Pool::getInstance()->getObject();
			pp->SetLinkURl(tmpurl);
			pp->SetURl(currenturl);
			MessageBus::getInstance()->call(3,"insert_queue",(void*)pp,NULL,NULL,NULL,NULL,NULL,NULL);

			//URL_Queue_Singleton::instance()->insert_queue(tmpurl,2); //2优先级
		}
	}
}

Fetcher::Fetcher() {
	// TODO Auto-generated constructor stub
}

Fetcher::~Fetcher() {
	// TODO Auto-generated destructor stub
}

void Fetcher::call(string/*插件方法名*/ a,void * v,void *d,void *e ,void* f,void *g,void *h,void **o/*函数返回值*/)
{
	if(a == "MakeRequest")
	{
		MakeRequest((char*)v,(char*)d,(char*)e,(char*)f);
	}
}

void Fetcher::MakeRequest(string url,string ip,string host,string path)
{
	char request[1024];
	memset(request,0,1024);
	const char data[] = "GET %s HTTP/1.1\r\nHOST: %s\r\n"
				"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:26.0) Gecko/20100101 Firefox/26.0\r\n"
				"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
				"Accept-Language: en-US,en;q=0.5\r\n"
				"Connection: close\r\n"
				"\r\n";

//	const char data[] = "GET %s HTTP/1.1\r\nHOST: %s\r\n"
//				"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:26.0) Gecko/20100101 Firefox/26.0\r\n"
//				"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
//				"Accept-Language: en-US,en;q=0.5\r\n"
//				"\r\n";

	sprintf(request,data,path.c_str(),host.c_str());

	ACE_INET_Addr addr(80,ip.c_str(),AF_INET);
	handler= new Net_Svc_Handler();
	//Connects to remote machine
	if(connector.connect(handler,addr) == -1)
	{
		ACE_DEBUG((LM_ERROR,"Connect Error\n"));
//		delete handler;
		MessageBus::getInstance()->call(1,"StartGetURL",NULL,NULL,NULL,NULL,NULL,NULL,NULL);
		return;
		//exit(1);

	}
	handler->SetUrl(url);
	int ret = handler->peer().send(request,strlen(request));
	if(ret != strlen(request))
	{
		MessageBus::getInstance()->call(1,"StartGetURL",NULL,NULL,NULL,NULL,NULL,NULL,NULL);
	}
}
