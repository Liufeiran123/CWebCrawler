/*
 * urlstring.h
 *
 *  Created on: 2015年1月4日
 *      Author: lfr
 */

#ifndef URLSTRING_H_
#define URLSTRING_H_

#include <string>

using namespace std;

class urlstring {
public:
	urlstring(string u,int ul);
	virtual ~urlstring();

/*	urlstring(const urlstring& u);
	urlstring &operator=(const urlstring &u);
*/
private:
	string url;

public:
	string GetURL();
	int priority;

};

struct cmp{
    bool operator() ( urlstring a, urlstring b ){
    	if( a.priority < b.priority )
        {
        	return true;
        }
        return false;
    }
};

#endif /* URLSTRING_H_ */
