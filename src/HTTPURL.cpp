/*
 * HTTPURL.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "HTTPURL.h"
#include "netdb.h"
#include "python2.7/Python.h"

HTTP_URL::HTTP_URL(string url) {
	// TODO Auto-generated constructor stub
	m_url = url;
}

HTTP_URL::~HTTP_URL() {
	// TODO Auto-generated destructor stub
}

void HTTP_URL::URLParser()
{
	  memset(urlstr1,0,1024);
	  sprintf(urlstr1,"urlstr=\'%s\'",m_url.c_str());

	  Py_Initialize();
	  PyRun_SimpleString("from urlparse import urlparse") ;
	  PyRun_SimpleString("def getnetloc(x):\n"
						"	o=urlparse(x)\n"
						"	return o.netloc\n");


	  PyRun_SimpleString(urlstr1);
	  PyObject* mainModule = PyImport_ImportModule("__main__" );
	  PyObject* dict = PyModule_GetDict(mainModule);
	  PyObject* resultObject = PyRun_String("getnetloc(urlstr)" , Py_eval_input, dict, dict);


	  if (resultObject)
	    {
		  	host = PyString_AsString(resultObject);
		  	char *p = (char*)m_url.c_str();
		  	p+=8;
		  	m_file = strchr(p,'/');
	        Py_DECREF(resultObject);
	    }
	  Py_Finalize();
}


int HTTP_URL::gethostaddr()
{
    struct hostent hostbuf, *hp;
    size_t hstbuflen;
    char tmphstbuf[1024];
    int res;
    int herr;

    hstbuflen = 1024;

    res = gethostbyname_r (host.c_str(), &hostbuf, tmphstbuf, hstbuflen,
            &hp, &herr);
    /*  Check for errors.  */
    if (res || hp == NULL)
        return -1;
    //char *p = hp->h_addr;

    char tmp[48];

    m_netaddr = inet_ntop(AF_INET, hp->h_addr, tmp, 48);
   // 这个函数，是将类型为af的网络地址结构src，转换成主机序的字符串形式，存放在长度为cnt的字符串中。
   // 这个函数，其实就是返回指向dst的一个指针。如果函数调用错误，返回值是NULL。


    return 0;
}

string & HTTP_URL::getip()
{
	return m_netaddr;
}

string & HTTP_URL::gethost()
{
	return host;
}
string & HTTP_URL::getFile()
{
	return m_file;
}




