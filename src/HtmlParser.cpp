/*
 * HtmlParser.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#include <algorithm>
#include <cctype>
#include "CharsetConverter.h"
#include "HtmlParser.h"
#include "commondefine.h"
#include "ImageURLFIlter.h"

using namespace std;

HtmlParser::HtmlParser():uf(new ImageURLFIlter()),hw("tcp://localhost:61616","FirstQueue"){
	// TODO Auto-generated constructor stub
	hw.InitWriter();
}

HtmlParser::~HtmlParser() {
	// TODO Auto-generated destructor stub
}


void HtmlParser::call(string/*插件方法名*/,void *,void*,void *,void*,void *,void *,void **/*函数返回值*/)
{

}

int HtmlParser::start()
{
	if(this->activate(THR_NEW_LWP | THR_JOINABLE, 1) == -1)
	{
// 		ACE_ERROR_RETURN ((LM_ERROR,
// 							ACE_TEXT ("%p.\n"),
// 							ACE_TEXT ("unable to activate thread pool")),
// 							-1);                            //by fzq
	//	LOGGER->AddLogger(LT_DEBUG_ERROR,ACE_TEXT("unable to activate thread pool")) ;
		return -1 ;
	}
	return 0;
}

int HtmlParser::stop()
{
	return 0;
}

string &HtmlParser::modifyurl(string &a)
{
	int b = string::npos;

	if((b = a.find('?',0)) != string::npos)
	{
		a = a.substr(0,b);
	}

	if((b =a.find('#',0)) != string::npos)
	{
		a = a.substr(0,b);
	}
	if(a[0]=='/')
	{
		a = protocol + "://" + baseTag+a;
	}

	if(a.find("http://") != string::npos || a.find("https://") != string::npos)
	{
		if(a.find('/',8) == string::npos)
		{
			a+="/";
		}
	}
	else
	{
		if(a.find('/',0) == string::npos)
		{
			a+="/";
		}
	}
	return a;
}
//转换为UTF-8
int HtmlParser::CharSetConv(string &charset,string &title,string &content,vector<string> &v)
{
	string encoding;
	string targetencoding = "UTF-8";

	if("gb2312" == charset)
	{
		charset = "GBK";
	}
	std::transform(charset.begin(),charset.end(),encoding.begin(), ::toupper);

	if("UTF-8" != encoding)
	{
		string data1;
		string title1;
		   iconv_t t = CharsetConverter::Open(targetencoding,encoding);
		   title1 = CharsetConverter::Convert(t,title);
		   if(title1.empty())
		   {
			   return -1;
		   }
		   data1 = CharsetConverter::Convert(t,content);
		   if(data1.empty())
		   {
			   return -1;
		   }
		   CharsetConverter::Close(t);
		   v.push_back(title1);
		   v.push_back(data1);
	}
	else
	{
		   v.push_back(title);
		   v.push_back(content);
	}
	return 0;
}
void HtmlParser::writeFile(Document* p)
{
	vector<string> v;
 	string title = p->GetTitle();
	string charset = p->GetCharEncoding();
	if(charset.empty())
	{
		ACE_DEBUG ((LM_INFO, ACE_TEXT ("charset is empty\n")));
		return;
	}
	string dir = "/home/lfr/crawlerData/";
	if(CharSetConv(charset,title,data_buffer,v) == 0)
	{
		v[0].append(".html");
		dir+= v[0];
		ofstream fs(dir.c_str());
		fs<<v[1];
	}
}

void HtmlParser::writeBase(Document *p)
{
	vector<string> v;
	string title = p->GetTitle();
	string url = p->GetURL();
	string charset = p->GetCharEncoding();
	if(CharSetConv(charset,title,data_buffer,v) == 0)
	{
			hw.Writehtml(url,v[0],v[1]);
	}
}
void HtmlParser::getBaseTag(Document* p)
{
	try
	{
		parser.parse(data_buffer);
		tr = parser.getTree();
			//cout << tr << endl;
		tree<HTML::Node>::iterator it1 = tr.begin();
		tree<HTML::Node>::iterator end1 = tr.end();

		for(; it1 != end1; ++it1)
		{
			if(it1->isTag() && (it1->tagName() == string("base")))
			{
				it1->parseAttributes();
				pair<bool,string> ab = it1->attribute("href");
				if(ab.first == true)
				{
					baseTag = ab.second;
					string accc = ab.second;
				}
			}
		}
		if(baseTag.empty() == true)
		{
			baseTag = p->getBase();
		}
		protocol = p->getProtocol();
	} catch (exception &e) {
		cerr << "Exception " << e.what() << " caught" << endl;
		//exit(1);
	} catch (...) {
		cerr << "Unknow exception caught " << endl;
	}

}
void HtmlParser::ParseText()
{
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
					   if(ab.second[0] != '/' && ab.second.find("http",0,4) == string::npos)
					   {
						   continue;
					   }
					   if(uf->doFilter(ab.second) == false)
					   {
						   continue;
					   }
					   insertQueue(ab.second);
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
void HtmlParser::insertQueue(string bac)
{
	   string abc = modifyurl(bac);
	   bool tmp;
	   MessageBus::getInstance()->call(5,"isInBloomSet",(void*)abc.c_str(),NULL,NULL,NULL,NULL,(void*)&tmp,NULL);

	   if(tmp == false)
	   {
	//	   printf("the insert queue is %s\n",abc.c_str());
		   bool tmp1 = URL_Queue_Singleton::instance()->isExist(abc);
		   if(tmp1 == false)
		   {
			   URL_Queue_Singleton::instance()->insert_queue(abc,1);  //1优先级
		   }
	   }
	   else
	   {
		   int i = 0;
	   }
}
int HtmlParser::svc(void)
{
	Document *pp;
	char text[max_doc];

	while(1)
	{
		bool retval;
		MessageBus::getInstance()->call(3,"isEmpty",NULL,NULL,NULL,NULL,NULL,&retval,NULL);
		if(!retval)
		{
			baseTag = "";
			data_buffer = "";
			memset(text,0,1024*1024);
			MessageBus::getInstance()->call(3,"pop_queue",NULL,NULL,NULL,NULL,NULL,NULL,(void**)&pp);
			int s = pp->getDoc((unsigned char*)text);
			if(s != 0)
			{
				text[s]='\0';
				data_buffer = text;
				//写入文件
				writeFile(pp);
				//writeBase(pp);
				MessageBus::getInstance()->call(5,"addToBloomSet",(void*)pp->GetURL().c_str(),NULL,NULL,NULL,NULL,NULL,NULL);
			}
			getBaseTag(pp);
			if(pp->GetLinkURL().empty() == true)
			{
				ParseText();
			}
			else
			{
				insertQueue(pp->GetLinkURL());
			}
			pp->Reset();
			Mem_Pool::getInstance()->freeObject(pp);
		}
		else
		{
			usleep(200000);
		}
	}
		return 0;
}
