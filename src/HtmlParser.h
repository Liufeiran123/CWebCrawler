/*
 * HtmlParser.h
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <ace/Task_T.h>
#include <string>

using namespace std;

class HtmlParser :  public ACE_Task<ACE_NULL_SYNCH>, MessageComponent {
public:
	HtmlParser();
	virtual ~HtmlParser();
public:

	//提取文本
	  void parseText (){}
	//提取URL，添加到URLQueue中
	  void parseURL ();
protected:

	  void SetBuffer()

private:
	  string data_buffer;

	  HTML::ParserDom parser;
	  tree<HTML::Node> tr;

public:
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
					int s = pp->getDoc(text);
					Mem_Pool<Document*>::getInstance()->freeObject(pp);
					text[s]='\0';
					data_buffer = text;
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
							if(it->isTag() && (it->tagName() == string("a") || it->tagName() == string("style")))
							{
								//   printf("skip\n");
								   if(it->isTag() && (it->tagName() == string("script") || it->tagName() == string("style")))
								   {
									//   printf("skip\n");
									   it->parseAttribute();
									   URL_Queue_Singleton::instance()->insert_queue(it->attributes("href"));
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
				return 0;
			}
};

#endif /* HTMLPARSER_H_ */
