/*
 * htmlwriter.h
 *
 *  Created on: 2015年2月3日
 *      Author: lfr
 */

#ifndef HTMLWRITER_H_
#define HTMLWRITER_H_

#include <string>
#include <fstream>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/lang/Long.h>
#include <decaf/lang/System.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include "KfsClient.h"

using namespace KFS;
using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;

class htmlWriterImpl
{
public:
	htmlWriterImpl();
	virtual ~htmlWriterImpl();
public:
	virtual int init();
	virtual void Writehtml(string title,string content) = 0;
	virtual void fini();
};

class QfsWriter : public htmlWriterImpl
{
public:
	QfsWriter();
	~QfsWriter();
private:
	   KfsClient* mKfsClient;
public:
	   virtual int init();
	   virtual void Writehtml(string title,string content);
	   virtual void fini();
private:
};

class LocalWriter : public htmlWriterImpl
{
public:
	LocalWriter();
	~LocalWriter();
public:
	   virtual int init();
	   virtual void Writehtml(string title,string content);
	   virtual void fini();
private:
};

/*template<typename implT>
class htmlwriter {
public:
	htmlwriter(string brokerurl,string queuename)
{

}
	 ~htmlwriter();
public:
	void InitWriter();
	void Writehtml(string url,string title,string content);
private:
	Connection*      connection;
    Session*         session;
    Destination*     destination;
    MessageProducer* producer;

    StreamMessage* message;

    string brokerurl;
    string queuename;

    htmlWriterImpl *impl;
};
*/
template<typename implT>
class htmlwriter {
public:
	htmlwriter()
{

}
	 ~htmlwriter()
	 {

	 }
public:
	void InitWriter()
	{
		impl = new implT();
		impl->init();
	}
	void Writehtml(string title,string content)
	{
		impl->Writehtml(title,content);
	}
	void finiWriter()
	{
		impl->fini();
		delete impl;
	}
private:
    htmlWriterImpl *impl;
};

#endif /* HTMLWRITER_H_ */
