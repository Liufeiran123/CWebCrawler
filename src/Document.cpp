/*
 * Document.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */
#include <stdio.h>
#include <iostream>
#include <boost/xpressive/xpressive_dynamic.hpp>
#include "Document.h"
#include <string.h>
#include "Url.h"

using namespace boost::xpressive;
using namespace std;

Document::Document():size(0){
	// TODO Auto-generated constructor stub

}

Document::~Document() {
	// TODO Auto-generated destructor stub
}

string Document::GetCharEncoding()
{
/*	if(size != 0)
	{
		char *p = strstr((char*)buffer,"meta");
		if(p == NULL)
		{
			return "gb2312";
		}

		p = strstr(p,"charset");

		if(p != NULL)
		{
			while(*(++p) != '=');
			while(*(++p) == ' ');
			char *t = p;
			while(*(++t) != '\"');
			char tmp[32];
			memset(tmp,0,32);
			memcpy(tmp,p,t-p);
			return string(tmp);
		}
		else
		{
			return "gb2312";    //
		}
	}*/
	cregex reg = cregex::compile("(<meta)(.{0,60})(charset.{0,10}=\\s*\"*\\s*)(.{0,30}?)(\\s*\"\\s*/*>)");
//	char *buffer = "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\" />";
	cmatch what;
	if(regex_search((char*)buffer,what,reg) == true)
	{
		/*for(int i =0;i<6;++i)
		{
			cout<<what[i]<<"\n";
		}*/
		cout<<what[4]<<"\n";
//		cout<<buffer<<"\n";
		return what[4];
	}
	{
		EncodingDetector *ed = new EncodingDetector();
		ed->setData((char*)buffer,size);
		return ed->getEncoding();
	}
}

void Document::append(unsigned char* a,int b)
{
	if(size+b > max_doc)
	{
		return;
	}
	memcpy(buffer+size,a,b);
	size += b;
}
int Document::getDoc(unsigned char*a)
{
	memcpy(a,buffer,size);
	return size;
}
int Document::getSize()
{
	return size;
}
string Document::GetTitle()
{
	if(size != 0)
	{
		char *p = strstr((char*)buffer,"<title>");
		if(p != NULL)
		{
			char *t = p;
			while(*(++t) != '<');
			char tmp[1024];
			memset(tmp,0,1024);
			memcpy(tmp,p+7,(t-p)-7);
			return string(tmp);
		}
		else
		{
			return string("unkowntitle");
		}
	}
	else
	{
		return string("");
	}
}


void Document::SetURl(string b)
{
	memcpy(url,b.c_str(),b.size());
	url[b.size()] = '\0';
}

string Document::GetURL()
{
	return url;
}

void Document::SetLinkURl(string b)
{
	memcpy(linkurl,b.c_str(),b.size());
	linkurl[b.size()] = '\0';
}
string Document::GetLinkURL()
{
	return linkurl;
}

void Document::Reset()
{
	size = 0;
	url[0]= '\0';
	linkurl[0]='\0';
}

string Document::getBase()
{
	/*string tmp(url);

	int i = strlen(url);
//	  assert (file[0] == '/');
	while (url[i] != '/') {
		i--;
	}

	return tmp.substr(0,i);*/
	oneurl u;
	u.ParseUrl(url);
	return u.GetHost();
	//m_file = url.GetPath();
}
string Document::getProtocol()
{
	oneurl u;
	u.ParseUrl(url);
	return u.GetScheme();
}

