/*
 * Document.h
 *
 *  Created on: 2014年12月28日
 *      Author: lfr
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>

using namespace std;
const int max_doc = 1024*1024;

class Document {
public:
	Document();
	virtual ~Document();
private:
	unsigned char buffer[max_doc];
	int size;
	string url;
public:
	void append(unsigned char* a,int asize);
	int getDoc(unsigned char*a);
	int getSize(){return size;}
	void SetTitle(string t);
	string GetTitle();
	void SetURl(string b);
	string &GetURL();
};

#endif /* DOCUMENT_H_ */
