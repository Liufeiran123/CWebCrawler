/*
 * HtmlParser.h
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include "ace/Task_T.h"
#include <string>
#include "ParserDom.h"
#include "utils.h"
#include "Document.h"
#include "MemPool.h"
#include <exception>
#include <iostream>
#include <fstream>
#include "MessageBus.h"
#include "URLQueue.h"

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

public:
		int start();
		int stop();
		virtual void call(string/*插件方法名*/,void *,void*,void *,void*,void *,unsigned long &/*函数返回值*/);
		int open(void*)
		{
			ACE_DEBUG((LM_DEBUG,"(%t) Active Object opened \n"));
			//Activate the object with a thread in it.
			activate();
			return 0;
		}
		int close(u_long)
		{
			ACE_DEBUG((LM_DEBUG, "(%t) Active Object being closed down \n"));
			return 0;
		}
		int svc(void)
		{
			Document *pp;
			char text[1024*1024];

			while(1)
			{
				unsigned long addr;
				MessageBus::getInstance()->call(3,"isEmpty",NULL,NULL,NULL,NULL,NULL,addr);
				bool retval = *(bool*)addr;
				if(!retval)
				{
					memset(text,0,1024*1024);
					MessageBus::getInstance()->call(3,"pop_queue",NULL,NULL,NULL,NULL,NULL,addr);
					pp = (Document*)addr;
					int s = pp->getDoc((unsigned char*)text);
					Mem_Pool::getInstance()->freeObject(pp);
					text[s]='\0';
					data_buffer = text;
					//写入文件
					string ff= pp->GetTitle();
					ff.append(".html");
					string dir = "/home/lfr/workspace3/crawler/Debug/htmldata/";
					dir+= ff;
					ofstream fs(dir.c_str());
					fs<<data_buffer;

					try
					{
						parser.parse(data_buffer);
						tr = parser.getTree();
							//cout << tr << endl;
						tree<HTML::Node>::iterator it = tr.begin();
						tree<HTML::Node>::iterator end = tr.end();

						for(; it != end; ++it)
						{
								//  printf("the tagname is %s\n",it->tagName().c_str());
							if(it->isTag() && (it->tagName() == string("a") || it->tagName() == string("A")))
							{
								   it->parseAttributes();
								   pair<bool,string> ab = it->attribute("href");
								   if(ab.first == true)
								   {
									   URL_Queue_Singleton::instance()->insert_queue(ab.second);
								   }
							}	 // cout<<it->text();
						}
					} catch (exception &e) {
						cerr << "Exception " << e.what() << " caught" << endl;
						//exit(1);
					} catch (...) {
						cerr << "Unknow exception caught " << endl;
					}
				}
				else
				{
					sleep(3);
				}
			}
				return 0;
		}
};

#endif /* HTMLPARSER_H_ */
