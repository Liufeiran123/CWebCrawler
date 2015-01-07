/*
 * Document.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#include "Document.h"
#include <string.h>

Document::Document():size(0){
	// TODO Auto-generated constructor stub

}

Document::~Document() {
	// TODO Auto-generated destructor stub
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
			char tmp[128];
			memset(tmp,0,128);
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
		return string();
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
	string tmp(url);

	int i = strlen(url);
//	  assert (file[0] == '/');
	while (url[i] != '/') {
		i--;
	}

	return tmp.substr(0,i);
}
