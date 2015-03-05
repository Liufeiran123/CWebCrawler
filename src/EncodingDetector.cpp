/*
 * EncodingDetector.cpp
 *
 *  Created on: 2015年2月8日
 *      Author: lfr
 */

#include "EncodingDetector.h"



EncodingDetector::EncodingDetector() {
	// TODO Auto-generated constructor stub
	ud = uchardet_new();
}

EncodingDetector::~EncodingDetector() {
	// TODO Auto-generated destructor stub
	uchardet_delete(ud);
}


int EncodingDetector::setData(const char *buffer,int size)
{
	int ret = uchardet_handle_data(ud,buffer,size);
	uchardet_data_end(ud);
	return ret;
}
const char *EncodingDetector::getEncoding()
{
	   return uchardet_get_charset(ud);
}
