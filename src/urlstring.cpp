/*
 * urlstring.cpp
 *
 *  Created on: 2015年1月4日
 *      Author: lfr
 */

#include "urlstring.h"

urlstring::urlstring(string u,int ul):url(u),priority(ul){
	// TODO Auto-generated constructor stub

}

urlstring::~urlstring() {
	// TODO Auto-generated destructor stub
}

/*urlstring::urlstring(const urlstring& rs)
{


}
*/

string urlstring::GetURL()
{
	return url;
}
