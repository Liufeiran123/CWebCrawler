/*
 * HTTPURL.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "HTTPURL.h"
#include "netdb.h"
#include "python2.7/Python.h"
#include "Url.h"

HTTP_URL::HTTP_URL(string url) {
	// TODO Auto-generated constructor stub
	m_url = url;
}

HTTP_URL::~HTTP_URL() {
	// TODO Auto-generated destructor stub
}

void HTTP_URL::URLParser(int a)
{
	oneurl url;
	url.ParseUrl(m_url);
	host = url.GetHost();
	m_file = url.GetPath();
	printf("the url is %s\n",m_url.c_str());
	printf("the m_file is %s\n\n",m_file.c_str());
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

string HTTP_URL::getBase()
{
	  int i = strlen(m_url.c_str());
	 // assert (file[0] == '/');
	  while (m_url[i] != '/') {
		i--;
	  }
	  char newFile[1024];
	  memcpy(newFile, m_url.c_str(), i+1);
	  newFile[i+1] = 0;
	  return string(newFile);
}


