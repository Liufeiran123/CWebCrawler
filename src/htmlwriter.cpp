/*
 * htmlwriter.cpp
 *
 *  Created on: 2015年2月3日
 *      Author: lfr
 */

#include "htmlwriter.h"

htmlwriter::htmlwriter(string brokerurl,string queuename) {
	// TODO Auto-generated constructor stub
	this->brokerurl = brokerurl;
	this->queuename = queuename;

	activemq::library::ActiveMQCPP::initializeLibrary();
}

htmlwriter::~htmlwriter() {
	// TODO Auto-generated destructor stub
	activemq::library::ActiveMQCPP::shutdownLibrary();


}

void htmlwriter::InitWriter()
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
}

void htmlwriter::Writehtml(string url,string title,string content)
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


