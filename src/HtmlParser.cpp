/*
 * HtmlParser.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#include "HtmlParser.h"

HtmlParser::HtmlParser() {
	// TODO Auto-generated constructor stub

}

HtmlParser::~HtmlParser() {
	// TODO Auto-generated destructor stub
}


void HtmlParser::call(string/*插件方法名*/,void *,void*,void *,void*,void *,unsigned long &/*函数返回值*/)
{

}

int HtmlParser::start()
{
	printf("hs\n");
	if(this->activate(THR_NEW_LWP | THR_JOINABLE, 1) == -1)
	{
// 		ACE_ERROR_RETURN ((LM_ERROR,
// 							ACE_TEXT ("%p.\n"),
// 							ACE_TEXT ("unable to activate thread pool")),
// 							-1);                            //by fzq
	//	LOGGER->AddLogger(LT_DEBUG_ERROR,ACE_TEXT("unable to activate thread pool")) ;
		return -1 ;
	}
	printf("hs123\n");
	return 0;
}

int HtmlParser::stop()
{


	return 0;
}
int HtmlParser::svc(void)
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
