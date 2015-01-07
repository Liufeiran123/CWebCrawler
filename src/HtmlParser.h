/*
 * HtmlParser.h
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include "ace/Task_T.h"
#include "ParserDom.h"
#include "utils.h"
#include "Document.h"
#include "MemPool.h"
#include "MessageBus.h"
#include "URLQueue.h"
#include "URLFilter.h"

using namespace std;
using namespace htmlcxx;

class HtmlParser :  public ACE_Task<ACE_NULL_SYNCH>, public MessageComponent {
public:
	HtmlParser();
	virtual ~HtmlParser();

private:
	  string data_buffer;  //html文件内容

	  HTML::ParserDom parser;
	  tree<HTML::Node> tr;
	  string baseTag;
	  URLFilter *uf;

public:
		int start();
		int stop();
		virtual void call(string/*插件方法名*/,void *,void*,void *,void*,void *,void *,void **/*函数返回值*/);
		int svc(void);
		string &modifyurl(string &a);
		void writeFile(Document*);
		void ParseText();
		void insertQueue(string bac);
		void getBaseTag(Document* p);
};

#endif /* HTMLPARSER_H_ */
