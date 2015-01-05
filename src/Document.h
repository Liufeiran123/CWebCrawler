/*
 * Document.h
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
#include "HTTPURL.h"

using namespace std;
const int max_doc = 1024*1024;

class Document {
public:
	Document();
	virtual ~Document();
private:
	unsigned char buffer[max_doc];
	//char url[1024];
	HTTP_URL *url;
	int size;
public:
	void append(unsigned char* a,int asize);
	int getDoc(unsigned char*a);
	int getSize(){return size;}
	string GetTitle();
	void SetURl(HTTP_URL *b);
	string getBase();
	void fini();
};

#endif /* DOCUMENT_H_ */
