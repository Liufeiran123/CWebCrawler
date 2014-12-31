/*
 * HtmlParser.cpp
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#include "HtmlParser.h"

HtmlParser::HtmlParser() {
	// TODO Auto-generated constructor stub

}

HtmlParser::~HtmlParser() {
	// TODO Auto-generated destructor stub
}


void HtmlParser::call(string/*插件方法名*/,void *,void*,void *,void*,void *,unsigned long &/*函数返回值*/)
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
