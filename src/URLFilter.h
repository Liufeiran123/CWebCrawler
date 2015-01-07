/*
 * URLFilter.h
 *
 *  Created on: 2015年1月7日
 *      Author: lfr
 */

#ifndef URLFILTER_H_
#define URLFILTER_H_

#include <string>
using namespace std;

class URLFilter {
public:
	URLFilter();
	virtual ~URLFilter();
public:
	virtual bool doFilter(string c) = 0;
};

#endif /* URLFILTER_H_ */
