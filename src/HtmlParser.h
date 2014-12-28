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
	  void parseText ();
	  // enter a comment
	  void parseComment ();
	  // enter a tag
	  void parseTag ();
	  // enter a tag content
	  void parseContent (int action);

	  void SetBuffer(char *b);
private:
	  // parsing position
	  char *posParse;
	  // current position in the buffer
	  uint pos;
	  // data buffer
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
