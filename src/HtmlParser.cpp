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


void HtmlParser::call(string/*插件方法名*/,void *,void*,void *,void*,void *,void *,void **/*函数返回值*/)
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

string &HtmlParser::modifyurl(string &a)
{
	int b = string::npos;
	if((b =a.find('#',0)) == string::npos)
	{
		return a;
	}
	else
	{
		a = a.substr(0,b);
		return a;
	}

}
int HtmlParser::svc(void)
{
	Document *pp;
	char text[1024*1024];

	while(1)
	{
		bool retval;
		MessageBus::getInstance()->call(3,"isEmpty",NULL,NULL,NULL,NULL,NULL,&retval,NULL);
		if(!retval)
		{
			memset(text,0,1024*1024);
			MessageBus::getInstance()->call(3,"pop_queue",NULL,NULL,NULL,NULL,NULL,NULL,(void**)&pp);
			int s = pp->getDoc((unsigned char*)text);
			text[s]='\0';
			data_buffer = text;
			//写入文件
			string ff= pp->GetTitle();
			ff.append(".html");
			string dir = "/home/lfr/crawlerData/";
			dir+= ff;
			ofstream fs(dir.c_str());
			fs<<data_buffer;
			MessageBus::getInstance()->call(5,"addToBloomSet",(void*)pp->GetURL().c_str(),NULL,NULL,NULL,NULL,NULL,NULL);

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
							   string abc = modifyurl(ab.second);
							   bool tmp;
							   MessageBus::getInstance()->call(5,"isInBloomSet",(void*)abc.c_str(),NULL,NULL,NULL,NULL,(void*)&tmp,NULL);
							   if(tmp == false)
							   {
								   URL_Queue_Singleton::instance()->insert_queue(abc,1);  //1优先级
							   }
						   }
					}	 // cout<<it->text();
				}
			} catch (exception &e) {
				cerr << "Exception " << e.what() << " caught" << endl;
				//exit(1);
			} catch (...) {
				cerr << "Unknow exception caught " << endl;
			}
			Mem_Pool::getInstance()->freeObject(pp);
		}
		else
		{
			sleep(3);
		}
	}
		return 0;
}
