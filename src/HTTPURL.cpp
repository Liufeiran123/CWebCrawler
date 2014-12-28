/*
 * HTTPURL.cpp
 *
 *  Created on: 2014年12月15日
 *      Author: lfr
 */

#include "HTTPURL.h"
#include "netdb.h"

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
		  	m_file = strstr(m_url.c_str(),host.c_str());
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

    m_netaddr = hp->h_addr;
    return 0;
}
