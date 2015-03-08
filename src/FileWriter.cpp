/*
 * FileWriter.cpp
 *
 *  Created on: 2015年3月6日
 *      Author: lfr
 */

#include "FileWriter.h"

FileWriter::FileWriter():isstop(true) {
	// TODO Auto-generated constructor stub
	hw.InitWriter();

}

FileWriter::~FileWriter() {
	// TODO Auto-generated destructor stub
	hw.finiWriter();
}

void FileWriter::call(string/*插件方法名*/,void *,void*,void *,void*,void *,void *,void **/*函数返回值*/)
{

}

int FileWriter::start()
{
	isstop = false;
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

int FileWriter::stop()
{
	isstop = true;
	this->wait();
	return 0;
}

int FileWriter::svc(void)
{
	Document *pp;
	char text[max_doc];
	while(!isstop)
	{
		bool retval;
		MessageBus::getInstance()->call(11,"isEmpty",NULL,NULL,NULL,NULL,NULL,&retval,NULL);
		if(!retval)
		{
			memset(text,0,1024*1024);
			MessageBus::getInstance()->call(11,"pop_queue",NULL,NULL,NULL,NULL,NULL,NULL,(void**)&pp);
			int s = pp->getDoc((unsigned char*)text);
			if(s != 0 )
			{
				text[s]='\0';
				data_buffer = text;
				//写入文件
				writeFile(pp);
			}
	//		pp->Reset();
			Mem_Pool::getInstance()->freeObject(pp);
		}
		else
		{
			usleep(200000);
		}
	}
		return 0;
}

void FileWriter::writeFile(Document* p)
{
	vector<string> v;
 	string title = p->GetTitle();
	string charset = p->GetCharEncoding();
	if(charset.empty())
	{
		ACE_DEBUG ((LM_INFO, ACE_TEXT ("charset is empty\n")));
		//自动测试字符编码
		return;
	}
	string dir = "/home/lfr/crawlerData/";
	if(CharSetConv(charset,title,data_buffer,v) == 0)
	{
		v[0].append(".html");
		/*dir+= v[0];
		ofstream fs(dir.c_str());
		fs<<v[1];*/
		hw.Writehtml(v[0],v[1]);
	}
}

int FileWriter::CharSetConv(string &charset,string &title,string &content,vector<string> &v)
{
	string encoding;
	string targetencoding = "UTF-8";

	if("gb2312" == charset)
	{
		charset = "GB18030";
	}

	encoding.resize(charset.size());

	std::transform(charset.begin(),charset.end(),encoding.begin(), ::toupper);

	if("UTF-8" != encoding)
	{
		string data1;
		string title1;
		   iconv_t t = CharsetConverter::Open(targetencoding,encoding);
		   if((iconv_t) -1 == t)
		   {
				ACE_DEBUG ((LM_INFO, ACE_TEXT ("charset converter open error\n")));
				return -1;
		   }
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
