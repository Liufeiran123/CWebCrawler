/*
 * Document.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#include "Document.h"
#include <string.h>

Document::Document():size(0) {
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

void Document::SetTitle(string t)
{


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
	url = b;
}

string &Document::GetURL()
{
	return url;
}
