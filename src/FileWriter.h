/*
 * FileWriter.h
 *
 *  Created on: 2015年3月6日
 *      Author: lfr
 */

#ifndef FILEWRITER_H_
#define FILEWRITER_H_

#include <string>
#include <vector>
#include <fstream>
#include "ace/Task_T.h"
#include "ParserDom.h"
#include "utils.h"
#include "Document.h"
#include "MemPool.h"
#include "MessageBus.h"
#include "CharsetConverter.h"
#include "EncodingDetector.h"
#include "commondefine.h"
#include "htmlwriter.h"

using namespace std;

class FileWriter :  public ACE_Task<ACE_NULL_SYNCH>, public MessageComponent{
public:
	FileWriter();
	~FileWriter();
private:
	  string data_buffer;  //html文件内容
	  htmlwriter<QfsWriter> hw;
public:
		int start();
		int stop();
		virtual void call(string/*插件方法名*/,void *,void*,void *,void*,void *,void *,void **/*函数返回值*/);
		int svc(void);
public:
		void writeFile(Document*);
		int CharSetConv(string &charset,string &title,string &content,vector<string> &v);  //转换到UTF-8
};

#endif /* FILEWRITER_H_ */
