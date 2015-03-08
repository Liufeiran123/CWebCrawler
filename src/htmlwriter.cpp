/*
 * htmlwriter.cpp
 *
 *  Created on: 2015年2月3日
 *      Author: lfr
 */

#include <fcntl.h>
#include "htmlwriter.h"

htmlWriterImpl::htmlWriterImpl()
{

}
htmlWriterImpl::~htmlWriterImpl()
{

}

int htmlWriterImpl::init()
{
	return 0;
}

void htmlWriterImpl::fini()
{

}

QfsWriter::QfsWriter()
{

}
QfsWriter::~QfsWriter()
{

}

int QfsWriter::init()
{
    mKfsClient = KfsClient::Connect("127.0.0.1",20000, 0);
    if(!mKfsClient)
    {
    	return -1;
    }
    return 0;
}

void QfsWriter::Writehtml(string title,string content)
{
	  string filename = "/crawler/";
	  filename +=title;
	  const int kfsfd =  mKfsClient->Open(
			  filename.c_str(),  O_CREAT | O_WRONLY ,
	            1,
	            0,
	            0,
	            0,
	            1,
	            0666,
	            15,
	            15
	        );

	    if (kfsfd < 0) {
	        cout << "open"<<filename;
	        return;
	    }

	  size_t ret = mKfsClient->Write(kfsfd, content.c_str(), content.size());

	  mKfsClient->Sync(kfsfd);
}

void QfsWriter::fini()
{
	if(mKfsClient)
	{
		delete mKfsClient;
	}
}
/*
template<typename implT>
htmlwriter<implT>::htmlwriter(string brokerurl,string queuename) {
	// TODO Auto-generated constructor stub
	this->brokerurl = brokerurl;
	this->queuename = queuename;

	activemq::library::ActiveMQCPP::initializeLibrary();
}
template<typename implT>
htmlwriter<implT>::~htmlwriter() {
	// TODO Auto-generated destructor stub
	activemq::library::ActiveMQCPP::shutdownLibrary();


}
template<typename implT>
void htmlwriter<implT>::InitWriter()
{
	try {
			// Create a ConnectionFactory
			auto_ptr<ConnectionFactory> connectionFactory( ConnectionFactory::createCMSConnectionFactory( brokerurl ) );

	        // Create a Connection
	        connection = connectionFactory->createConnection();
	        connection->start();

	        // Create a Session
			session = connection->createSession( Session::AUTO_ACKNOWLEDGE );

	        // Create the destination (Topic or Queue)
			destination = session->createQueue( queuename );

	        // Create a MessageProducer from the Session to the Topic or Queue
	        producer = session->createProducer( destination );
	        producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

	        message = session->createStreamMessage();
	}catch ( CMSException& e ) {
	            e.printStackTrace();
	    }
	impl = new implT();
}
template<typename implT>
void htmlwriter<implT>::Writehtml(string url,string title,string content)
{
	   message->clearBody();
	   message->clearProperties();
//	   message->setStringProperty();
//	   message->w
        message->writeString(url);
        message->writeString(title);
        message->writeString(content);
        producer->send( message );
}
*/

LocalWriter::LocalWriter()
{

}
LocalWriter::~LocalWriter()
{

}

int LocalWriter::init()
{
	return 0;
}
void LocalWriter::Writehtml(string title,string content)
{
	string filename = "/home/lfr/crawlerData/";
	filename += title;
	ofstream fs(filename.c_str());
	fs<<content;
}
void LocalWriter::fini()
{

}
