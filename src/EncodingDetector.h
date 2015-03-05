/*
 * EncodingDetector.h
 *
 *  Created on: 2015年2月8日
 *      Author: lfr
 */

#ifndef ENCODINGDETECTOR_H_
#define ENCODINGDETECTOR_H_

#include "uchardet.h"

class EncodingDetector {
public:
	EncodingDetector();
	virtual ~EncodingDetector();
private:
	uchardet_t ud;
public:
	int setData(const char *buffer,int size);
	const char *getEncoding();
};

#endif /* ENCODINGDETECTOR_H_ */
