/*
 * HTTPURL.h
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#ifndef HTTPURL_H_
#define HTTPURL_H_

#include "ace/INET_Addr.h"
#include <string>

using namespace std;

class HTTP_URL {
public:
	explicit HTTP_URL(string url);
	virtual ~HTTP_URL();
private:

	//URL地址
	string m_netaddr;
	//URL主机名
	string host;
	//file
	string m_file;
	//URL
	string m_url;

	char urlstr1[1024];
public:
	void URLParser();
	int gethostaddr();
};

#endif /* HTTPURL_H_ */
