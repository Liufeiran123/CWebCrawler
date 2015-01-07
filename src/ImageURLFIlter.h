/*
 * ImageURLFIlter.h
 *
 *  Created on: 2015年1月7日
 *      Author: lfr
 */

#ifndef IMAGEURLFILTER_H_
#define IMAGEURLFILTER_H_

#include "URLFilter.h"
#include <list>
using namespace std;

class ImageURLFIlter: public URLFilter {
public:
	ImageURLFIlter();
	virtual ~ImageURLFIlter();
public:
	virtual bool doFilter(string c);
	void initfilter();
private:
	list<string> strfilter;

};

#endif /* IMAGEURLFILTER_H_ */
