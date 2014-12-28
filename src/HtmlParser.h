/*
 * HtmlParser.h
 *
 *  Created on: 2014年12月16日
 *      Author: lfr
 */

#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <ace/Task_T.h>
#include <string>

using namespace std;

class HtmlParser :  public ACE_Task<ACE_NULL_SYNCH>, MessageComponent {
public:
	HtmlParser();
	virtual ~HtmlParser();
public:

	//提取文本
	  void parseText (){}
	//提取URL，添加到URLQueue中
	  void parseURL ();
protected:

	  void SetBuffer()

private:
	  string data_buffer;
public:
		int open(void*)
		{
			ACE_DEBUG((LM_DEBUG,"(%t) Active Object opened \n"));
			//Activate the object with a thread in it.
			activate();
			return 0;
		}
		int close(u_long)
		{
			ACE_DEBUG((LM_DEBUG, "(%t) Active Object being closed down \n"));
			return 0;
		}
		int svc(void)
		{

			return 0;
		}
};

#endif /* HTMLPARSER_H_ */
