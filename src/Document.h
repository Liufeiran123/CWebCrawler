/*
 * Document.h
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
#include "commondefine.h"

using namespace std;


class Document {
public:
	Document();
	virtual ~Document();
private:
	unsigned char buffer[max_doc];   //文档数据
	char url[1024];
	char linkurl[1024];  //redirect
	int size;
public:
	void append(unsigned char* a,int asize);
	int getDoc(unsigned char*a);
	int getSize();
	string GetTitle();

	string GetCharEncoding();
	void SetURl(string b);
	string GetURL();

	void SetLinkURl(string b);
	string GetLinkURL();

	void Reset();
	string getBase();
	string getProtocol();
};

#endif /* DOCUMENT_H_ */
