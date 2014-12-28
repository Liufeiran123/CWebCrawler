/*
 * Document.cpp
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#include "Document.h"

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
}
int Document::getDoc(unsigned char*a)
{
	memcpy(a,buffer,size);
	return size;
}
